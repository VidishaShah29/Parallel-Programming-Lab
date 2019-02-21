__kernel void matrix (__global int *A, __global int *B, int M, int N) {

    int row = get_global_id(0);
    int col = get_global_id(1);
    int rsum = 0, csum = 0;
    int i;
    
    for (i = 0; i < N; ++i) 
        rsum += A[i + M * row];
    
    for (i = 0; i < M; ++i) 
        csum += A[i * N + col];
    
    B[row * M + col] = rsum + csum;
}











