#include <stdio.h>
#include <stdlib.h>

// Function to return the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Dynamic Programming solution for 0/1 Knapsack Problem
int knapsackDP(int weights[], int values[], int n, int W) {
    // Create a DP table to store the maximum value at each subproblem
    int dp[n+1][W+1];

    // Initialize the DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;  // Base case: no items or no capacity
            else if (weights[i-1] <= w)
                dp[i][w] = max(dp[i-1][w], values[i-1] + dp[i-1][w - weights[i-1]]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    // The last cell of the DP table contains the result (maximum value for full capacity)
    return dp[n][W];
}

int main() {
    // Example items (weights and values)
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int n = sizeof(weights) / sizeof(weights[0]); // Number of items
    int W = 5;  // Knapsack capacity

    // Call the knapsackDP function to compute the maximum value
    int result = knapsackDP(weights, values, n, W);

    // Print the result
    printf("Maximum value in knapsack = %d\n", result);

    return 0;
}
