#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <inttypes.h>
#include <cpuid.h>
#include <errno.h>

unsigned long long search_in_file(char *f, char *str, int find_numeric);
unsigned long long find_num_in_str(char *str);
uint64_t rdtsc();

int main(int argc, const char ** argv) {
	int k;
	long sum;
	for (k = 0; k < 10; ++k) {

		unsigned long long time1, time2, timeInt1, timeInt2;
		int n = 1;
		int i;
		usleep(100); // To wait until the process is scheduled
		time1 = rdtsc();
		timeInt1 = search_in_file("/proc/interrupts", "LOC", 1);
		timeInt2 = search_in_file("/proc/interrupts", "LOC", 1);
		while (timeInt2 - timeInt1 == 0) {
			n *= 2;
			for (i = 0; i < n; i++) {
				sum += i;
			}
			time2 = rdtsc();
			timeInt2 = search_in_file("/proc/interrupts", "LOC", 1);

		}
		printf("%d - %llu\n", n, time2 - time1);

	}
	return sum;
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

unsigned long long search_in_file(char *f, char *str, int find_numeric) {
	FILE *fp;
	char temp[512];

	// Open file.
	if ((fp = fopen(f, "r")) == NULL) {
		printf("Error: unable to open %s: %s\n", f, strerror(errno));
		return (-1);
	}

	// Search for str and extract numeric.
	while (fgets(temp, 512, fp) != NULL) {
		if ((strstr(temp, str)) != NULL) {
			if (find_numeric) {
				unsigned long long number = find_num_in_str(temp);
				if (fp) {
					fclose(fp);
				}
				return number;
			} else {
				printf("A match found\n.");
				printf("\n%s\n", temp);
			}
		}
	}

	//Close the file if still open.
	if (fp) {
		fclose(fp);
	}
	return (0);
}

// Find a numeric in a string
unsigned long long find_num_in_str(char *str) {
	unsigned long long num = -1;
	sscanf(str, "%*[^0-9]%llu", &num);
	//printf("%s\n", str);
	return num;
}
