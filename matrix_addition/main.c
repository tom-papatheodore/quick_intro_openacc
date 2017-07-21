#include <stdlib.h>
#include <stdio.h>

int main()
{
	// Number of elements in arrays
	unsigned int N = 1 << 10;

	// Bytes in arrays
	size_t bytes_in_array = N*N*sizeof(double);

	// Allocate memory for arrays on host
	double *A = (double*)malloc(bytes_in_array);
	double *B = (double*)malloc(bytes_in_array);
	double *C = (double*)malloc(bytes_in_array);


	// Initialize vector values
	for(int row=0; row<N; row++){
		for(int col=0; col<N; col++){
			A[row*N + col] = 1.0;
			B[row*N + col] = 2.0;
			C[row*N + col] = 0.0;
		}
	}


	#pragma acc data copyin(A[0:N*N],B[0:N*N]) copyout(C[0:N*N])
	{

	// Perform element-wise addition of vectors
	#pragma acc parallel loop
	for(int row=0; row<N; row++){
		for(int col=0; col<N; col++){
			C[row*N + col] = A[row*N + col] + B[row*N + col];
		}
	}

	// Check for correctness
	for(int row=0; row<N; row++){
		for(int col=0; col<N; col++){
			if(C[row*N + col] != 3.0){
				printf("Error: Element C[%d] with row=%d and col=%d is equal to %f instead of 3.0\n", row*N + col, row, col, C[row*N + col]);
				exit(0);
			}
		}
	}

	}

	printf("__SUCCESS__\n");
	
}
