/* MSPDebug - debugging tool for MSP430 MCUs
 * Copyright (C) 2009-2012 Daniel Beer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "dis.h"
#include "device.h"
#include "binfile.h"
#include "stab.h"
#include "util.h"
#include "usbutil.h"
#include "gdb.h"
#include "rtools.h"
#include "sym.h"
#include "devcmd.h"
#include "expr.h"
#include "opdb.h"
#include "reader.h"
#include "output.h"
#include "output_util.h"
#include "simio.h"
#include "ctrlc.h"

#include "sim.h"
#include "bsl.h"
#include "fet.h"
#include "vector.h"
#include "fet_db.h"
#include "fet_olimex_db.h"
#include "gdbc.h"
#include "tilib.h"
#include "goodfet.h"
#include "input.h"
#include "input_async.h"
#include "pif.h"

#include "flash_bsl.h"
#include "reset.h"
#include "debug.h"
#include "tapslip.h"

#define OPT_NO_RC		0x01
#define OPT_EMBEDDED		0x02

struct cmdline_args {
	const char		*driver_name;
	int			flags;
	struct device_args	devarg;
};

static const struct device_class *const driver_table[] = {
	&device_rf2500,
	&device_olimex,
	&device_olimex_v1,
	&device_olimex_iso,
	&device_olimex_iso_mk2,
	&device_sim,
	&device_uif,
	&device_bsl,
	&device_flash_bsl,
	&device_gdbc,
	&device_tilib,
	&device_goodfet,
	&device_pif,
	&device_reset,
	&device_debug,
	&device_tapslip,
};

static const char *version_text =
"MSPDebug version 0.21 - debugging tool for MSP430 MCUs\n"
"Copyright (C) 2009-2012 Daniel Beer <dlbeer@gmail.com>\n"
"This is free software; see the source for copying conditions.  There is NO\n"
"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR "
"PURPOSE.\n";

static void usage(const char *progname)
{
	int i;

	printc_err("Usage: %s [options] <driver> [command ...]\n"
"\n"
"    -q\n"
"        Start in quiet mode.\n"
"    -d device\n"
"        Connect via the given tty device, rather than USB.\n"
"    -U bus:dev\n"
"        Specify a particular USB device to connect to.\n"
"    -s serial\n"
"        Specify a particular device serial number to connect to.\n"
"    -j\n"
"        Use JTAG, rather than Spy-Bi-Wire (UIF devices only).\n"
"    -v voltage\n"
"        Set the supply voltage, in millivolts.\n"
"    -n\n"
"        Do not read ~/.mspdebug on startup.\n"
"    --long-password\n"
"        Send 32-byte IVT as BSL password (flash-bsl only)\n"
"    --help\n"
"        Show this help text.\n"
"    --fet-list\n"
"        Show a list of devices supported by the FET driver.\n"
"    --fet-force-id string\n"
"        Override the device ID returned by the FET.\n"
"    --usb-list\n"
"        Show a list of available USB devices.\n"
"    --force-reset\n"
"        Force target reset in initialization sequence.\n"
"    --allow-fw-update\n"
"        Update FET firmware (tilib only) if necessary.\n"
"    --require-fw-update <image.txt>\n"
"        Require FET firmware update. The required image format depends\n"
"        on the driver.\n"
"    --version\n"
"        Show copyright and version information.\n"
"    --embedded\n"
"        Run in embedded mode.\n"
"\n"
"Most drivers connect by default via USB, unless told otherwise via the\n"
"-d option. By default, the first USB device found is opened.\n"
"\n"
"If commands are given, they will be executed. Otherwise, an interactive\n"
"command reader is started.\n\n",
		progname);

	printc("Available drivers are:\n");
	for (i = 0; i < ARRAY_LEN(driver_table); i++) {
		const struct device_class *drv = driver_table[i];

		printc("    %s\n        %s\n", drv->name, drv->help);
	}
}

static void process_rc_file(void)
{
	const char *home = getenv("HOME");
	char text[256];

	if (!home)
		return;

	snprintf(text, sizeof(text), "%s/.mspdebug", home);
	if (!access(text, F_OK))
		process_file(text, 0);
}

static int add_fet_device(void *user_data, const struct fet_db_record *r)
{
	struct vector *v = (struct vector *)user_data;

	return vector_push(v, &r->name, 1);
}

static int add_fet_olimex_device(void *user_data, const char *name)
{
	struct vector *v = (struct vector *)user_data;

	return vector_push(v, &name, 1);
}

static int list_devices(void)
{
	struct vector v;

	vector_init(&v, sizeof(const char *));
	if (fet_db_enum(add_fet_device, &v) < 0) {
		pr_error("couldn't allocate memory");
		vector_destroy(&v);
		return -1;
	}

	printc("Devices supported by FET driver:\n");
	namelist_print(&v);
	vector_destroy(&v);

	vector_init(&v, sizeof(const char *));
	if (fet_olimex_db_enum(add_fet_olimex_device, &v) < 0) {
		pr_error("couldn't allocate memory");
		vector_destroy(&v);
		return -1;
	}

	printc("\n");
	printc("Devices supported by Olimex FET driver:\n");
	namelist_print(&v);
	vector_destroy(&v);

	return 0;
}

static int parse_cmdline_args(int argc, char **argv,
			      struct cmdline_args *args)
{
	int opt;
	static const struct option longopts[] = {
		{"help",                0, 0, 'H'},
		{"fet-list",            0, 0, 'L'},
		{"fet-force-id",        1, 0, 'F'},
		{"usb-list",            0, 0, 'I'},
		{"version",             0, 0, 'V'},
		{"long-password",       0, 0, 'P'},
		{"force-reset",		0, 0, 'R'},
		{"allow-fw-update",	0, 0, 'A'},
		{"require-fw-update",	1, 0, 'M'},
		{"embedded",		0, 0, 'E'},
		{NULL, 0, 0, 0}
	};
	int want_usb = 0;

	while ((opt = getopt_long(argc, argv, "d:jv:nU:s:q",
				  longopts, NULL)) >= 0)
		switch (opt) {
		case 'q':
			{
				static const union opdb_value v = {
					.boolean = 1
				};

				opdb_set("quiet", &v);
			}
			break;

		case 'E':
			args->flags |= OPT_EMBEDDED;
			break;

		case 'A':
			args->devarg.flags |= DEVICE_FLAG_DO_FWUPDATE;
			break;

		case 'I':
			usb_init();
			usb_find_busses();
			usb_find_devices();
			usbutil_list();
			exit(0);

		case 'd':
			args->devarg.path = optarg;
			args->devarg.flags |= DEVICE_FLAG_TTY;
			break;

		case 'M':
			args->devarg.require_fwupdate = optarg;
			break;

		case 'U':
			args->devarg.path = optarg;
			want_usb = 1;
			break;

		case 's':
			args->devarg.requested_serial = optarg;
			break;

		case 'L':
			exit(list_devices());

		case 'F':
			args->devarg.forced_chip_id = optarg;
			break;

		case 'H':
			usage(argv[0]);
			exit(0);

		case 'V':
			printc("%s", version_text);
			exit(0);

		case 'v':
			args->devarg.vcc_mv = atoi(optarg);
			break;

		case 'j':
			args->devarg.flags |= DEVICE_FLAG_JTAG;
			break;

		case 'n':
			args->flags |= OPT_NO_RC;
			break;

		case 'P':
			args->devarg.flags |= DEVICE_FLAG_LONG_PW;
			break;

		case 'R':
			args->devarg.flags |= DEVICE_FLAG_FORCE_RESET;
			break;

		case '?':
			printc_err("Try --help for usage information.\n");
			return -1;
		}

	if (want_usb && (args->devarg.flags & DEVICE_FLAG_TTY)) {
		printc_err("You can't simultaneously specify a serial and "
			"a USB device.\n");
		return -1;
	}

	if (optind >= argc) {
		printc_err("You need to specify a driver. Try --help for "
			"a list.\n");
		return -1;
	}

	args->driver_name = argv[optind];
	optind++;

	return 0;
}

int setup_driver(struct cmdline_args *args)
{
	int i;

	i = 0;
	while (i < ARRAY_LEN(driver_table) &&
	       strcasecmp(driver_table[i]->name, args->driver_name))
		i++;
	if (i >= ARRAY_LEN(driver_table)) {
		printc_err("Unknown driver: %s. Try --help for a list.\n",
			args->driver_name);
		return -1;
	}

	if (stab_init() < 0)
		return -1;

	device_default = driver_table[i]->open(&args->devarg);
	if (!device_default) {
		stab_exit();
		return -1;
	}

	return 0;
}

#ifdef __Windows__
static int sockets_init(void)
{
	WSADATA data;

	if (WSAStartup(MAKEWORD(2, 2), &data)) {
		printc_err("Winsock init failed");
		return -1;
	}

	return 0;
}

static void sockets_exit(void)
{
	WSACleanup();
}
#else
static int sockets_init(void) { return 0; }
static void sockets_exit(void) { }
#endif

int main(int argc, char **argv)
{
	struct cmdline_args args = {0};
	int ret = 0;

	setvbuf(stderr, NULL, _IOFBF, 0);
	setvbuf(stdout, NULL, _IOFBF, 0);

	opdb_reset();
	ctrlc_init();

	args.devarg.vcc_mv = 3000;
	args.devarg.requested_serial = NULL;
	if (parse_cmdline_args(argc, argv, &args) < 0)
		goto fail_parse;

	if (args.flags & OPT_EMBEDDED)
		input_module = &input_async;
	if (input_module->init() < 0)
		goto fail_input;

	output_set_embedded(args.flags & OPT_EMBEDDED);

	if (sockets_init() < 0) {
		ret = -1;
		goto fail_sockets;
	}

	printc_dbg("%s\n", version_text);
	if (setup_driver(&args) < 0) {
		ret = -1;
		goto fail_driver;
	}

	if (device_probe_id(device_default) < 0)
		printc_err("warning: device ID probe failed\n");

	simio_init();

	if (!(args.flags & OPT_NO_RC))
		process_rc_file();

	/* Process commands */
	if (optind < argc) {
		while (optind < argc) {
			if (process_command(argv[optind++]) < 0) {
				ret = -1;
				break;
			}
		}
	} else {
		reader_loop();
	}

	simio_exit();
	device_destroy();
	stab_exit();
fail_driver:
	sockets_exit();
fail_sockets:
	input_module->exit();
fail_input:
fail_parse:

	/* We need to do this on Windows, because in embedded mode we
	 * may still have a running background thread for input. If so,
	 * returning from main() won't cause the process to terminate.
	 */
#if defined(__Windows__) || defined(__CYGWIN__)
	ExitProcess(ret);
#endif
	return ret;
}