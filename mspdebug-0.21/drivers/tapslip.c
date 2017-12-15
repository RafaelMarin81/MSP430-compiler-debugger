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

#include "tapslip.h"
#include "util.h"
#include "output.h"
#include "fet_error.h"
#include "sport.h"

/*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <err.h>

in_addr_t giaddr;
in_addr_t netaddr;
in_addr_t circuit_addr;

int ssystem(const char *fmt, ...)
         __attribute__((__format__ (__printf__, 1, 2)));
         void write_to_serial(int outfd, void *inbuf, int len);

#define USAGE_STRING "usage: tapslip6 [-B baudrate] [-s siodev] [-t tundev] ipaddress netmask"

char tundev[32] = { "tap0" };

int
ssystem(const char *fmt, ...) __attribute__((__format__ (__printf__, 1, 2)));

int
ssystem(const char *fmt, ...)
{
    char cmd[128];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(cmd, sizeof(cmd), fmt, ap);
    va_end(ap);
    printf("[tapslip] %s\n", cmd);
    fflush(stdout);
    return system(cmd);
}

#define SLIP_END     0300
#define SLIP_ESC     0333
#define SLIP_ESC_END 0334
#define SLIP_ESC_ESC 0335

static void
print_packet(u_int8_t *p, int len) {
    int i;
    for(i = 0; i < len; i++) {
        printf("%x", p[i]);
        if ((i & 3) == 3)
            printf(" ");
        if ((i & 15) == 15)
            printf("\n");
    }
    printf("\n");
}

int
is_sensible_string(const unsigned char *s, int len)
{
    int i;
    for(i = 1; i < len; i++) {
        if(s[i] == 0 || s[i] == '\r' || s[i] == '\n' || s[i] == '\t') {
            continue;
        } else if(s[i] < ' ' || '~' < s[i]) {
            return 0;
        }
    }
    return 1;
}

void
serial_to_tun(FILE *inslip, int outfd)
{
    static union {
        unsigned char inbuf[2000];
    } uip;
    static int inbufptr = 0;
    
    int ret;
    unsigned char c;
    
#ifdef linux
    ret = fread(&c, 1, 1, inslip);
    if(ret == -1 || ret == 0) err(1, "serial_to_tun: read");
    goto after_fread;
#endif
    
read_more:
    if(inbufptr >= sizeof(uip.inbuf)) {
        inbufptr = 0;
    }
    ret = fread(&c, 1, 1, inslip);
#ifdef linux
after_fread:
#endif
    if(ret == -1) {
        
        err(1, "serial_to_tun: read");
    }
    if(ret == 0) {
        clearerr(inslip);
        return;
        fprintf(stdout, "serial_to_tun: EOF\n");
        exit(1);
    }
    /*  fprintf(stdout, ".");*/
    switch(c) {
        case SLIP_END:
            if(inbufptr > 0) {
                if(uip.inbuf[0] == '!') {
                    if (uip.inbuf[1] == 'M') {
                        /* Read gateway MAC address and autoconfigure tap0 interface */
                        char macs[6*3+1];
                        
                        /* translation the same as ieee803 to ieee802.15.4 translation, i.e.
                         * 6lowpan mac address translation. */
                        snprintf(macs, sizeof(macs), "%c%c:%c%c:%c%c:%c%c:%c%c:%c%c\0",
                                uip.inbuf[2+2*0], uip.inbuf[2+2*0+1],
                                uip.inbuf[2+2*1], uip.inbuf[2+2*1+1],
                                uip.inbuf[2+2*2], uip.inbuf[2+2*2+1],
                                uip.inbuf[2+2*5], uip.inbuf[2+2*5+1],
                                uip.inbuf[2+2*6], uip.inbuf[2+2*6+1],
                                uip.inbuf[2+2*7], uip.inbuf[2+2*7+1]);
                        
                        printf("*** Gateway's ethernet MAC address: %s\n", macs);
                        
                        ssystem("ifconfig %s down", tundev);
                        ssystem("ifconfig %s hw ether %s", tundev, macs);
                        ssystem("ifconfig %s up", tundev);
                    }
#define DEBUG_LINE_MARKER '\r'
                } else if(uip.inbuf[0] == DEBUG_LINE_MARKER) {
                    fwrite(uip.inbuf + 1, inbufptr - 1, 1, stdout);
                } else if(is_sensible_string(uip.inbuf, inbufptr)) {
                    fwrite(uip.inbuf, inbufptr, 1, stdout);
                } else {
                    fprintf(stdout, "[tapslip] packet from serial to ethernet  len:%i\n",inbufptr);
                    fflush(stdout);
                    if(write(outfd, uip.inbuf, inbufptr) != inbufptr) {
                        err(1, "serial_to_tun: write");
                    }
                }
                inbufptr = 0;
            }
            break;
            
        case SLIP_ESC:
            if(fread(&c, 1, 1, inslip) != 1) {
                clearerr(inslip);
                /* Put ESC back and give up! */
                ungetc(SLIP_ESC, inslip);
                return;
            }
            
            switch(c) {
                case SLIP_ESC_END:
                    c = SLIP_END;
                    break;
                case SLIP_ESC_ESC:
                    c = SLIP_ESC;
                    break;
            }
            /* FALLTHROUGH */
        default:
            uip.inbuf[inbufptr++] = c;
            break;
    }
    
    goto read_more;
}

