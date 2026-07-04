# 0/1 Knapsack Problem — Complete Study Guide

> **Reference:** CSE246: Algorithms — Dynamic Programming & 0/1 Knapsack  
> **Instructor:** Rabea Khatun, Lecturer, Dept. of CSE, East West University

---

## 1. Problem Statement

### What is the 0/1 Knapsack Problem?

Imagine you are a thief who broke into a store. You have a bag (called a **knapsack**) that can only hold a certain amount of weight. The store has many items. Each item has a **weight** and a **value** (how much money it is worth).

You want to steal as much valuable stuff as possible, but your bag has a weight limit. You **cannot break items into pieces** — you either take the whole item or leave it behind. That is why it is called **0/1**: you pick it (1) or you skip it (0).

### Why Do We Use Dynamic Programming?

You might think: "Why not just pick the most expensive items first?" That is called a **greedy approach**, and it does **not** always work for this problem.

Here is why: sometimes picking a cheaper item leaves room for other items that together give you more value. A greedy strategy only looks at one step ahead. It does not consider all the combinations.

**Dynamic Programming (DP)** solves this by:
- Breaking the big problem into **smaller sub-problems**.
- Solving each small problem **only once**.
- Storing the results in a **table** so we do not redo work.
- Building up the answer **step by step** from smaller answers.

DP has two key ingredients:
1. **Optimal Substructure** — the best solution to the big problem is made from the best solutions to smaller problems.
2. **Overlapping Subproblems** — the same smaller problems come up again and again (so we save time by storing their answers).

### What is the Goal?

Find which items to put in the bag so that:
- The **total weight** does not go over the bag's limit.
- The **total value** is as high as possible.

---

## 2. Our Input

| Item | Weight | Profit (Value) |
|------|--------|----------------|
| 1    | 2      | 12             |
| 2    | 1      | 10             |
| 3    | 3      | 20             |
| 4    | 2      | 15             |

**Maximum capacity (W) = 5**

We have **4 items** and our bag can hold at most **5 units of weight**.

---

## 3. The DP Formula

We build a table called **P(i, w)** where:
- **i** = the number of items we are considering (from item 1 up to item i)
- **w** = the current bag capacity (from 0 up to W)

**P(i, w)** = the maximum profit we can get using items 1 to i, with a bag of capacity w.

The formula has **four cases**:

| Case | Condition | Formula | Meaning |
|------|-----------|---------|---------|
| Case 3 | i = 0 or w = 0 | P(i, w) = 0 | No items or no capacity → profit is 0 |
| Case 4 | weight of item i > w | P(i, w) = P(i-1, w) | Item is too heavy, skip it |
| General | weight of item i ≤ w | P(i, w) = max { v_i + P(i-1, w - w_i), P(i-1, w) } | Pick the better option: take it or leave it |

When the item fits, we compare:
- **Include the item:** Add the item's value + the best we can do with the remaining weight using previous items = `v_i + P(i-1, w - w_i)`
- **Exclude the item:** Just use the best answer from the row above = `P(i-1, w)`

We pick whichever is **larger**.

---

## 4. Building the DP Table — The Empty Table

Our table has:
- **Rows:** 0 to 4 (row 0 is the base case with no items, rows 1–4 are for items 1–4)
- **Columns:** 0 to 5 (column 0 is capacity 0, column 5 is full capacity)

Here is the empty table with the base cases filled in (row 0 and column 0 are all zeros):

| i \ w | 0 | 1 | 2 | 3 | 4 | 5 |
|-------|---|---|---|---|---|---|
| **0** | 0 | 0 | 0 | 0 | 0 | 0 |
| **1** | 0 |   |   |   |   |   |
| **2** | 0 |   |   |   |   |   |
| **3** | 0 |   |   |   |   |   |
| **4** | 0 |   |   |   |   |   |

**Why is row 0 all zeros?** Because if we have zero items to choose from, we cannot make any profit.

