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

---

## Step-by-step iteration trace (with actual numbers)

**Starting state:** jar capacity = 10 kg, `small_weight = 0`, `benefit_tracker = 0`

**Ratios computed first:**

| Item | Weight | Profit | Ratio |
|------|--------|--------|-------|
| 1    | 4      | 12     | 3.00  |
| 2    | 8      | 32     | 4.00  |
| 3    | 2      | 40     | 20.00 |
| 4    | 6      | 30     | 5.00  |
| 5    | 1      | 50     | 50.00 |

---

**Iteration 1** — `small_weight = 0`, `remaining = 10`

- Highest ratio → **Item 5** (50.0)
- `tracker_weight = 1`, fits? `1 <= 10` → YES, full item taken
- `small_weight = 0 + 1 = 1`, `benefit_tracker = 0 + 50 = 50`
- Item 5 removed (value / weight / benefit set to 0)

---

**Iteration 2** — `small_weight = 1`, `remaining = 9`

- Highest ratio → **Item 3** (20.0)
- `tracker_weight = 2`, fits? `2 <= 9` → YES, full item taken
- `small_weight = 1 + 2 = 3`, `benefit_tracker = 50 + 40 = 90`
- Item 3 removed

---

**Iteration 3** — `small_weight = 3`, `remaining = 7`

- Highest ratio → **Item 4** (5.0)
- `tracker_weight = 6`, fits? `6 <= 7` → YES, full item taken
- `small_weight = 3 + 6 = 9`, `benefit_tracker = 90 + 30 = 120`
- Item 4 removed

---

**Iteration 4** — `small_weight = 9`, `remaining = 1`

- Remaining items: Item 1 (ratio 3.0), Item 2 (ratio 4.0)
- Highest ratio → **Item 2** (4.0)
- `tracker_weight = 8`, fits? `8 <= 1` → **NO → else branch (partial item)**

The `else` branch runs:

```
remaining_weight = 1
tracker_weight   = 8
profit_tracker   = 32

fraction         = (float)1 / 8 = 0.125   ← 12.5% of Item 2

fraction_profit  = 32 × 0.125 = 4.00

benefit_tracker  = 120 + 4.00 = 124.00

small_weight     = total_weight = 10       ← jar declared full
```

Printed: `Item 2 partly taken -> weight used: 1 of 8, profit: 4.00, remaining jar: 0`

**Loop check:** `small_weight (10) < total_weight (10)` → FALSE → loop exits

---

**Final total profit = 124.00**

> **Key insight for Item 2:** Only 1 kg of space was left, but Item 2 weighs 8 kg.
> The algorithm takes `1/8 = 12.5%` of Item 2, earning `12.5%` of its profit (= 4.00),
> then sets `small_weight = total_weight` to signal the jar is completely full and stop the loop.
> Item 1 is never reached — the jar was already filled in round 4.