unsigned char slip_buf[2000];
int slip_end, slip_begin;

void
slip_send(int fd, unsigned char c)
{
    if (slip_end >= sizeof(slip_buf))
        err(1, "slip_send overflow");
    slip_buf[slip_end] = c;
    slip_end++;
}

int
slip_empty()
{
    return slip_end == 0;
}

void
slip_flushbuf(int fd)
{
    int n;
    
    if (slip_empty())
        return;
    
    n = write(fd, slip_buf + slip_begin, (slip_end - slip_begin));
    
    if(n == -1 && errno != EAGAIN) {
        err(1, "slip_flushbuf write failed");
    } else if(n == -1) {
        fprintf(stdout, "[tapslip] Outqueueis full!\n");              /* Outqueueis full! */
        fflush(stdout);
    } else {
        slip_begin += n;
        if(slip_begin == slip_end) {
            slip_begin = slip_end = 0;
        }
    }
}

void
write_to_serial(int outfd, void *inbuf, int len)
{
    u_int8_t *p = inbuf;
    int i, ecode;
    /* It would be ``nice'' to send a SLIP_END here but it's not
     * really necessary.
     */
    slip_send(outfd, SLIP_END);
//    printf("[tapslip] writing packet to serial!!! %d\n", len);
    for(i = 0; i < len; i++) {
        switch(p[i]) {
            case SLIP_END:
                slip_send(outfd, SLIP_ESC);
                slip_send(outfd, SLIP_ESC_END);
                break;
            case SLIP_ESC:
                slip_send(outfd, SLIP_ESC);
                slip_send(outfd, SLIP_ESC_ESC);
                break;
            default:
                slip_send(outfd, p[i]);
//                printf("%.2X ", p[i]);
                break;
        }
        
    }
    slip_send(outfd, SLIP_END);
    fprintf(stdout, "[tapslip] packet from ethernet to serial len:%i\n", len);
    fflush(stdout); 
}

/*
 * Read from tun, write to slip.
 */
void
tun_to_serial(int infd, int outfd)
{
    struct {
        unsigned char inbuf[2000];
    } uip;
    int size;
    
    if((size = read(infd, uip.inbuf, 2000)) == -1) err(1, "tun_to_serial: read");
    
    write_to_serial(outfd, uip.inbuf, size);
}

#ifndef BAUDRATE
#define BAUDRATE B115200
#endif
speed_t b_rate = BAUDRATE;

void
stty_telos(int fd)
{
    struct termios tty;
    speed_t speed = b_rate;
    int i;
    
    if(tcflush(fd, TCIOFLUSH) == -1) err(1, "tcflush");
    
    if(tcgetattr(fd, &tty) == -1) err(1, "tcgetattr");
    
    cfmakeraw(&tty);
    
    /* Nonblocking read. */
    tty.c_cc[VTIME] = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag &= ~HUPCL;
    tty.c_cflag &= ~CLOCAL;
    
    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);
    
    if(tcsetattr(fd, TCSAFLUSH, &tty) == -1) err(1, "tcsetattr");
    
