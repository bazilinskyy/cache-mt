#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <inttypes.h>
#include <cpuid.h>
#include <errno.h>

uint64_t rdtsc();

//TODO check flags for formatting of printfs
int main(int argc, const char ** argv) {
	int k;

	printf("Control experiment for latency of registers. A tempo variable is putputted to avoid compiler optimisation.\n");

	printf("Int\n");
	for (k = 0; k < 10; ++k) {
		register int x = 10;
		int z = 10;
		int y = 0;
		unsigned long long time1, time2;
		usleep(100); // To wait until the process is scheduled
		time1 = rdtsc();
		x = y;
		time2 = rdtsc();
		printf("R: %d. %llu %d\n", k, time2 - time1, x);

		time1 = rdtsc();
		x = z;
		time2 = rdtsc();
		printf("N: %d. %llu %d\n", k, time2 - time1, x);
	}

	printf("Double\n");
	for (k = 0; k < 10; ++k) {
		register double x = 10;
		double z = 10;
		double y = 0;
		unsigned long long time1, time2;
		usleep(100); // To wait until the process is scheduled
		time1 = rdtsc();
		x = y;
		time2 = rdtsc();
		printf("R: %d. %llu %f\n", k, time2 - time1, x);

		time1 = rdtsc();
		x = z;
		time2 = rdtsc();
		printf("N: %d. %llu %f\n", k, time2 - time1, x);
	}

	printf("Long\n");
	for (k = 0; k < 10; ++k) {
		register long x = 10l;
		long z = 10l;
		long y = 0l;
		unsigned long long time1, time2;
		usleep(100); // To wait until the process is scheduled
		time1 = rdtsc();
		x = y;
		time2 = rdtsc();
		printf("R: %d. %llu %lu\n", k, time2 - time1, x);

		time1 = rdtsc();
		x = z;
		time2 = rdtsc();
		printf("N: %d. %llu %lu\n", k, time2 - time1, x);

	}

	printf("Long Long\n");
	for (k = 0; k < 10; ++k) {
		register long long x = 10ll;
		long long z = 10ll;
		long long y = 0ll;
		unsigned long long time1, time2;
		usleep(100); // To wait until the process is scheduled
		time1 = rdtsc();
		x = y;
		time2 = rdtsc();
		printf("R: %d. %llu %llu\n", k, time2 - time1, x);

		time1 = rdtsc();
		x = z;
		time2 = rdtsc();
		printf("N: %d. %llu %llu\n", k, time2 - time1, x);
	}
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
