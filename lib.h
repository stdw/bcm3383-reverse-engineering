void* memset(void* buf, int c, unsigned int n);
void* memcpy(void* dst, const void* src, int n);
void* malloc(unsigned int size);
int printf(char* str, ...);

void* socket(int ip_proto, int a, int b, int ip_stack);
int bind(void* handle, void* addr, int port);
int listen(void* handle, int a);
void* accept(void* handle, int a, int b);
int send(void* handle, char* buf, int len, int a);
int recv(void* handle, char* buf, int len, int a);

int new_addr(int a);
int addr_cpy(int dst, int src);

#define NULL (void*) 0

// Network
#define AF_INET  0x02
#define AF_INET6 0x1C
