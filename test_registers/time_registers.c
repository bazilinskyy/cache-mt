#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <inttypes.h>
#include <cpuid.h>
#include <errno.h>

uint64_t rdtsc();

int main(int argc, const char ** argv) {
	int k;
	register long x = 10;
	long y = 0;
	printf("Test with registers\n");
	for (k = 0; k < 100; ++k) {
		unsigned long long time1, time2;
		usleep(100); // To wait until the process is scheduled
		time1 = rdtsc();
		x = y;
		time2 = rdtsc();
		printf("%d. %llu\n", k, time2 - time1);
	}
	return x; // Return x to trick the compiler optimizer.
}

uint64_t rdtsc() {
	uint32_t lo, hi;
	/* We cannot use "=A", since this would use %rax on x86_64 */
	asm volatile (
			/*"CPUID\n\t"serialize*/
			"RDTSC\n\t"/*read the clock*/
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t": "=r" (hi), "=r"
			(lo):: "%rax", "%rbx", "%rcx", "%rdx");
	return (uint64_t) hi << 32 | lo;
}