**Why is column 0 all zeros?** Because if the bag has zero capacity, we cannot put anything in it.

---

## 5. Simulation — Filling Every Cell

This is the most important section. We will go through **every single cell** one by one.

---

### Row 1: Considering Item 1 (weight = 2, value = 12)

---

#### Cell P(1, 0) — Row 1, Column 0

- **Item being considered:** Item 1 (weight = 2, value = 12)
- **Current bag capacity:** 0
- **Decision:** Column 0 is always 0 (base case). If the bag can hold 0 weight, we cannot put anything in it.
- **Value stored:** **0**

---

#### Cell P(1, 1) — Row 1, Column 1

- **Item being considered:** Item 1 (weight = 2, value = 12)
- **Current bag capacity:** 1
- **Check:** Can Item 1 fit? Item 1 weighs 2, but the bag can only hold 1.
- **2 > 1**, so Item 1 is **too heavy** for this capacity.
- **Case used:** Case 4 — Item is too heavy, so we copy the value from the row above.
- **Formula:** P(1, 1) = P(0, 1) = 0
- **Value stored:** **0**

---

#### Cell P(1, 2) — Row 1, Column 2

- **Item being considered:** Item 1 (weight = 2, value = 12)
- **Current bag capacity:** 2
- **Check:** Can Item 1 fit? Item 1 weighs 2, and the bag can hold 2.
- **2 ≤ 2**, so Item 1 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 1:** P(0, 2) = 0
- **Including Item 1:** value of Item 1 + P(0, 2 - 2) = 12 + P(0, 0) = 12 + 0 = 12
- **Compare:** max(12, 0) = **12**
- **The including option (12) is larger than the excluding option (0).**
- **Formula:** P(1, 2) = max{12 + P(0, 0), P(0, 2)} = max{12, 0} = 12
- **Value stored:** **12**

---

#### Cell P(1, 3) — Row 1, Column 3

- **Item being considered:** Item 1 (weight = 2, value = 12)
- **Current bag capacity:** 3
- **Check:** Can Item 1 fit? Item 1 weighs 2, and the bag can hold 3.
- **2 ≤ 3**, so Item 1 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 1:** P(0, 3) = 0
- **Including Item 1:** 12 + P(0, 3 - 2) = 12 + P(0, 1) = 12 + 0 = 12
- **Compare:** max(12, 0) = **12**
- **The including option (12) is larger than the excluding option (0).**
- **Formula:** P(1, 3) = max{12 + P(0, 1), P(0, 3)} = max{12, 0} = 12
- **Value stored:** **12**

---

#### Cell P(1, 4) — Row 1, Column 4

- **Item being considered:** Item 1 (weight = 2, value = 12)
- **Current bag capacity:** 4
- **Check:** Can Item 1 fit? Item 1 weighs 2, and the bag can hold 4.
- **2 ≤ 4**, so Item 1 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 1:** P(0, 4) = 0
- **Including Item 1:** 12 + P(0, 4 - 2) = 12 + P(0, 2) = 12 + 0 = 12
- **Compare:** max(12, 0) = **12**
- **The including option (12) is larger than the excluding option (0).**
- **Formula:** P(1, 4) = max{12 + P(0, 2), P(0, 4)} = max{12, 0} = 12
- **Value stored:** **12**

---

#### Cell P(1, 5) — Row 1, Column 5

- **Item being considered:** Item 1 (weight = 2, value = 12)
- **Current bag capacity:** 5
- **Check:** Can Item 1 fit? Item 1 weighs 2, and the bag can hold 5.
- **2 ≤ 5**, so Item 1 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 1:** P(0, 5) = 0
- **Including Item 1:** 12 + P(0, 5 - 2) = 12 + P(0, 3) = 12 + 0 = 12
- **Compare:** max(12, 0) = **12**
- **The including option (12) is larger than the excluding option (0).**
- **Formula:** P(1, 5) = max{12 + P(0, 3), P(0, 5)} = max{12, 0} = 12
- **Value stored:** **12**

