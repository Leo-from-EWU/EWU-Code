# Fractional Knapsack Problem

**Summary:** `fractional knapsack problem.c` solves the Fractional Knapsack using a greedy strategy — repeatedly pick the item with the highest benefit/weight ratio, take it whole if it fits, otherwise take the fraction that fills the remaining capacity.

## Input

Knapsack capacity = **10**

| Item | Weight | Benefit | Ratio (benefit / weight) |
|------|--------|---------|--------------------------|
| 1    | 4      | 12      | 12 / 4 = 3.00            |
| 2    | 8      | 32      | 32 / 8 = 4.00            |
| 3    | 2      | 40      | 40 / 2 = 20.00           |
| 4    | 6      | 30      | 30 / 6 = 5.00            |
| 5    | 1      | 50      | 50 / 1 = 50.00           |

## How it works

1. Compute the ratio `benefit / weight` for every item.
2. Each round, scan all remaining items and pick the one with the **highest ratio**.
3. If the item's weight fits the remaining capacity → take it **fully** (add full weight + full benefit).
4. If it does not fit → take the **fraction** that fills the jar: `benefit × (remaining / weight)`.
5. Remove the chosen item (by its index) and repeat until the jar is full.

## Iteration table

Greedy order by ratio: Item 5 (50) → Item 3 (20) → Item 4 (5) → Item 2 (4) → Item 1 (3)

| Round | Picked (highest ratio) | Item weight | Remaining before | Action  | Weight added | Profit added     | Used weight | Total profit |
|-------|------------------------|-------------|------------------|---------|--------------|------------------|-------------|--------------|
| 1     | Item 5 (ratio 50)      | 1           | 10               | full    | 1            | 50               | 1           | 50.00        |
| 2     | Item 3 (ratio 20)      | 2           | 9                | full    | 2            | 40               | 3           | 90.00        |
| 3     | Item 4 (ratio 5)       | 6           | 7                | full    | 6            | 30               | 9           | 120.00       |
| 4     | Item 2 (ratio 4)       | 8           | 1                | partial | 1 of 8       | 32 × 1/8 = 4.00  | 10          | 124.00       |

Item 1 is never reached — the jar is full after round 4.

### Fraction calculation (round 4)

| Remaining capacity | Item weight | Fraction taken | Profit = benefit × fraction |
|--------------------|-------------|----------------|-----------------------------|
| 1                  | 8           | 1 / 8 = 0.125  | 32 × 0.125 = 4.00           |

## Output

```
Total profit = 124.00
```

## Key fixes baked into the code

| Bug | Fix |
|-----|-----|
| Ratio stored as `int` → decimals truncated | Store `value` as `float`, cast division `(float)benefit / weight` |
| Profit tracked as `int` → partial profit lost | `float benefit_tracker` |
| Loop `small_weight <= total_weight` overruns full jar | `small_weight < total_weight` |
| Removing item by matching ratio deletes all items with same ratio | Remove by `selected_index` |
| Partial item added full profit instead of the fraction | Compute `profit × (remaining / weight)` |
