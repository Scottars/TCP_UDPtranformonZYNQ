#include "user_udp.h"

//---------------------------------------------------------
//                    变量定义
//---------------------------------------------------------
struct udp_pcb *connected_pcb = NULL;
static struct pbuf *pbuf_to_be_sent = NULL;
char *send_buff = "helloWorld";  //待发送字符
int *send_buffint = 100;
struct ip_addr ipaddr;

static unsigned local_port = 5002;      //本地端口
static unsigned remote_port = 8080;  //远程端口
typedef union
{
    float floatData;
    unsigned char byteData[4];
//  uint32_t byteData;
} FLOAT_BYTE;
//---------------------------------------------------------
//                  UDP连接初始化函数
//---------------------------------------------------------
int user_udp_init(void)
{
	struct udp_pcb *pcb;
	err_t err;

	/*  创建UDP控制块   */
	pcb = udp_new();
	if (!pcb) {
		xil_printf("Error Creating PCB.\r\n");
		return -1;
	}
	/*  绑定本地端口   */
	err = udp_bind(pcb, IP_ADDR_ANY, local_port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d\r\n", local_port);
		return -2;
	}
	/*  设置远程地址   */
	IP4_ADDR(&ipaddr, 192, 168, 127, 201);
//	IP4_ADDR(&ipaddr, 192, 168, 1, 101);
//	IP4_ADDR(&ipaddr, 115, 156, 162, 123);
//	IP4_ADDR(&ipaddr, 115, 156, 162, 76);
	connected_pcb = pcb;

	/*  申请pbuf资源  */
	pbuf_to_be_sent = pbuf_alloc(PBUF_TRANSPORT, 10, PBUF_ROM);
	memset(pbuf_to_be_sent->payload, 0, 10);
//	memcpy(pbuf_to_be_sent->payload, (u8 *)send_buff, 4);

	return 0;
}

//---------------------------------------------------------
//                   UDP发送数据函数
//---------------------------------------------------------
void udp_printf(float data)
{
	err_t err;
	struct udp_pcb *tpcb = connected_pcb;
	if (!tpcb) {
		xil_printf("error connect.\r\n");
	}
//
//	send_buff[0] ='0';
//	send_buff[1] = '1';
//	send_buff[2] = '2';
//	send_buff[3] = '3';
//	send_buff[4] = '4';
//	send_buff[5] = '5';
//	send_buff[6] = '6';
//	send_buff[7] = '7';
//	send_buff[8] = '8';
//	send_buff[9] = '9';


//	*send_buff = "hellod6789";
//	*send_buff = data;
	FLOAT_BYTE testdata;
	testdata.floatData=data;
	send_buff[0]=0x11; // Slave address
	send_buff[1]=0x03;// function  code
	send_buff[2]=0x01;// register address
	send_buff[3]=0x04;//length of data
	send_buff[4]=testdata.byteData[3];
	send_buff[5]=testdata.byteData[2];
	send_buff[6]=testdata.byteData[1];
	send_buff[7]=testdata.byteData[0];
	send_buff[8]='c';
	send_buff[8]='r';


//	memset(pbuf_to_be_sent->payload, 0, 10);
	memcpy(pbuf_to_be_sent->payload, (u8 *)send_buff, 10);

	/*  发送字符串  */
	err = udp_sendto(tpcb, pbuf_to_be_sent, &ipaddr, remote_port);
	if (err != ERR_OK) {
//		xil_printf("Error on udp send : %d\r\n", err);
		return;
	}
}
void udp_senddata(int data)
{
	err_t err;
	struct udp_pcb *tpcb = connected_pcb;
	if (!tpcb) {
		xil_printf("error connect.\r\n");
	}
//	data =100;

	*send_buffint = data;
	memcpy(pbuf_to_be_sent->payload, send_buffint, 2);

	xil_printf("we are sending here:%d\r\n",*send_buffint);

	/*  发送字符串  */
	err = udp_sendto(tpcb, pbuf_to_be_sent, &ipaddr, remote_port);
	if (err != ERR_OK) {
//		xil_printf("Error on udp send : %d\r\n", err);
		return;
	}
}
