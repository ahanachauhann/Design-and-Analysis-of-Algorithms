#include <stdio.h>
#include <stdlib.h>

// Struct to hold item details (weight, value)
struct Item {
    int weight;
    int value;
};

// Utility function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to compare items by value/weight ratio (for sorting)
int compare(const void *a, const void *b) {
    struct Item *itemA = (struct Item *)a;
    struct Item *itemB = (struct Item *)b;
    double ratioA = (double)itemA->value / itemA->weight;
    double ratioB = (double)itemB->value / itemB->weight;
    if (ratioA < ratioB) return 1;
    if (ratioA > ratioB) return -1;
    return 0;
}

// Branch and Bound function to solve 0/1 Knapsack problem
int boundKnapsack(struct Item items[], int n, int W, int idx, int currentWeight, int currentValue, int best) {
    // If the current weight exceeds the knapsack's capacity, return best
    if (currentWeight > W) return best;

    // Update the best solution so far
    best = max(best, currentValue);

    // If we have considered all items, return the current value
    if (idx >= n) return best;

    // Include the current item and explore further
    if (currentWeight + items[idx].weight <= W) {
        best = boundKnapsack(items, n, W, idx + 1, currentWeight + items[idx].weight, currentValue + items[idx].value, best);
    }

    // Exclude the current item and explore further
    best = boundKnapsack(items, n, W, idx + 1, currentWeight, currentValue, best);

    return best;
}

int knapsackBranchBound(struct Item items[], int n, int W) {
    int best = 0;

    // Sort items by value-to-weight ratio (greedy heuristic)
    qsort(items, n, sizeof(struct Item), compare);

    // Start the recursive Branch and Bound function
    best = boundKnapsack(items, n, W, 0, 0, 0, best);

    return best;
}

int main() {
    // Example items: weight and value
    struct Item items[] = {
        {2, 3},
        {3, 4},
        {4, 5},
        {5, 6}
    };

    int n = sizeof(items) / sizeof(items[0]); // Number of items
    int W = 5;  // Knapsack capacity

    // Call the knapsackBranchBound function to get the maximum value
    int result = knapsackBranchBound(items, n, W);
    
    // Print the result
    printf("Maximum value in knapsack = %d\n", result);

    return 0;
}
