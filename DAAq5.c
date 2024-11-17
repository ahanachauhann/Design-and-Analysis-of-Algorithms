#include <stdio.h>
#include <limits.h>

// Function to compute the minimum number of scalar multiplications
int matrixChainOrder(int p[], int n) {
    // dp[i][j] stores the minimum number of multiplications needed to multiply matrices A[i] to A[j]
    int dp[n][n];
    
    // Initialize the dp table with 0s for base cases
    for (int i = 1; i < n; i++) {
        dp[i][i] = 0;
    }
    
    // l is the chain length
    for (int length = 2; length < n; length++) {
        for (int i = 1; i < n - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;  // Initialize with a large number
            
            // Try all possible positions to split the matrix chain
            for (int k = i; k <= j - 1; k++) {
                int q = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                }
            }
        }
    }
    
    // dp[1][n-1] stores the minimum number of multiplications needed for multiplying matrices A[1] to A[n-1]
    return dp[1][n - 1];
}

int main() {
    // Dimensions of matrices in the form p[] = [p0, p1, p2, ..., pn]
    // Matrix A1 is p0 x p1, A2 is p1 x p2, ..., An is pn-1 x pn
    int arr[] = {10, 20, 30, 40, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Calling the matrixChainOrder function to find the minimum number of multiplications
    printf("Minimum number of multiplications is %d\n", matrixChainOrder(arr, n));
    
    return 0;
}
