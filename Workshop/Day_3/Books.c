#include <stdio.h>
#include <limits.h>

int check(int p[], int m, int n, int mid) {
    int sr = 1;  // Number of students required
    int curr_sum = 0;

    for (int i = 0; i < n; i++) {
        if (p[i] > mid) {
            return 0;  // If a single book has more pages than mid, not possible
        }
        if (curr_sum + p[i] > mid) {
            sr++;  // Assign a new student
            curr_sum = p[i];  // Start a new sum
            if (sr > m) {
                return 0;  // More students than allowed
            }
        } else {
            curr_sum += p[i];
        }
    }
    return 1;  // Allocation is possible
}

int pages(int p[], int m, int n) {
    if (m > n) {
        return -1;  // Not enough books for students
    }

    int sum = 0, start = 0, res = INT_MAX;

    // Calculate the total number of pages
    for (int i = 0; i < n; i++) {
        sum += p[i];
    }

    int end = sum;

    while (start <= end) {
        int mid = (start + end) / 2;

        if (check(p, m, n, mid)) {
            res = mid;  // Update result
            end = mid - 1;  // Try for a smaller maximum
        } else {
            start = mid + 1;  // Try for a larger maximum
        }
    }
    return res;
}

int main() {
    int n, m;

    printf("Enter the number of books: ");
    scanf("%d", &n);
    printf("Enter the number of students: ");
    scanf("%d", &m);

    int p[n];
    printf("Enter the number of pages in each book: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int result = pages(p, m, n);

    if (result == -1) {
        printf("-1\n");
    } else {
        printf("The minimum number of maximum pages is: %d\n", result);
    }

    return 0;
}
