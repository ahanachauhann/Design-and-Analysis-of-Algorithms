#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 16  // Start with a smaller size (16) for debugging

// Traditional Matrix Multiplication (Naive)
void multiply_naive(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Strassen's helper functions
void add(int A[N][N], int B[N][N], int C[N][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int A[N][N], int B[N][N], int C[N][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's Matrix Multiplication (Recursive)
void strassen(int A[N][N], int B[N][N], int C[N][N], int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return; // Base case when size reaches 1x1 matrix
    }

    int newSize = size / 2;
    
    // Define temporary sub-matrices
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize];
    int M5[newSize][newSize], M6[newSize][newSize], M7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];

    // Divide matrices into sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, newSize);
    add(B11, B22, temp2, newSize);
    strassen(temp1, temp2, M1, newSize);

    // M2 = (A21 + A22) * B11
    add(A21, A22, temp1, newSize);
    strassen(temp1, B11, M2, newSize);

    // M3 = A11 * (B12 - B22)
    subtract(B12, B22, temp2, newSize);
    strassen(A11, temp2, M3, newSize);

    // M4 = A22 * (B21 - B11)
    subtract(B21, B11, temp2, newSize);
    strassen(A22, temp2, M4, newSize);

    // M5 = (A11 + A12) * B22
    add(A11, A12, temp1, newSize);
    strassen(temp1, B22, M5, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, temp1, newSize);
    add(B11, B12, temp2, newSize);
    strassen(temp1, temp2, M6, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, newSize);
    add(B21, B22, temp2, newSize);
    strassen(temp1, temp2, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, temp1, newSize);
    subtract(temp1, M5, temp2, newSize);
    add(temp2, M7, C, newSize);

    // C12 = M3 + M5
    add(M3, M5, temp1, newSize);
    for (int i = 0; i < newSize; i++) {
        for (int j = newSize; j < size; j++) {
            C[i][j] = temp1[i][j - newSize];
        }
    }

    // C21 = M2 + M4
    add(M2, M4, temp1, newSize);
    for (int i = newSize; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = temp1[i - newSize][j];
        }
    }

    // C22 = M1 - M2 + M3 + M6
    add(M1, M2, temp1, newSize);
    subtract(temp1, M3, temp2, newSize);
    add(temp2, M6, temp1, newSize);
    for (int i = newSize; i < size; i++) {
        for (int j = newSize; j < size; j++) {
            C[i][j] = temp1[i - newSize][j - newSize];
        }
    }
}

int main() {
    int A[N][N], B[N][N], C1[N][N], C2[N][N];
    srand(time(0));

    // Initialize matrices A and B with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    // Timing the traditional matrix multiplication
    clock_t start = clock();
    multiply_naive(A, B, C1);
    clock_t end = clock();
    double naive_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Traditional Matrix Multiplication Time: %.6f seconds\n", naive_time);

    // Timing Strassen's matrix multiplication
    start = clock();
    strassen(A, B, C2, N);
    end = clock();
    double strassen_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Strassen's Matrix Multiplication Time: %.6f seconds\n", strassen_time);

    return 0;
}