---

**Row 1 complete!** The table now looks like:

| i \ w | 0 | 1 | 2  | 3  | 4  | 5  |
|-------|---|---|----|----|----|----|
| **0** | 0 | 0 | 0  | 0  | 0  | 0  |
| **1** | 0 | 0 | 12 | 12 | 12 | 12 |

This makes sense: with only Item 1 available, we can only take it if the bag can hold at least 2 units. Once we take it, the profit is 12.

---

### Row 2: Considering Items 1–2 (Item 2: weight = 1, value = 10)

---

#### Cell P(2, 0) — Row 2, Column 0

- **Item being considered:** Item 2 (weight = 1, value = 10)
- **Current bag capacity:** 0
- **Decision:** Column 0 is always 0 (base case).
- **Value stored:** **0**

---

#### Cell P(2, 1) — Row 2, Column 1

- **Item being considered:** Item 2 (weight = 1, value = 10)
- **Current bag capacity:** 1
- **Check:** Can Item 2 fit? Item 2 weighs 1, and the bag can hold 1.
- **1 ≤ 1**, so Item 2 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 2:** P(1, 1) = 0
- **Including Item 2:** 10 + P(1, 1 - 1) = 10 + P(1, 0) = 10 + 0 = 10
- **Compare:** max(10, 0) = **10**
- **The including option (10) is larger than the excluding option (0).**
- **Formula:** P(2, 1) = max{10 + P(1, 0), P(1, 1)} = max{10, 0} = 10
- **Value stored:** **10**

---

#### Cell P(2, 2) — Row 2, Column 2

- **Item being considered:** Item 2 (weight = 1, value = 10)
- **Current bag capacity:** 2
- **Check:** Can Item 2 fit? Item 2 weighs 1, and the bag can hold 2.
- **1 ≤ 2**, so Item 2 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 2:** P(1, 2) = 12
- **Including Item 2:** 10 + P(1, 2 - 1) = 10 + P(1, 1) = 10 + 0 = 10
- **Compare:** max(10, 12) = **12**
- **The excluding option (12) is larger than the including option (10). It is better to keep Item 1 alone here.**
- **Formula:** P(2, 2) = max{10 + P(1, 1), P(1, 2)} = max{10, 12} = 12
- **Value stored:** **12**

---

#### Cell P(2, 3) — Row 2, Column 3

- **Item being considered:** Item 2 (weight = 1, value = 10)
- **Current bag capacity:** 3
- **Check:** Can Item 2 fit? Item 2 weighs 1, and the bag can hold 3.
- **1 ≤ 3**, so Item 2 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 2:** P(1, 3) = 12
- **Including Item 2:** 10 + P(1, 3 - 1) = 10 + P(1, 2) = 10 + 12 = 22
- **Compare:** max(22, 12) = **22**
- **The including option (22) is larger than the excluding option (12). Taking both Item 1 and Item 2 together gives more profit!**
- **Formula:** P(2, 3) = max{10 + P(1, 2), P(1, 3)} = max{22, 12} = 22
- **Value stored:** **22**

---

#### Cell P(2, 4) — Row 2, Column 4

- **Item being considered:** Item 2 (weight = 1, value = 10)
- **Current bag capacity:** 4
- **Check:** Can Item 2 fit? Item 2 weighs 1, and the bag can hold 4.
- **1 ≤ 4**, so Item 2 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 2:** P(1, 4) = 12
- **Including Item 2:** 10 + P(1, 4 - 1) = 10 + P(1, 3) = 10 + 12 = 22
- **Compare:** max(22, 12) = **22**
- **The including option (22) is larger. Taking Item 2 along with Item 1 is better.**
- **Formula:** P(2, 4) = max{10 + P(1, 3), P(1, 4)} = max{22, 12} = 22
- **Value stored:** **22**

---

#### Cell P(2, 5) — Row 2, Column 5

