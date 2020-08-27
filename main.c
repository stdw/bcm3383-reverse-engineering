#include "lib.h"

int __start(void)
{
	void* sock;
	void* conn;
	int addr[5] = {0};
	int n;
	char* buf = malloc(512);
	memset(buf, 0, 512);

	if (NULL == (sock = socket(2, 1, 6, 2)))
		return -1;
	//printf("sock %x\n", sock);	

	addr[2] = 0xc0a86401; // set ip address
	//printf("addr: 0x%x\n", addr);
	if (0 != bind(sock, addr, 1338)) 
		return -2;

	if (0 != listen(sock, 1))
		return -3;

	if (NULL == (conn = accept(sock, 0, 0)))
		return -4;

	n = recv(conn, buf, 511, 0);
	if (n <= 0)
		return -5;

	printf("%s\n", buf);

	char resp[] = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: 5\r\n\r\nHello";
	n = send(conn, resp, sizeof(resp), 0);

	return 0;
}