#if 1
    /* Nonblocking read and write. */
    /* if(fcntl(fd, F_SETFL, O_NONBLOCK) == -1) err(1, "fcntl"); */
    
    tty.c_cflag |= CLOCAL;
    if(tcsetattr(fd, TCSAFLUSH, &tty) == -1) err(1, "tcsetattr");
    
    //i = TIOCM_DTR;
    //if(ioctl(fd, TIOCMBIS, &i) == -1) err(1, "ioctl");
#endif

    usleep(10*1000);              /* Wait for hardware 10ms. */
    
    /* Flush input and output buffers. */
    if(tcflush(fd, TCIOFLUSH) == -1) err(1, "tcflush");
}

int
devopen(const char *dev, int flags)
{
    char t[32];
    strcpy(t, "/dev/");
    strcat(t, dev);
    return open(t, flags);
}

#include <linux/if.h>
#include <linux/if_tun.h>

int
tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;
    
    if( (fd = open("/dev/net/tun", O_RDWR)) < 0 )
        return -1;
    
    memset(&ifr, 0, sizeof(ifr));
    
    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     * IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if(*dev != 0)
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    
    if((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        close(fd);
        return err;
    }
    strcpy(dev, ifr.ifr_name);
    return fd;
}


const char *ipaddr;
const char *netmask;


void
cleanup(void)
{
    ssystem("ifconfig %s down", tundev);
#ifndef linux
    ssystem("sysctl -w net.ipv6.conf.all.forwarding=1");
#endif
    /* ssystem("arp -d %s", ipaddr); */
    ssystem("netstat -nr"
            " | awk '{ if ($2 == \"%s\") print \"route delete -net \"$1; }'"
            " | sh",
            tundev);
}

void
sigcleanup(int signo)
{
    fprintf(stdout, "[tapslip] signal %d\n", signo);
    exit(0);                      /* exit(0) will call cleanup() */
}

static int got_sigalarm;
static int request_mac;

void
sigalarm(int signo)
{
    got_sigalarm = 1;
    return;
}

void
sigalarm_reset()
{
#ifdef linux
#define TIMEOUT (997*1000)
#else
#define TIMEOUT (2451*1000)
#endif
    ualarm(TIMEOUT, TIMEOUT);
    got_sigalarm = 0;
}

void
ifconf(const char *tundev, const char *ipaddr, const char *netmask)
{
    struct in_addr netname;
    netname.s_addr = inet_addr(ipaddr) & inet_addr(netmask);
    
#ifdef linux
    ssystem("ifconfig %s inet `hostname` up", tundev);
    if(strcmp(ipaddr, "0.0.0.0") != 0) {
        ssystem("route add -net %s netmask %s dev %s",
                inet_ntoa(netname), netmask, tundev);
    }
#else
    ssystem("ifconfig %s inet `hostname` %s up", tundev, ipaddr);
    if(strcmp(ipaddr, "0.0.0.0") != 0) {
        ssystem("route add -net %s -netmask %s -interface %s",
                inet_ntoa(netname), netmask, tundev);
    }
    ssystem("sysctl -w net.inet.ip.forwarding=1");
#endif /* !linux */

    ssystem("ifconfig %s\n", tundev);
}

/*********************************************************************************/

