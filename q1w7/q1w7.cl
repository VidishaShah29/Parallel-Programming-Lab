__kernel void matrix(__global int* A, __global int* B,  int m, int n){

	int row = get_global_id(0);
	int col = get_global_id(1);
		
	int x = A[row * n + col];
	int p = x;
	for (int k = 1; k <= row; k++) {
		p *= x;
	}

	B[row * n + col] = p;
			
}