- **Item being considered:** Item 2 (weight = 1, value = 10)
- **Current bag capacity:** 5
- **Check:** Can Item 2 fit? Item 2 weighs 1, and the bag can hold 5.
- **1 ≤ 5**, so Item 2 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 2:** P(1, 5) = 12
- **Including Item 2:** 10 + P(1, 5 - 1) = 10 + P(1, 4) = 10 + 12 = 22
- **Compare:** max(22, 12) = **22**
- **The including option (22) is larger.**
- **Formula:** P(2, 5) = max{10 + P(1, 4), P(1, 5)} = max{22, 12} = 22
- **Value stored:** **22**

---

**Row 2 complete!** The table now looks like:

| i \ w | 0 | 1  | 2  | 3  | 4  | 5  |
|-------|---|----|----|----|----|-----|
| **0** | 0 | 0  | 0  | 0  | 0  | 0  |
| **1** | 0 | 0  | 12 | 12 | 12 | 12 |
| **2** | 0 | 10 | 12 | 22 | 22 | 22 |

With items 1 and 2 available, we can get up to 22 profit (by taking both) when the bag has capacity ≥ 3.

---

### Row 3: Considering Items 1–3 (Item 3: weight = 3, value = 20)

---

#### Cell P(3, 0) — Row 3, Column 0

- **Item being considered:** Item 3 (weight = 3, value = 20)
- **Current bag capacity:** 0
- **Decision:** Column 0 is always 0 (base case).
- **Value stored:** **0**

---

#### Cell P(3, 1) — Row 3, Column 1

- **Item being considered:** Item 3 (weight = 3, value = 20)
- **Current bag capacity:** 1
- **Check:** Can Item 3 fit? Item 3 weighs 3, but the bag can only hold 1.
- **3 > 1**, so Item 3 is **too heavy** for this capacity.
- **Case used:** Case 4 — Item is too heavy, so we copy the value from the row above.
- **Formula:** P(3, 1) = P(2, 1) = 10
- **Value stored:** **10**

---

#### Cell P(3, 2) — Row 3, Column 2

- **Item being considered:** Item 3 (weight = 3, value = 20)
- **Current bag capacity:** 2
- **Check:** Can Item 3 fit? Item 3 weighs 3, but the bag can only hold 2.
- **3 > 2**, so Item 3 is **too heavy** for this capacity.
- **Case used:** Case 4 — Item is too heavy, so we copy the value from the row above.
- **Formula:** P(3, 2) = P(2, 2) = 12
- **Value stored:** **12**

---

#### Cell P(3, 3) — Row 3, Column 3

- **Item being considered:** Item 3 (weight = 3, value = 20)
- **Current bag capacity:** 3
- **Check:** Can Item 3 fit? Item 3 weighs 3, and the bag can hold 3.
- **3 ≤ 3**, so Item 3 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 3:** P(2, 3) = 22
- **Including Item 3:** 20 + P(2, 3 - 3) = 20 + P(2, 0) = 20 + 0 = 20
- **Compare:** max(20, 22) = **22**
- **The excluding option (22) is larger than the including option (20). It is better to keep Items 1+2 (profit 22) than to take only Item 3 (profit 20).**
- **Formula:** P(3, 3) = max{20 + P(2, 0), P(2, 3)} = max{20, 22} = 22
- **Value stored:** **22**

---

#### Cell P(3, 4) — Row 3, Column 4

- **Item being considered:** Item 3 (weight = 3, value = 20)
- **Current bag capacity:** 4
- **Check:** Can Item 3 fit? Item 3 weighs 3, and the bag can hold 4.
- **3 ≤ 4**, so Item 3 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 3:** P(2, 4) = 22
- **Including Item 3:** 20 + P(2, 4 - 3) = 20 + P(2, 1) = 20 + 10 = 30
- **Compare:** max(30, 22) = **30**
- **The including option (30) is larger! Taking Item 3 with Item 2 (from the remaining capacity) gives more profit.**
- **Formula:** P(3, 4) = max{20 + P(2, 1), P(2, 4)} = max{30, 22} = 30
- **Value stored:** **30**

