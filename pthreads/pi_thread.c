#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

      
#define NUM_THREADS  1              

long   mytotal;                     

int main(int argc, char *argv[])
{

   int        i;
   int        nthreads;                     
   long       total;                         
   pthread_t  thread_id[NUM_THREADS];        
   long       totalhits = 0;                 
   double     pi;                            
   void *     myhits_p;
   void *     calc(void *);                  

   nthreads = NUM_THREADS;   

   mytotal = (long) ceil(total/nthreads);
   total = nthreads * mytotal;              
   
  
   for (i=0; i<nthreads; i++) {
     pthread_create(&thread_id[i], NULL, calc, NULL);
   }   

  
   for (i=0; i<nthreads; i++) {
     pthread_join(thread_id[i], &myhits_p);
     totalhits +=  * (long *)myhits_p;
   }   
   
  
   pi = totalhits/(double)total*4;
   printf("\nPI = %lf\n", pi);
}




void * calc(void *args)
{
   
   double  x, y;                     
   long *  hits_p;                   
   int     seed;                    
   long    i;
   
   hits_p = (long *) calloc(1, sizeof(long));      

   
   seed = (int) pthread_self();
   for(i=0; i<mytotal; i++)
   {
      x = ((double) myrand_r(&seed))/RAND_R_MAX;
      y = ((double) myrand_r(&seed))/RAND_R_MAX;
      
      if ( x*x + y*y <= 1.0 )
      {
	 (*hits_p)++;
      }
   }

   return(hits_p); 
}