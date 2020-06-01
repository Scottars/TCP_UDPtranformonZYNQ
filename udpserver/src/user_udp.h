/*
 * usr_udp.h
 *
 *  Created on: 2020Äê1ÔÂ16ÈÕ
 *      Author: Scottar
 */


#ifndef SRC_USER_UDP_H_
#define SRC_USER_UDP_H_

#include "lwip/err.h"
#include "lwip/udp.h"
#include "lwip/init.h"
#include "lwipopts.h"
#include "lwip/err.h"
#include "lwipopts.h"
#include "netif/xadapter.h"
#include "xil_printf.h"

int user_udp_init(void);
//void udp_printf(void);
void udp_printf(float data);
void udp_senddata(int data);

#endif /* SRC_USER_UDP_H_ */