---

#### Cell P(3, 5) — Row 3, Column 5

- **Item being considered:** Item 3 (weight = 3, value = 20)
- **Current bag capacity:** 5
- **Check:** Can Item 3 fit? Item 3 weighs 3, and the bag can hold 5.
- **3 ≤ 5**, so Item 3 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 3:** P(2, 5) = 22
- **Including Item 3:** 20 + P(2, 5 - 3) = 20 + P(2, 2) = 20 + 12 = 32
- **Compare:** max(32, 22) = **32**
- **The including option (32) is larger! Taking Item 3 along with Item 1 (from the remaining capacity of 2) is better.**
- **Formula:** P(3, 5) = max{20 + P(2, 2), P(2, 5)} = max{32, 22} = 32
- **Value stored:** **32**

---

**Row 3 complete!** The table now looks like:

| i \ w | 0 | 1  | 2  | 3  | 4  | 5  |
|-------|---|----|----|----|----|-----|
| **0** | 0 | 0  | 0  | 0  | 0  | 0  |
| **1** | 0 | 0  | 12 | 12 | 12 | 12 |
| **2** | 0 | 10 | 12 | 22 | 22 | 22 |
| **3** | 0 | 10 | 12 | 22 | 30 | 32 |

---

### Row 4: Considering Items 1–4 (Item 4: weight = 2, value = 15)

---

#### Cell P(4, 0) — Row 4, Column 0

- **Item being considered:** Item 4 (weight = 2, value = 15)
- **Current bag capacity:** 0
- **Decision:** Column 0 is always 0 (base case).
- **Value stored:** **0**

---

#### Cell P(4, 1) — Row 4, Column 1

- **Item being considered:** Item 4 (weight = 2, value = 15)
- **Current bag capacity:** 1
- **Check:** Can Item 4 fit? Item 4 weighs 2, but the bag can only hold 1.
- **2 > 1**, so Item 4 is **too heavy** for this capacity.
- **Case used:** Case 4 — Item is too heavy, so we copy the value from the row above.
- **Formula:** P(4, 1) = P(3, 1) = 10
- **Value stored:** **10**

---

#### Cell P(4, 2) — Row 4, Column 2

- **Item being considered:** Item 4 (weight = 2, value = 15)
- **Current bag capacity:** 2
- **Check:** Can Item 4 fit? Item 4 weighs 2, and the bag can hold 2.
- **2 ≤ 2**, so Item 4 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 4:** P(3, 2) = 12
- **Including Item 4:** 15 + P(3, 2 - 2) = 15 + P(3, 0) = 15 + 0 = 15
- **Compare:** max(15, 12) = **15**
- **The including option (15) is larger than the excluding option (12). Taking Item 4 alone is better here.**
- **Formula:** P(4, 2) = max{15 + P(3, 0), P(3, 2)} = max{15, 12} = 15
- **Value stored:** **15**

---

#### Cell P(4, 3) — Row 4, Column 3

- **Item being considered:** Item 4 (weight = 2, value = 15)
- **Current bag capacity:** 3
- **Check:** Can Item 4 fit? Item 4 weighs 2, and the bag can hold 3.
- **2 ≤ 3**, so Item 4 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 4:** P(3, 3) = 22
- **Including Item 4:** 15 + P(3, 3 - 2) = 15 + P(3, 1) = 15 + 10 = 25
- **Compare:** max(25, 22) = **25**
- **The including option (25) is larger than the excluding option (22). Taking Item 4 with Item 2 is better.**
- **Formula:** P(4, 3) = max{15 + P(3, 1), P(3, 3)} = max{25, 22} = 25
- **Value stored:** **25**

---

#### Cell P(4, 4) — Row 4, Column 4

