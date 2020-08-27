#define PRINTF_ADDR 0x8052b178

//typedef void* memcpy_t(void* dst, const void* src, int n);
typedef int printf_t(char* str, ...);
typedef int socket_t(int ip_proto, int a, int b, int ip_stack);
typedef int new_addr_t(int a);
typedef int bind_t(int handle, int addr, int port);
typedef int addr_cpy_t(int dst, int src);
typedef int listen_t(int handle, int a);
typedef int accept_t(int handle, int a, int b);
typedef int recv_t(int handle, int buf, int len, int a);
typedef int send_t(int handle, char* buf, int len, int a);


void* memcpy(void* dst, const void* src, int n);

#define BASE 0x80800000

//memcpy_t *memcpy_p = (memcpy_t*) 0x80004f30;

int __start(void)
{
	printf_t *printf = (printf_t*) PRINTF_ADDR;
	socket_t *socket = (socket_t*) 0x80332fd0;
	new_addr_t *new_addr = (new_addr_t*) 0x8013df20;
	bind_t *bind = (bind_t*) 0x800ae7bc;
	addr_cpy_t *addr_cpy = (addr_cpy_t*) 0x800186b4;
	listen_t *listen = (listen_t*) 0x80412ed4;
	accept_t *accept = (accept_t*) 0x80413118;
	recv_t *recv = (recv_t*) 0x804134bc;
	send_t *send = (send_t*) 0x80413240;

	int sock;
	int conn;
	int* addr = (int*) BASE;
	int n;

	if (0 == (sock = socket(2, 1, 6, 2)))
		return -1;
	printf("sock %x\n", sock);	
	//a[114] = 2; // set ip stack
	//addr = new_addr(0x80800000);
	//printf("addr: 0x%x\n", addr);
	addr[2] = 0xc0a86401;
	//addr_cpy(0x80800000, addr);
	//printf("addr: 0x%x\n", addr);
	if (0 != bind(sock, BASE, 1337)) 
		return -2;
	//printf("bind\n");

	if (0 != listen(sock, 1))
		return -3;
	//printf("listen\n");

	if (0 == (conn = accept(sock, 0, 0)))
		return -4;
	//printf("acc\n");

	n = recv(conn, BASE, 512, 0);
	if (n <= 0)
		return -5;

	printf("%s\n", BASE);

	char resp[] = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: 5\r\n\r\nHello";
	n = send(conn, resp, sizeof(resp), 0);
	printf("sent %d\n", n);

	return conn;
}
