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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#include "debug.h"
#include "util.h"
#include "output.h"
#include "fet_error.h"
#include "sport.h"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

#include <sys/ioctl.h>

#define BAUDRATE B115200
#define BAUDRATE_S "115200"
#define MODEMDEVICE "/dev/ttyS0"

#ifdef __linux__
#include <linux/serial.h>
#endif

#define SLIP_END     0300
#define SLIP_ESC     0333
#define SLIP_ESC_END 0334
#define SLIP_ESC_ESC 0335

#define CSNA_INIT 0x01

#define BUFSIZE 40
#define HCOLS 20
#define ICOLS 18

#define MODE_START_DATE 0
#define MODE_DATE   1
#define MODE_START_TEXT 2
#define MODE_TEXT   3
#define MODE_INT    4
#define MODE_HEX    5
#define MODE_SLIP_AUTO  6
#define MODE_SLIP   7
#define MODE_SLIP_HIDE  8

static unsigned char rxbuf[2048];

#define SPORT_EVEN_PARITY   0x01
#define SPORT_ISERR(x) ((x) < 0)


static device_t debug_open(const struct device_args *args)
{
    struct termios options;
    fd_set mask, smask;
    int fd;
    speed_t speed = BAUDRATE;
    char *speedname = BAUDRATE_S;
    char *device = MODEMDEVICE;
    char *timeformat = "%Y-%m-%d %H:%M:%S";
    unsigned char buf[BUFSIZE], outbuf[HCOLS];
    unsigned char mode = MODE_START_TEXT;
    int nfound, flags = 0;
    unsigned char lastc = '\0';

    int index = 0;

    printf("--------------------------------------------\n");
    printf("Debug application via RS-232 at 115200 Baud-rate\n");
    printf("  Use: TX and RX pins for UART\n");
    printf("  Exit: Ctrl+C\n");
    printf("--------------------------------------------\n");

    #include "ctrlc.h"
    ctrlc_exit();

    device = args->path;
    // fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_DIRECT | O_SYNC );  // ORIGINAL
    fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC );
    if (fd <0) {
        fprintf(stderr, "\n");
        perror(device);
        exit(-1);
    }

/*******************************************************************************/
    // IMPORTANT:  Reset the micro  before DEBUG is starting
    if (sport_set_modem(fd, ~ SPORT_MC_DTR) != 0) {
        return NULL;
    }
    delay_ms(50);

/*******************************************************************************/

    if (fcntl(fd, F_SETFL, 0) < 0) {
        perror("could not set fcntl");
        exit(-1);
    }

    if (tcgetattr(fd, &options) < 0) {
        perror("could not get options");
        exit(-1);
    }
    /*   fprintf(stderr, "serial options set\n"); */
    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);
    /* Enable the receiver and set local mode */
    options.c_cflag |= (CLOCAL | CREAD);
    /* Mask the character size bits and turn off (odd) parity */
    options.c_cflag &= ~(CSIZE|PARENB|PARODD);
    /* Select 8 data bits */
    options.c_cflag |= CS8;
    
    /* Raw input */
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    /* Raw output */
    options.c_oflag &= ~OPOST;
    
    if (tcsetattr(fd, TCSANOW, &options) < 0) {
        perror("could not set options");
        exit(-1);
    }


  /* Make read() return immediately */
