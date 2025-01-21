#include <stdio.h>
#include <stdlib.h>

// Compare function for sorting activities by end time
int compare(const void *a, const void *b) {
    return ((int*)a)[1] - ((int*)b)[1];
}

// Function to calculate the maximum number of activities
int maxActivities(int activities[][2], int n) {
    qsort(activities, n, sizeof(activities[0]), compare);

    int count = 1; // At least one activity can be selected
    int lastEnd = activities[0][1]; // End time of the first activity

    for (int i = 1; i < n; i++) {
        if (activities[i][0] > lastEnd) { // If the start time is after the last end time
            count++;
            lastEnd = activities[i][1]; // Update the last end time
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    int activities[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &activities[i][0], &activities[i][1]); // Read start and end times
    }

    printf("Maximum number of activities: %d\n", maxActivities(activities, n));
    return 0;
}
