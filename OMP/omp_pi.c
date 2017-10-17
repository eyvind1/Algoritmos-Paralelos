#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> 



int main(int argc, char* argv[]) {
   long long n, i;
   int thread_count;
   double factor;
   double sum = 0.0;
   thread_count = strtol(argv[1], NULL, 10);
   n = 100;

#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: sum) private(factor)
   for (i = 0; i < n; i++) {
      factor = (i % 2 == 0) ? 1.0 : -1.0; 
      sum += factor/(2*i+1);
#     ifdef DEBUG
      printf("Thread %d > i = %lld, my_sum = %f\n", my_rank, i, my_sum);
#     endif
   }

   sum = 4.0*sum;
   printf("Con n = %lld terminos y %d threads,\n", n, thread_count);
   printf("   Estimado de pi = %.14f\n", sum);
   printf("                   pi = %.14f\n", 4.0*atan(1.0));
   return 0;
}  

