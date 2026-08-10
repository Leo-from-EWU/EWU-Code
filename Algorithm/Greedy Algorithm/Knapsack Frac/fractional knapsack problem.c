#include <stdio.h>

// Fractional Knapsack Problem (Greedy Algorithm)

int main() {
    int n = 5;
    int W = 10;

    int weight[] = {4, 8, 2, 6, 1};
    int value[] = {12, 32, 40, 30, 50};
    float benefit[5];
    float x[5] = {0};

    // v_i <- b_i / w_i
    for (int i = 0; i < n; i++) {
        benefit[i] = (float)value[i] / weight[i];
    }

    int w = 0; // total weight

    // while w < W
    while (w < W) {
        // remove item i with highest v_i
        int idx = -1;
        float maxVal = 0;
        for (int i = 0; i < n; i++) {
            if (benefit[i] > maxVal && x[i] == 0) {
                maxVal = benefit[i];
                idx = i;
            }
        }
        if (idx == -1) break;

        // x_i <- min{w_i, W - w}
        int take;
        if (weight[idx] <= W - w) //1< 10-1
            take = weight[idx];
        else
            take = W - w;

        x[idx] = take;

        // w <- w + min{w_i, W - w}
        w = w + take;

        float gained = (float)value[idx] * take / weight[idx];
        printf("Item %d: %d ml of %d ml, Benefit: $%.2f\n", idx + 1, take, weight[idx], gained);
    }

    // total benefit
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += (float)value[i] * x[i] / weight[i];
    }
    printf("\nTotal Weight: %d / %d\n", w, W);
    printf("Total Benefit: $%.2f\n", total);

    return 0;
}