- **Item being considered:** Item 4 (weight = 2, value = 15)
- **Current bag capacity:** 4
- **Check:** Can Item 4 fit? Item 4 weighs 2, and the bag can hold 4.
- **2 ≤ 4**, so Item 4 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 4:** P(3, 4) = 30
- **Including Item 4:** 15 + P(3, 4 - 2) = 15 + P(3, 2) = 15 + 12 = 27
- **Compare:** max(27, 30) = **30**
- **The excluding option (30) is larger than the including option (27). It is better to keep Items 2+3 (profit 30) than to take Item 4 with Item 1 (profit 27).**
- **Formula:** P(4, 4) = max{15 + P(3, 2), P(3, 4)} = max{27, 30} = 30
- **Value stored:** **30**

---

#### Cell P(4, 5) — Row 4, Column 5

- **Item being considered:** Item 4 (weight = 2, value = 15)
- **Current bag capacity:** 5
- **Check:** Can Item 4 fit? Item 4 weighs 2, and the bag can hold 5.
- **2 ≤ 5**, so Item 4 **fits**.
- **Case used:** General case — compare including vs excluding.
- **Excluding Item 4:** P(3, 5) = 32
- **Including Item 4:** 15 + P(3, 5 - 2) = 15 + P(3, 3) = 15 + 22 = 37
- **Compare:** max(37, 32) = **37**
- **The including option (37) is larger! Taking Item 4 along with the best combination from capacity 3 (Items 1+2, which give 22) results in the highest profit.**
- **Formula:** P(4, 5) = max{15 + P(3, 3), P(3, 5)} = max{37, 32} = 37
- **Value stored:** **37**

---

## 6. Final DP Table (Completed)

Here is the full, completed DP table:

| i \ w | 0 | 1  | 2  | 3  | 4  | 5  |
|-------|---|----|----|----|----|-----|
| **0** | 0 | 0  | 0  | 0  | 0  | 0  |
| **1** | 0 | 0  | 12 | 12 | 12 | 12 |
| **2** | 0 | 10 | 12 | 22 | 22 | 22 |
| **3** | 0 | 10 | 12 | 22 | 30 | 32 |
| **4** | 0 | 10 | 15 | 25 | 30 | 37 |

The **maximum profit** is **P(4, 5) = 37**, found in the bottom-right corner.

---

## 7. Trace Back — Finding the Selected Items

Now we know the maximum profit is 37, but **which items did we select?** We find out by tracing back through the table, starting from the bottom-right corner.

### Step 1: Start at P(4, 5) = 37

- We are at **Row 4** (Item 4), **Column 5** (capacity 5).
- Look at the row above: P(3, 5) = 32.
- **P(4, 5) = 37 ≠ P(3, 5) = 32** — the values are different.
- This means **Item 4 was taken!** (If Item 4 was not taken, the value would be the same as the row above.)
- Since Item 4 was taken, we subtract Item 4's weight from the current capacity: 5 - 2 = 3.
- **Move to P(3, 3).** (We go to row 3, and column = 5 - 2 = 3.)

✅ **Item 4 is SELECTED** (weight = 2, value = 15)

---

### Step 2: Now at P(3, 3) = 22

- We are at **Row 3** (Item 3), **Column 3** (capacity 3).
- Look at the row above: P(2, 3) = 22.
- **P(3, 3) = 22 = P(2, 3) = 22** — the values are the **same**.
- This means **Item 3 was NOT taken.** The profit came entirely from items 1 and 2.
- **Move straight up to P(2, 3).** (Same column, go to row 2.)

❌ **Item 3 is SKIPPED**

---

### Step 3: Now at P(2, 3) = 22

- We are at **Row 2** (Item 2), **Column 3** (capacity 3).
- Look at the row above: P(1, 3) = 12.
- **P(2, 3) = 22 ≠ P(1, 3) = 12** — the values are different.
- This means **Item 2 was taken!**
- Subtract Item 2's weight: 3 - 1 = 2.
- **Move to P(1, 2).** (We go to row 1, and column = 3 - 1 = 2.)

