/* MSPDebug - debugging tool for the eZ430
 * Copyright (C) 2009, 2010 Daniel Beer
 * Copyright (C) 2010 Andrew Armenia
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
 *
 * Modified: Rafael Marin-Perez rafael81@um.es  
 * Copyright (C) 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#include "reset.h"
#include "util.h"
#include "output.h"
#include "fet_error.h"
#include "sport.h"

static device_t reset_open(const struct device_args *args)
{
    int fd;

	fd = sport_open(args->path, 9600, SPORT_EVEN_PARITY);
	if (SPORT_ISERR(fd)) {
		printc_err("reset: can't open %s: %s\n", args->path, last_error());
		return NULL;
	}


    printf("--------------------------------------------\n");
    printf("Reset application via RS-232\n");
    printf("  Set LOW to RESET pin in DTR line\n");
    printf("--------------------------------------------\n\n");
    
    /* enter RESET pin in DTR line */      
    if (sport_set_modem(fd, ~ SPORT_MC_DTR) != 0) {
        printc_err("reset: failed to set low the DTR line");
        return NULL;
    }
	delay_ms(50);

    sport_close(fd);
    return NULL;

}

const struct device_class device_reset = {
	.name		= "reset",
	.help = "Reset application via RS-232",
	.open		= reset_open,
	.destroy	= NULL, //reset_destroy,
	.readmem	= NULL, //reset_readmem,
	.writemem	= NULL, //reset_writemem,
	.getregs	= NULL, //reset_getregs,
	.setregs	= NULL, //reset_setregs,
	.ctl		= NULL, //reset_ctl,
	.poll		= NULL, //reset_poll,
	.erase		= NULL, //reset_erase
};
