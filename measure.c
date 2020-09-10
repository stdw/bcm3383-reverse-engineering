#include "lib.h"

#define SAMPLES 2000000
int __start(void)
{
	int* buf = (int*) malloc(SAMPLES*4);
	if(!buf)
		return -1;
	memset(buf, 0, SAMPLES*4);
	set_channel_freq(95900000, 5, 1);
	int i;
	int* p = (int*)0xb3c19010;
	printf("start\n");
	timer_start((void*)0x80800000);
	for (i = 0; i < SAMPLES; i++) {
		buf[i] = p[0];
	}
	timer_stop((void*)0x80800000);
	printf("done\n");


	void* sock;
	void* conn;
	sock_addr_t sa = {0};
	int n = 1;

	if (NULL == (sock = socket(AF_INET, 1, 6, 2)))
		return -1;
	//printf("sock %x\n", sock);	

	sa.addr = 0xc0a86401; // set ip address to 192.168.100.1
	//printf("addr: 0x%x\n", addr);
	if (0 != bind(sock, &sa, 1337))
		return -2;

	if (0 != listen(sock, 1))
		return -3;

	if (NULL == (conn = accept(sock, 0, 0)))
		return -4;

	int remaining = SAMPLES*4;
	int chunk_size = 1024;
	int chunk_sent = 0;
	char* start = (char*)buf;
	while (remaining > 0) {
		chunk_sent = 0;
		if (remaining < chunk_size)
			chunk_size = remaining;

		while (chunk_sent < chunk_size && n > 0) {
			n = send(conn, start, chunk_size - chunk_sent, 0);
			chunk_sent += n;
			start += n;
		}
		if (n <= 0) {
			printf("error sending: %d\n", n);
			return n;		
		}
		printf("sent %d\n", chunk_size);
		remaining -= chunk_size;
	}
	printf("sent %d bytes total\n", SAMPLES*4 - remaining);
	return (int)buf;
}
