#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

static long num_steps = 10000000;
double step;
#define NUM_THREADS 4

void main()
{	
	for (int j = NUM_THREADS - 1; j >= 0; j--) {
		int i, numthreads; double pi, sum[NUM_THREADS];
		step = 1.0 / (double)num_steps;
		double runtime = omp_get_wtime();
		omp_set_num_threads(NUM_THREADS - j);
		#pragma omp parallel
		{
			int i, id, nthreads;
			double x;
			id = omp_get_thread_num();
			nthrds = omp_get_num_threads();
			if (id == 0) numthreads = nthreads;
		#pragma omp parallel for reduction(+:sum)
			for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthreads) {
				x = (i + 0.5) * step;
				sum[id] += 4.0 / (1.0 + x * x);
			}
		}
		for (i = 0, pi = 0.0; i < numthreads; i++)
			pi += sum[i] * step;
		runtime = omp_get_wtime() - runtime;
		printf("pi = % f in % f secs with % d threads\n", pi, runtime, (NUM_THREADS - j));
	}
  return;
}
