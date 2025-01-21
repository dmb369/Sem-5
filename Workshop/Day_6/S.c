#include <stdio.h>

// Function to calculate maximum profit with a transaction fee
int calculateProfit(int* prices, int n, int fee) {
    int hold = -prices[0];  // Profit when holding a stock
    int noHold = 0;         // Profit when not holding a stock

    for (int i = 1; i < n; i++) {
        noHold = noHold > (hold + prices[i] - fee) ? noHold : (hold + prices[i] - fee);
        hold = hold > (noHold - prices[i]) ? hold : (noHold - prices[i]);
    }

    return noHold; // Maximum profit when not holding any stock
}

int main() {
    int n, fee;

    // Input number of days
    printf("Enter the number of days: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of days.\n");
        return 0;
    }

    // Input stock prices
    int prices[n];
    printf("Enter stock prices: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    // Input transaction fee
    printf("Enter transaction fee: ");
    scanf("%d", &fee);

    // Calculate and print the maximum profit
    int profit = calculateProfit(prices, n, fee);
    printf("Maximum profit: %d\n", profit);

    return 0;
}