/*    if (fcntl(fd, F_SETFL, FNDELAY) < 0) { */
/*      perror("\ncould not set fcntl"); */
/*      exit(-1); */
/*    } */

  FD_ZERO(&mask);
  FD_SET(fd, &mask);
  FD_SET(fileno(stdin), &mask);


  index = 0;
  for (;;) {
//      fprintf(stderr, ".");
      smask = mask;
      nfound = select(FD_SETSIZE, &smask, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0); 
      if(nfound < 0) {
          if (errno == EINTR) {
              fprintf(stderr, "interrupted system call\n");
              continue;
          }
          /* something is very wrong! */
          perror("select");
          exit(1);
      }
      
      if(FD_ISSET(fileno(stdin), &smask)) {
          // data from standard in 
          int n = read(fileno(stdin), buf, sizeof(buf));
          if (n < 0) {
              perror("could not read");
              exit(-1);
          } else if (n > 0) {
              // because commands might need parameters, lines needs to be
              // separated which means the terminating LF must be sent 
              // 	while(n > 0 && buf[n - 1] < 32) { 
              // 	  n--; 
              // 	} 
              if(n > 0) {
                  int i;
                  fprintf(stderr, "SEND %d bytes\n", n);
                  // write slowly 
                  for (i = 0; i < n; i++) {

                      if (write(fd, &buf[i], 1) <= 0) {
                          perror("write");
                          exit(1);
                      } else {
                          fflush(NULL);
                          usleep(6000);
                      }
                  }
              }
          } else {
              // End of input, exit. 
              exit(0);
          }
      }


      if(FD_ISSET(fd, &smask)) {
          int i, n = read(fd, buf, sizeof(buf));
          if (n < 0) {
              perror("could not read");
              exit(-1);
          }
          
          for(i = 0; i < n; i++) {
              switch(mode) {
                  case MODE_START_TEXT:
                  case MODE_TEXT:
                      printf("%c", buf[i]);
                      break;
                  case MODE_START_DATE: 
                      {
                          time_t t;
                          t = time(&t);
                          strftime(outbuf, HCOLS, timeformat, localtime(&t));
                          printf("%s|", outbuf);
                          mode = MODE_DATE;
                      }
                      /* continue into the MODE_DATE */
                  case MODE_DATE:
                      printf("%c", buf[i]);
                      if(buf[i] == '\n') {
                          mode = MODE_START_DATE;
                      }
                      break;
                  case MODE_INT:
                      printf("%03d ", buf[i]);
                      if(++index >= ICOLS) {
                          index = 0;
                          printf("\n");
                      }
                      break;
                  case MODE_HEX:
                      rxbuf[index++] = buf[i];
                      if(index >= HCOLS) {
                          print_hex_line("", rxbuf, index);
                          index = 0;
                          printf("\n");
                      }
                      break;
                      
                  case MODE_SLIP_AUTO:
                  case MODE_SLIP_HIDE:
                      if(!flags && (buf[i] != SLIP_END)) {
                          /* Not a SLIP packet? */
                          printf("%c", buf[i]);
                          break;
                      }
                      /* continue to slip only mode */
                  case MODE_SLIP:
                      switch(buf[i]) {
                          case SLIP_ESC:
                              lastc = SLIP_ESC;
                              break;
                              
                          case SLIP_END:
                              if(index > 0) {
                                  if(flags != 2 && mode != MODE_SLIP_HIDE) {
                                      /* not overflowed: show packet */
                                      print_hex_line("SLIP: ", rxbuf,
                                              index > HCOLS ? HCOLS : index);
                                      printf("\n");
                                  }
                                  lastc = '\0';
                                  index = 0;
                                  flags = 0;
                              } else {
                                  flags = !flags;
                              }
                              break;
                              
                          default:
                              if(lastc == SLIP_ESC) {
                                  lastc = '\0';
                                  
                                  /* Previous read byte was an escape byte, so this byte will be
                                   * 		 interpreted differently from others. */
                                  switch(buf[i]) {
                                      case SLIP_ESC_END:
                                          buf[i] = SLIP_END;
                                          break;
                                      case SLIP_ESC_ESC:
                                          buf[i] = SLIP_ESC;
                                          break;
                                  }
                              }
                              
                              rxbuf[index++] = buf[i];
                              if(index >= sizeof(rxbuf)) {
                                  fprintf(stderr, "**** slip overflow\n");
                                  index = 0;
                                  flags = 2;
                              }
                              break;
                      }
                      break;
                  default:
                      fprintf(stderr, "**** wrong mode\n");
              }
          }
          
          /* after processing for some output modes */
          if(index > 0) {
              switch(mode) {
                  case MODE_HEX:
                      print_hex_line("", rxbuf, index);
                      break;
              }
          }
          fflush(stdout);
      }
  }
  
}

const struct device_class device_debug = {
	.name		= "debug",
	.help = "Debug application via RS-232",
	.open		= debug_open,
	.destroy	= NULL,  //debug_destroy,
	.readmem	= NULL,  //debug_readmem,
	.writemem	= NULL,  //debug_writemem,
	.getregs	= NULL,  //debug_getregs,
	.setregs	= NULL,  //debug_setregs,
	.ctl		= NULL,  //debug_ctl,
	.poll		= NULL,  //debug_poll,
	.erase		= NULL,  //debug_erase
};
