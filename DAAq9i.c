#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;  // Returns the maximum of a and b
}

// Helper function to perform backtracking (defined outside main function)
void solve(int idx, int currentWeight, int currentValue, int weights[], int values[], int n, int W, int *best) {
    if (idx == n) {
        *best = max(*best, currentValue);  // If we've considered all items, update best value
        return;
    }

    // Include the item if it doesn't exceed the capacity
    if (currentWeight + weights[idx] <= W) {
        solve(idx + 1, currentWeight + weights[idx], currentValue + values[idx], weights, values, n, W, best);
    }

    // Exclude the item
    solve(idx + 1, currentWeight, currentValue, weights, values, n, W, best);
}

int knapsackBacktracking(int weights[], int values[], int n, int W) {
    int best = 0;  // Stores the best (maximum) value found so far

    // Start solving from the first item
    solve(0, 0, 0, weights, values, n, W, &best);

    return best;  // Return the best value found
}

int main() {
    int weights[] = {2, 3, 4, 5};    // Weights of the items
    int values[] = {3, 4, 5, 6};     // Values of the items
    int n = sizeof(weights) / sizeof(weights[0]);  // Number of items
    int W = 5;  // Knapsack weight capacity

    // Call the knapsackBacktracking function to get the maximum value
    int result = knapsackBacktracking(weights, values, n, W);
    
    // Print the result
    printf("Maximum value in knapsack = %d\n", result);

    return 0;
}
