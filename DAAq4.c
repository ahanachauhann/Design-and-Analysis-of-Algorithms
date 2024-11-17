#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity
struct Activity {
    int start;
    int finish;
};

// Comparison function to sort activities based on their finish time
int compare(const void *a, const void *b) {
    struct Activity *activityA = (struct Activity *)a;
    struct Activity *activityB = (struct Activity *)b;
    return activityA->finish - activityB->finish;
}

// Function to select the maximum number of activities
void activitySelection(struct Activity activities[], int n) {
    // Sort the activities based on finish time
    qsort(activities, n, sizeof(struct Activity), compare);

    // The first activity is always selected
    int lastSelected = 0;
    printf("Selected activities are:\n");
    printf("Activity %d: (%d, %d)\n", lastSelected + 1, activities[lastSelected].start, activities[lastSelected].finish);

    // Iterate through the remaining activities
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= activities[lastSelected].finish) {
            // Select this activity if it does not overlap with the last selected one
            printf("Activity %d: (%d, %d)\n", i + 1, activities[i].start, activities[i].finish);
            lastSelected = i;
        }
    }
}

int main() {
    // Array of activities with start and finish times
    struct Activity activities[] = {
        {1, 3},
        {2, 5},
        {4, 6},
        {7, 8},
        {5, 7},
        {8, 9}
    };
    int n = sizeof(activities) / sizeof(activities[0]);

    // Call the activity selection function
    activitySelection(activities, n);

    return 0;
}
