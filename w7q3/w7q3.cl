__kernel void matrix(__global int *A, __global int *B, int M, int N) {

    int i = get_global_id(0);
    int j = get_global_id(1);
    B[j + N * i] = A[i + M * j];
}
