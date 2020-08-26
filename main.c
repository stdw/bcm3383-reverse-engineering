#define PRINTF_ADDR 0x8052b178

typedef void printf_t(char* str, ...);
typedef int socket_t(int ip_proto, int a, int b, int ip_stack);
typedef int new_addr_t(int a);
typedef int bind_t(int handle, int addr, int port);
typedef int addr_cpy_t(int dst, int src);
typedef int listen_t(int handle, int a);
typedef int accept_t(int handle, int a, int b);
typedef int recv_t(int handle, int buf, int len, int a);

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

	int sock = 0;
	int addr = 0;
	sock = socket(2, 1, 6, 2);
	//printf("socket: 0x%x\n", sock);
	int* a = (int*) 0x80800000;
	//a[114] = 2; // set ip stack
	//addr = new_addr(0x80800000);
	//printf("addr: 0x%x\n", addr);
	a[2] = 0xc0a86401;
	//addr_cpy(0x80800000, addr);
	//printf("addr: 0x%x\n", addr);
	bind(sock, 0x80800000, 1337);
	listen(sock, 1);
	int conn = accept(sock, 0, 0);
	recv(conn, 0x80800000, 1024, 0);
	printf("%s\n", 0x80800000);
	return conn;
}
