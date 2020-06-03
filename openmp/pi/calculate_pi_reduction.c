#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#include<stdint.h>
#include<time.h>

uint32_t __GetTickCount(void) {
	struct timespec ts;
	uint32_t tick = 0U;
	clock_gettime(CLOCK_REALTIME, &ts);
	tick = ts.tv_nsec / 1000000;
	tick += ts.tv_sec * 1000;
	return tick;
}

double fx(double a, double interval, int i) {
	return (a + i*interval) * (a + i*interval);
}

void PI(double a, double b, int numIntervals, double* global_result_p) {
	int i;
	double x, my_result, sum = 0.0, interval, local_a, local_b, local_numIntervals;
	int myThread = omp_get_thread_num();
	int numThreads = omp_get_num_threads();
	
	interval = (b-a)/ (double) numIntervals;
	local_numIntervals = numIntervals/numThreads; 
	local_a = a + myThread*local_numIntervals*interval; 
	local_b = local_a + local_numIntervals*interval; 
	sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
	for (i = 0; i < local_numIntervals; i++) {
			x = local_a + i*interval;
			sum +=  4.0 / (1.0 + x*x);
			//sum += 4.0 / (1.0 + fx(local_a, interval, i));
	}
	my_result = interval * sum;
	
//#pragma omp critical 
	*global_result_p += my_result; 
}

int main(int argc, char** argv) {
	double global_result = 0.0;
	volatile uint32_t dwStart;

	if (argc < 2) {
		fprintf(stderr, "argerr\n");
		return 1;
	}

	int n = 100000000;
  printf("numberInterval %d \n", n);
	int numThreads = strtol(argv[1], NULL, 10);
	dwStart = __GetTickCount();
#pragma omp parallel num_threads(numThreads) 
	PI(0, 1, n, &global_result); 
	
	printf("number of threads %d \n", numThreads);
	printf("Pi = %f \n", global_result);
	printf("milliseconds %d \n", __GetTickCount() - dwStart);
}
