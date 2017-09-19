#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MAX_CONTRIB 20

int suma_global(int my_contrib, int my_rank, int p, MPI_Comm comm) {
   int sum = my_contrib;
   int temp;
   int divisor = 2;
   int proc_diff = 1;
   int partner;
   int done = 0;
   int i_send;

   while (!done && divisor <= smallest_power_two(p)) {
      i_send = my_rank % divisor;
      if (i_send) {
         partner = my_rank - proc_diff;
         MPI_Send(&sum, 1, MPI_INT, partner, 0, comm); 
         done = 1;
      } else {  
         partner = my_rank + proc_diff;
         if (partner < p) {
            MPI_Recv(&temp, 1, MPI_INT, partner, 0, comm,MPI_STATUS_IGNORE);
            sum += temp;
         }
         divisor *= 2;
         proc_diff *= 2;
      }
   }


   return sum;
} 


int smallest_power_two(int p) {
   int temp = 1;

   while (temp < p) 
      temp *= 2;
   return temp;
}

int main() {
   int p, my_rank;
   MPI_Comm comm;
   int x;
   int total;

   MPI_Init(NULL, NULL);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   srandom(my_rank);
   x = random() % MAX_CONTRIB;
   printf("Proceso %d > x = %d, p = %d\n", my_rank, x, p);

   total = suma_global(x, my_rank, p, comm);

   if (my_rank == 0)
      printf("Total %d\n", total);

   MPI_Finalize();
   return 0;
} 


