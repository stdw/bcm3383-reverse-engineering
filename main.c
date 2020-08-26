#define PRINTF_ADDR 0x8052b178

typedef void printf_t(char* str, ...);
typedef int socket_t(int ip_proto, int a, int b, int ip_stack);
typedef int new_addr_t(int a);
typedef int bind_t(int handle, int addr, int port);
typedef int addr_cpy_t(int dst, int src);

int __start(void)
{
	printf_t *printf = (printf_t*) PRINTF_ADDR;
	socket_t *socket = (socket_t*) 0x80332fd0;
	new_addr_t *new_addr = (new_addr_t*) 0x8013df20;
	bind_t *bind = (bind_t*) 0x800ae7bc;
	addr_cpy_t *addr_cpy = (addr_cpy_t*) 0x800186b4;

	int sock = 0;
	int addr = 0;
	//printf("HELLO WORLD %d\n", 1234);
	//sock = socket(2, 2, 0x11, 2);
	sock = socket(2, 1, 6, 2);
	//printf("socket: 0x%x\n", sock);
	int* a = 0x80800000;
	//a[2] = 1;
	a[114] = 2; // ip stack
	addr = new_addr(0x80800000);
	//printf("addr: 0x%x\n", addr);
	addr_cpy(0x80800000, addr);
	//printf("addr: 0x%x\n", addr);
	//addr[9] = 1; //
	//bind(sock, 0x80800000, 1337);

	return 123;
}
