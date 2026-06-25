# Fractional Knapsack Problem

**Summary:** `fractional knapsack problem.c` solves the Fractional Knapsack using a greedy strategy — repeatedly pick the item with the highest `profit/weight` ratio, take it whole if it fits, otherwise take only the fraction that fills the remaining capacity.

## Input

Knapsack capacity (`fixed_weight`) = **10**

| Item | Weight | Profit | Ratio (profit / weight) |
|------|--------|--------|--------------------------|
| 1    | 4      | 12     | 12 / 4 = 3.00            |
| 2    | 8      | 32     | 32 / 8 = 4.00            |
| 3    | 2      | 40     | 40 / 2 = 20.00           |
| 4    | 6      | 30     | 30 / 6 = 5.00            |
| 5    | 1      | 50     | 50 / 1 = 50.00           |

## Data Structure

Each item is stored in a `struct knapsack` with four fields:

```c
struct knapsack {
    int   item;    // item number
    int   weight;  // weight of the item
    int   profit;  // profit of the item
    float ratio;   // profit / weight, computed before the loop
};
```

## How It Works

1. Compute `ratio = (float)profit / weight` for every item before the loop starts.
2. Enter a `while` loop that runs as long as `total_weight < fixed_weight`.
3. Each round, scan all items with `arr[i].weight != 0` (unzero = not yet used) and find the one with the highest `ratio`. Its index is stored in `idx`.
4. Check if the item fits fully: `total_weight + arr[idx].weight <= fixed_weight`.
   - **Yes (full item):** add its full weight to `total_weight`, print item number, weight, and profit.
   - **No (partial item):** compute `remaining = fixed_weight - total_weight`, calculate `partial_profit = (float)remaining / arr[idx].weight * arr[idx].profit`, set `total_weight = fixed_weight` to exit the loop, and print the partial result.
5. After either branch, set `arr[idx].weight = 0` to mark the item as used so it is skipped in future rounds.

## Iteration Table

Greedy order by ratio: Item 5 (50.00) → Item 3 (20.00) → Item 4 (5.00) → Item 2 (4.00)

| Round | `idx` | Item picked      | `arr[idx].weight` | `total_weight` before | Condition `total_weight + weight <= 10` | Action   | Weight added | Benefit added         | `total_weight` after |
|-------|-------|------------------|--------------------|----------------------|----------------------------------------|----------|--------------|-----------------------|----------------------|
| 1     | 4     | Item 5 (ratio 50)| 1                  | 0                    | 0 + 1 = 1 ≤ 10 → TRUE                 | Full     | 1            | 50                    | 1                    |
| 2     | 2     | Item 3 (ratio 20)| 2                  | 1                    | 1 + 2 = 3 ≤ 10 → TRUE                 | Full     | 2            | 40                    | 3                    |
| 3     | 3     | Item 4 (ratio 5) | 6                  | 3                    | 3 + 6 = 9 ≤ 10 → TRUE                 | Full     | 6            | 30                    | 9                    |
| 4     | 1     | Item 2 (ratio 4) | 8                  | 9                    | 9 + 8 = 17 ≤ 10 → FALSE               | Partial  | 1 of 8       | 32 × (1/8) = **4.00** | 10 → loop exits      |

Item 1 is never reached — the container is full after round 4.

## Fraction Calculation (Round 4)

```
remaining       = fixed_weight - total_weight = 10 - 9 = 1
partial_profit  = (float)remaining / arr[idx].weight * arr[idx].profit
                = (float)1 / 8 * 32
                = 0.125 * 32
                = 4.00
```

## Output

```
Item 5 , total weight used: 1, Benefit: 50
Item 3 , total weight used: 2, Benefit: 40
Item 4 , total weight used: 6, Benefit: 30
Item 2 (partial 1/8 units), Partial Benefit: 4.00
```

Total profit = 50 + 40 + 30 + 4.00 = **124.00**

