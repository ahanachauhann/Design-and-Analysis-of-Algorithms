#include <stdio.h>
#include <stdbool.h>

// Function to check if there's a subset with sum equal to 'sum'
bool isSubsetSum(int set[], int n, int sum) {
    // Create a 2D DP array where dp[i][j] means if sum 'j' can be formed from first 'i' elements
    bool dp[n+1][sum+1];

    // Initialize the dp array
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            // If sum is 0, it's always possible (by choosing no elements)
            if (j == 0) {
                dp[i][j] = true;
            } else if (i == 0) {
                dp[i][j] = false;
            } else {
                // If the current element is greater than the sum, don't include it
                if (set[i-1] > j) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    // Otherwise, check if sum can be obtained either by including or excluding the current element
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-set[i-1]];
                }
            }
        }
    }
    return dp[n][sum];
}

int main() {
    int set[] = {3, 34, 4, 12, 5, 2};  // Example set
    int sum = 9;  // Target sum
    
    int n = sizeof(set)/sizeof(set[0]);
    
    if (isSubsetSum(set, n, sum)) {
        printf("Subset with sum %d exists.\n", sum);
    } else {
        printf("Subset with sum %d does not exist.\n", sum);
    }

    return 0;
}
