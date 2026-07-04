# Fractional Knapsack Problem — Beginner's Guide

This file explains how [new.c](file:///Users/samiulazim/Documents/Antigravity%20Folders/EWU-Code/Algorithm/Greedy%20Algorithm/knapsack/new.c) works, step by step, so you can understand the logic **without reading the code**.

---

## What is the Fractional Knapsack Problem?

Imagine you have a **bag (knapsack)** that can hold at most **10 ml** of items. You have **5 items** in front of you. Each item has a **weight** and a **benefit (money value)**. You want to **fill the bag to earn the most money**.

The special rule: **you CAN take a fraction of an item**. You don't have to take the whole thing. For example, if an item weighs 8 ml but you only have 1 ml of space left, you can take just 1 ml of it and get a proportional benefit.

---

## The Items We Have

| Item | Weight | Benefit | Value ($ per ml) |
|------|--------|---------|-------------------|
| 1    | 4 ml   | $12     | 12 / 4 = **3.00** |
| 2    | 8 ml   | $32     | 32 / 8 = **4.00** |
| 3    | 2 ml   | $40     | 40 / 2 = **20.00** |
| 4    | 6 ml   | $30     | 30 / 6 = **5.00** |
| 5    | 1 ml   | $50     | 50 / 1 = **50.00** |

**Knapsack Capacity (W) = 10 ml**

---

## The Greedy Strategy

The algorithm uses a **greedy approach**:

> **Always pick the item with the highest value per ml first.**

Why? Because that item gives you the most money for each ml of space it takes up.

---

## The Key Conditions in the Code

### Condition 1: Keep going while the bag is not full
```
while (w < W)
```
- `w` = how much weight is already in the bag (starts at **0**)
- `W` = max capacity of the bag (**10**)
- As long as the bag has space, keep picking items

### Condition 2: Find the item with the highest value (that hasn't been taken yet)
```
if (value[i] > maxVal && x[i] == 0)
```
- `value[i]` = the dollar-per-ml ratio of item `i`
- `maxVal` = the best ratio found so far (starts at **0** each round)
- `x[i] == 0` = this item hasn't been picked yet
- This loop scans all 5 items and picks the one with the **highest value per ml**

### Condition 3: Take the whole item OR just a fraction
```
if (weight[idx] < W - w)
    take = weight[idx];      // whole item fits → take all of it
else
    take = W - w;            // doesn't fit → take only what space is left
```
- `W - w` = remaining space in the bag
- If the item weighs **less** than the remaining space → **take the whole item**
- If the item weighs **more** than the remaining space → **take only a fraction** (just enough to fill the bag)

### Condition 4: Calculate partial benefit
```
gained = benefit[idx] * take / weight[idx]
```
- If you take 1 ml out of an 8 ml item worth $32, you get: `32 × 1 / 8 = $4.00`
- If you take the full item, you get the full benefit

---

## Step-by-Step Iteration

### Before Starting
```
Bag status: 0 / 10 ml used (10 ml free)
All items available: 1, 2, 3, 4, 5
```

---

### Iteration 1 — Pick the Best Item

**Scan all items for the highest value per ml:**

| Item | Value ($/ml) | Already taken? | Candidate? |
|------|-------------|----------------|------------|
| 1    | 3.00        | No             | Yes        |
| 2    | 4.00        | No             | Yes        |
| 3    | 20.00       | No             | Yes        |
| 4    | 5.00        | No             | Yes        |
| 5    | **50.00**   | No             | ✅ **Winner** |

**Winner: Item 5** (value = $50.00 per ml)

**Does it fit?**
- Item 5 weight = 1 ml
- Remaining space = 10 - 0 = 10 ml
- 1 < 10 → **Yes, take the whole item!**

**Take:** 1 ml of 1 ml
**Benefit gained:** $50 × (1/1) = **$50.00**

```
Bag status: 1 / 10 ml used (9 ml free)
```

---

### Iteration 2 — Pick the Next Best

**Scan remaining items:**

| Item | Value ($/ml) | Already taken? | Candidate? |
|------|-------------|----------------|------------|
| 1    | 3.00        | No             | Yes        |
| 2    | 4.00        | No             | Yes        |
| 3    | **20.00**   | No             | ✅ **Winner** |
| 4    | 5.00        | No             | Yes        |
| 5    | 50.00       | Yes            | ❌ Skip     |

**Winner: Item 3** (value = $20.00 per ml)

**Does it fit?**
- Item 3 weight = 2 ml
- Remaining space = 10 - 1 = 9 ml
- 2 < 9 → **Yes, take the whole item!**

**Take:** 2 ml of 2 ml
**Benefit gained:** $40 × (2/2) = **$40.00**

```
Bag status: 3 / 10 ml used (7 ml free)
```

---

### Iteration 3 — Pick the Next Best

**Scan remaining items:**

| Item | Value ($/ml) | Already taken? | Candidate? |
|------|-------------|----------------|------------|
| 1    | 3.00        | No             | Yes        |
| 2    | 4.00        | No             | Yes        |
| 3    | 20.00       | Yes            | ❌ Skip     |
| 4    | **5.00**    | No             | ✅ **Winner** |
| 5    | 50.00       | Yes            | ❌ Skip     |

**Winner: Item 4** (value = $5.00 per ml)

**Does it fit?**
- Item 4 weight = 6 ml
- Remaining space = 10 - 3 = 7 ml
- 6 < 7 → **Yes, take the whole item!**

**Take:** 6 ml of 6 ml
**Benefit gained:** $30 × (6/6) = **$30.00**

```
Bag status: 9 / 10 ml used (1 ml free)
```

---

### Iteration 4 — Only 1 ml Left!

**Scan remaining items:**

| Item | Value ($/ml) | Already taken? | Candidate? |
|------|-------------|----------------|------------|
| 1    | 3.00        | No             | Yes        |
| 2    | **4.00**    | No             | ✅ **Winner** |
| 3    | 20.00       | Yes            | ❌ Skip     |
| 4    | 5.00        | Yes            | ❌ Skip     |
| 5    | 50.00       | Yes            | ❌ Skip     |

**Winner: Item 2** (value = $4.00 per ml)

**Does it fit?**
- Item 2 weight = 8 ml
- Remaining space = 10 - 9 = 1 ml
- 8 > 1 → **No! Take only a fraction!**

**Take:** 1 ml of 8 ml (just a fraction)
**Benefit gained:** $32 × (1/8) = **$4.00**

```
Bag status: 10 / 10 ml used (0 ml free) — BAG IS FULL!
```

---

### Loop Ends

`w (10) < W (10)` → **False** → The `while` loop **stops**.

---

## Final Result

| Item | Taken     | Weight Used | Benefit Gained |
|------|-----------|-------------|----------------|
| 5    | Full      | 1 ml        | $50.00         |
| 3    | Full      | 2 ml        | $40.00         |
| 4    | Full      | 6 ml        | $30.00         |
| 2    | Fractional (1/8) | 1 ml  | $4.00          |
| 1    | ❌ Not taken | 0 ml     | $0.00          |

### Totals
- **Total Weight:** 10 / 10 ml
- **Total Benefit: $124.00**

---

## What About Item 1?

Item 1 was **never picked** because:
- It had the **lowest value per ml** ($3.00/ml)
- By the time the algorithm got to it, the bag was already **full**
- The greedy algorithm always picks higher-value items first, so Item 1 lost out

---

## Program Output

When you compile and run `new.c`, you see:

```
Item 5: 1 ml of 1 ml, Benefit: $50.00
Item 3: 2 ml of 2 ml, Benefit: $40.00
Item 4: 6 ml of 6 ml, Benefit: $30.00
Item 2: 1 ml of 8 ml, Benefit: $4.00

Total Weight: 10 / 10
Total Benefit: $124.00
```

---

## Quick Summary

1. **Calculate** the value (benefit ÷ weight) for each item
2. **Pick** the item with the highest value that hasn't been taken
3. **Check** if the whole item fits in the remaining space
   - If **yes** → take the whole item
   - If **no** → take only what fits (fraction)
4. **Repeat** until the bag is full
5. The answer is the **maximum possible benefit** = **$124.00**
