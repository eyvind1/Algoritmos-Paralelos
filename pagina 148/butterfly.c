#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int MAX_CONTRIB = 20;

void imprimir(char title[], int value, int my_rank, int p,
      MPI_Comm comm) {
   int* vals = NULL, q;

   if (my_rank == 0) {
      vals = malloc(p*sizeof(int));
      MPI_Gather(&value, 1, MPI_INT, vals, 1, MPI_INT, 0, comm);
      printf("%s:\n", title);
      for (q = 0; q < p; q++)
         printf("Proc %d > %d\n", q, vals[q]);
      printf("\n");
      free(vals);
   } else {
      MPI_Gather(&value, 1, MPI_INT, vals, 1, MPI_INT, 0, comm);
   }
} 



int suma_global(int my_contrib, int my_rank, int p, MPI_Comm comm) {
    int        sum = my_contrib;
    int        temp;
    int        partner;
    unsigned   bitmask = 1;

    while (bitmask < p) {
        partner = my_rank ^ bitmask;
        MPI_Sendrecv(&sum, 1, MPI_INT, partner, 0, &temp, 1, MPI_INT, partner, 0,comm, MPI_STATUS_IGNORE);
        sum += temp;
        bitmask <<= 1;
    }

    return sum;
}  


int main(void) {
   int      p, my_rank;
   MPI_Comm comm;
   int      my_contrib;
   int      sum;

   MPI_Init(NULL, NULL);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   
   srandom(my_rank);
   my_contrib = random() % MAX_CONTRIB;

   imprimir("Process Values", my_contrib, my_rank, p, comm);

   sum = suma_global(my_contrib, my_rank, p, comm);

   imprimir("Process Totals", sum, my_rank, p, comm);

   MPI_Finalize();
   return 0;
} 

 
