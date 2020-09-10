/* constants */
#define NULL (void*) 0

#define AF_INET  0x02
#define AF_INET6 0x1C


/* structs */

typedef struct sock_addr_s {
	unsigned int _pad1;
	unsigned int _pad2;
	unsigned int addr;
	unsigned int _pad4;
	unsigned int _pad5;
	unsigned int _pad6;
	unsigned int _pad7;
	unsigned int _pad8;
} sock_addr_t;



/* stdlib functions */
void* memset(void* buf, int c, unsigned int n);
void* memcpy(void* dst, const void* src, int n);
void* malloc(unsigned int size);
int printf(char* str, ...);
void sleep_ms(unsigned int);


/* network functions */

/* Create a new socket with IP protocol ip_proto on IP stack number ip_stack
 * _a and _b are unknown, use 1 and 6 respectively for IPv4 TCP.
 * Returns NULL on failure and pointer to socket handle on success. 
 */
void* socket(int ip_proto, int _a, int _b, int ip_stack);

/* Bind the valid socket handle to the given address and port. 
 * Returns 0 on success. 
 */
int bind(void* handle, void* addr, int port);

/* Listen for a TCP connection on the bound socket. 
 * Arg _a is unknown, probably backlog like posix listen(). Use 1.
 * Returns 0 on success.
 */
int listen(void* handle, int _a);

/* Accept a connection on a listening socket. 
 * Args _a and _b are unknown, use 0 and 0 respectively.
 * Returns a pointer to a new socket handle on success or NULL on failure.
 */
void* accept(void* handle, int _a, int _b);

/* Send len bytes of data at the buffer buf on the connection handle.
 * Arg _a is unknown, use 0.
 * Returns the number of bytes send on success.
 */
int send(void* handle, char* buf, int len, int _a);

/* Read up to len bytes of data from the connection handle into buffer buf.
 * Arg _a is unknown, use 0.
 * Returns the number of bytes read on success.
 */
int recv(void* handle, char* buf, int len, int _a);

int new_addr(int a);
int addr_cpy(int dst, int src);



/* transceiver functions */

/* Write the given value to the given LNA register.
 */
void write_lna_reg(unsigned int reg, unsigned int val);

/* Read the given LNA register.
 * Returns the value read.
 */
unsigned int read_lna_reg(unsigned int reg);

/* Write a value to the given tuner register.
 * buf is a pointer to a 64 byte buffer
 * The value to write must be set in buf at offset reg.
 * reg is the register number/offset in buf to start from 
 * size is the number of bytes to write
 * _a is unknown?
 */
int write_tuner_reg(void* buf, unsigned int reg, unsigned int size, unsigned int _a);

/* Read size bytes into buf from the tuner register reg.
 */
void read_tuner_reg(int reg, void* buf, unsigned int size);

/* Return/print the downstream power measurement (DPM) for the given channel.
 */
int get_channel_dpm(int channel);

/* Sample the bandpower between start_freq and stop_freq using points samples
 * to the buffer buf.
 * Args _a and _b unknown, use 0 and 0 respectively.
 */
int sample_bandpower(unsigned int start_freq, unsigned int stop_freq, int points, int* out, int _a, int _b);

/* Set the given channel to the given freqency in Hz.  
 * Arg _a unknown, use 0 or 1.
 */
int set_channel_freq(unsigned int freq, int channel, int _a);



/* misc functions */

/* Not actually its primary purpose but it prints the elapsed time in
 * microseconds.
 */
void timer_start(int* t);
void timer_stop(int* t);

