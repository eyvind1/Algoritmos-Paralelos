#include <stdio.h>
#include <cuda.h>

__global__ void Vec_add(float *c, float *a, float *b, int n) {
   int idx = blockIdx.x * blockDim.x + threadIdx.x;
   if (idx < n){
     c[idx] = a[idx] + b[idx];
   }
}

int main(int argc, char* argv[]) {
   float *a_h, *b_h, *c_h;
   float *a_d, *b_d, *c_d;
   const int n=24;
   size_t size=n *sizeof(float);

   a_h = (float*) malloc(size);
   b_h = (float*) malloc(size);
   c_h = (float*) malloc(size);

   for (int i = 0; i < n; i++) {
      a_h[i] = i;
      b_h[i] = 	i+1;
   }

   printf("\nArreglo a:\n");
   for(int i=0;i<n;i++)
   		printf("%f ",a_h[i]);
   printf("\nArreglo b:\n");
   for(int i=0;i<n;i++)
   		printf("%f ",b_h[i]);
   
   cudaMalloc((void**)&a_d, size);
   cudaMalloc((void**)&b_d, size);
   cudaMalloc((void**)&c_d, size);

   cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
   cudaMemcpy(b_d, b_h, size, cudaMemcpyHostToDevice);

   int block_size=8;
   int n_blocks=n/block_size+(n%block_size==0 ? 0:1);
   Vec_add<<<n_blocks,block_size>>>(c_d, a_d, b_d, n);

   cudaMemcpy(c_h, c_d, size, cudaMemcpyDeviceToHost);

   printf("\nLa suma es: \n");
   for (int i = 0; i < n; i++)
      printf("%f ", c_h[i]);
   printf("\n");

   
   free(a_h);
   free(b_h);
   free(c_h);
   cudaFree(a_d);
   cudaFree(b_d);
   cudaFree(c_d);
   return 0;
}