static device_t tapslip_open(const struct device_args *args)
{
    int fd;

	fd = sport_open(args->path, 115200, SPORT_EVEN_PARITY);
	if (SPORT_ISERR(fd)) {
		printc_err("tapslip: can't open %s: %s\n", args->path, last_error());
		return NULL;
	}


    printf("[tapslip] --------------------------------------------\n");
    printf("[tapslip] Ethbridge application via RS-232\n");
    printf("[tapslip] Set LOW to RESET pin in DTR line\n");
    printf("[tapslip] Exit: Ctrl+C\n");
    printf("[tapslip] --------------------------------------------\n\n");

    #include "ctrlc.h"
    ctrlc_exit();
   
    /* enter RESET pin in DTR line */      
    if (sport_set_modem_rafa(fd, ~ SPORT_MC_DTR) != 0) {
        printc_err("tapslip: failed to set low the DTR line");
        return NULL;
    }
	delay_ms(50);

//    sport_close(fd);
  //  return NULL;

/*********************************************************************************/
    {
        char siodev[30] = {"ttyUSB0"};
        int slipfd = fd;
        FILE *inslip;
        int tunfd, maxfd;
        int ret;
        fd_set rset, wset;
        request_mac = 1;

        ipaddr = "127.0.0.1"; // argv[1];
        netmask = "255.0.0.0"; // argv[2];
        circuit_addr = inet_addr(ipaddr);
        netaddr = inet_addr(ipaddr) & inet_addr(netmask);

        fprintf(stdout, "[tapslip] slip started on ``/dev/%s''\n", siodev);
        stty_telos(slipfd);
        slip_send(slipfd, SLIP_END);
        inslip = fdopen(slipfd, "r");
        if(inslip == NULL) err(1, "main: fdopen");
        
        tunfd = tun_alloc(tundev);
        printf("[tapslip] opening: %s\n", tundev);
        if(tunfd == -1) {
            fprintf(stdout, "[tapslip] ERROR: You require SUDO permission. to create device  /dev/%s\n", tundev);
            err(1, "main: open");
        }
        fprintf(stdout, "[tapslip] opened device ``/dev/%s''\n", tundev);
        
        atexit(cleanup);
        signal(SIGHUP, sigcleanup);
        signal(SIGTERM, sigcleanup);
        signal(SIGINT, sigcleanup);
        signal(SIGALRM, sigalarm);
        ifconf(tundev, ipaddr, netmask);

  
        while(1) {
            maxfd = 0;
            FD_ZERO(&rset);
            FD_ZERO(&wset);
            
            // request mac address from gateway node for autoconfiguration of ethernet interface tap0 
            if (request_mac) {
                slip_send(slipfd, '?');
                slip_send(slipfd, 'M');
                slip_send(slipfd, SLIP_END);
                request_mac = 0;
            }
            
            if(got_sigalarm) {         // Send "?IPA". 
                slip_send(slipfd, '?');
                slip_send(slipfd, 'I');
                slip_send(slipfd, 'P');
                slip_send(slipfd, 'A');
                slip_send(slipfd, SLIP_END);
                got_sigalarm = 0;
            }

            if(!slip_empty()) {         // Anything to flush? 
                FD_SET(slipfd, &wset);
            }
            
            FD_SET(slipfd, &rset);      // Read from slip ASAP! 
            if(slipfd > maxfd) maxfd = slipfd;
            
            // We only have one packet at a time queued for slip output. 
            if(slip_empty()) {
                FD_SET(tunfd, &rset);
                if(tunfd > maxfd) maxfd = tunfd;
            }
            
            ret = select(maxfd + 1, &rset, &wset, NULL, NULL);
            if(ret == -1 && errno != EINTR) {
                err(1, "select");
            } else if(ret > 0) {
                if(FD_ISSET(slipfd, &rset)) {
                    serial_to_tun(inslip, tunfd);
                }
                
                if(FD_ISSET(slipfd, &wset)) {
                    slip_flushbuf(slipfd);
                    sigalarm_reset();
                }
                
                if(slip_empty() && FD_ISSET(tunfd, &rset)) {
                    tun_to_serial(tunfd, slipfd);
                    slip_flushbuf(slipfd);
                    sigalarm_reset();
                }
            }
            
        }       
    }
/*********************************************************************************/
}


const struct device_class device_tapslip = {
	.name		= "tapslip",
	.help       = "TAPSLIP application via RS-232",
	.open		= tapslip_open,
	.destroy	= NULL, //tapslip_destroy,
	.readmem	= NULL, //tapslip_readmem,
	.writemem	= NULL, //tapslip_writemem,
	.getregs	= NULL, //tapslip_getregs,
	.setregs	= NULL, //tapslip_setregs,
	.ctl		= NULL, //tapslip_ctl,
	.poll		= NULL, //tapslip_poll,
	.erase		= NULL, //tapslip_erase
};