✅ **Item 2 is SELECTED** (weight = 1, value = 10)

---

### Step 4: Now at P(1, 2) = 12

- We are at **Row 1** (Item 1), **Column 2** (capacity 2).
- Look at the row above: P(0, 2) = 0.
- **P(1, 2) = 12 ≠ P(0, 2) = 0** — the values are different.
- This means **Item 1 was taken!**
- Subtract Item 1's weight: 2 - 2 = 0.
- **Move to P(0, 0).** (We go to row 0, and column = 2 - 2 = 0.)

✅ **Item 1 is SELECTED** (weight = 2, value = 12)

---

### Step 5: Now at P(0, 0) = 0

- We are at **Row 0** (no more items), **Column 0** (no more capacity).
- **We have reached the base case. The traceback is complete.**

---

### Traceback Summary

| Step | Position | Value in Cell | Value Above | Same? | Decision | Remaining Capacity |
|------|----------|---------------|-------------|-------|----------|--------------------|
| 1    | P(4, 5)  | 37            | 32          | No    | ✅ Take Item 4 | 5 - 2 = 3 |
| 2    | P(3, 3)  | 22            | 22          | Yes   | ❌ Skip Item 3 | 3 (unchanged) |
| 3    | P(2, 3)  | 22            | 12          | No    | ✅ Take Item 2 | 3 - 1 = 2 |
| 4    | P(1, 2)  | 12            | 0           | No    | ✅ Take Item 1 | 2 - 2 = 0 |
| 5    | P(0, 0)  | 0             | —           | —     | Done | 0 |

---

## 8. Final Answer

### Selected Items

| Item | Weight | Value |
|------|--------|-------|
| 1    | 2      | 12    |
| 2    | 1      | 10    |
| 4    | 2      | 15    |

### Totals

- **Total Weight:** 2 + 1 + 2 = **5** (exactly fills the bag!)
- **Total Profit:** 12 + 10 + 15 = **37**

### Why is This the Best Combination?

Let's check some other combinations to see why Items 1, 2, and 4 give the best result:

| Combination | Items | Total Weight | Total Profit | Fits? |
|-------------|-------|-------------|--------------|-------|
| A           | 1, 2, 4 | 2+1+2 = 5 | 12+10+15 = **37** | ✅ Yes |
| B           | 1, 3   | 2+3 = 5   | 12+20 = 32   | ✅ Yes |
| C           | 2, 3   | 1+3 = 4   | 10+20 = 30   | ✅ Yes |
| D           | 3, 4   | 3+2 = 5   | 20+15 = 35   | ✅ Yes |
| E           | 1, 2, 3 | 2+1+3 = 6 | 12+10+20 = 42 | ❌ No (over 5) |
| F           | 2, 3, 4 | 1+3+2 = 6 | 10+20+15 = 45 | ❌ No (over 5) |
| G           | 1, 2   | 2+1 = 3   | 12+10 = 22   | ✅ Yes |

Combination A (Items 1, 2, 4) gives the **highest profit (37)** while staying within the weight limit of 5. No other valid combination can beat it. The DP algorithm found this answer by systematically checking every possibility without having to list them all out like we just did — that is the power of Dynamic Programming!

---

## 9. Key Takeaways

1. **Dynamic Programming builds answers from smaller answers.** We started with 0 items and added one item at a time.
2. **The DP table stores the best profit for every (item count, capacity) pair.** This avoids recalculating the same thing over and over.
3. **For each cell, we make one simple decision:** Is it better to include this item or exclude it? We pick whichever gives more profit.
4. **The traceback tells us which items were actually selected.** We walk backwards through the table comparing each row with the row above it.
5. **The time complexity is O(n × W)** where n is the number of items and W is the bag capacity. For our example: 4 × 5 = 20 cell calculations.
6. **The space complexity is O(n × W)** for the table.

---

*This guide is based on the CSE246 lecture material from East West University.*
