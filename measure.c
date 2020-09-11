#include "lib.h"

#define SAMPLES 10000
#define FREQ 	96000000
#define BW 	7500000 /* Assuming because it uses 7.5Mhz bins? */
#define HALFBW 	3750000

int __start(void)
{
	int bandpower[4];
	int* buf = (int*) malloc(SAMPLES*8);
	if(!buf)
		return -1;

	/* RAM is mapped to addresses 0x80000000 and 0xA0000000
	 * The latter is not cached and we get mostly zeros if we use
	 * the 0x80000000 address even though the function looks to be
	 * converting it interally too. So pass a 0xA0000000 address
	 */
	buf = (int*)((int)buf | 0x20000000);
	memset(buf, 0, SAMPLES*8);

	printf("buffer: 0x%x\n", buf);

	/* The last argument is the buffer to use for samples used to
	 * calculate the FFT. 2nd to last arg is the number of 8 byte
	 * samples. The samples are passed to a function that pulls
	 * out the first and second 32-bit words separately. These
	 * values are positive and negative integers centered around 0. 
	 * Seems logical that it is I/Q data?
	 */
	sample_bandpower(FREQ-HALFBW, FREQ+HALFBW, 128, (void*)&bandpower, SAMPLES, buf);

	void* sock;
	void* conn;
	sock_addr_t sa = {0};
	int n = 1;

	if (NULL == (sock = socket(AF_INET, 1, 6, 2)))
		return -1;

	sa.addr = 0xc0a86401; // set ip address to 192.168.100.1
	if (0 != bind(sock, &sa, 1337))
		return -2;

	if (0 != listen(sock, 1))
		return -3;

	if (NULL == (conn = accept(sock, 0, 0)))
		return -4;

	int remaining = SAMPLES*8;
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
		remaining -= chunk_size;
	}
	printf("sent %d bytes total\n", SAMPLES*8 - remaining);
	return (int)buf;
}
