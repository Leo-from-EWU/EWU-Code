# 🔌 Dhaka Emergency Power Distribution System

> A CLI-based simulation that decides **which zones of Dhaka get electricity first** during a power shortage — using DSA concepts like stacks, greedy allocation, and Prim's MST.

---

## What It Does

Manages power distribution across 16 zones of Dhaka by:

- **Ranking zones** by a weighted priority score (hospitals, schools, industries, banks, govt offices, population)
- **Allocating limited power** to the highest-priority zones first (Greedy / 0-1 Knapsack approach)
- **Finding the cheapest cable network** to connect all zones (Prim's Minimum Spanning Tree)
- **Handling emergencies** — any zone can be force-promoted to Rank 1
- **Managing facilities** — add/remove infrastructure and watch rankings update live

---

## Why We Built It

Load-shedding is a real problem in Dhaka. We wanted to model a fair, data-driven approach to power distribution instead of arbitrary cutoffs — while applying core DSA and algorithm concepts to a real-world scenario.

---

## Time Complexity

| Operation | Complexity | Notes |
|---|---|---|
| Priority Scoring | O(n) | Single pass over all zones |
| Sorting (Bubble Sort) | O(n²) | Sorts zones by score |
| Greedy Allocation | O(n) | One pass, greedily assigns power |
| Prim's MST | O(n²) | Adjacency matrix implementation |
| Stack Operations | O(1) | Push / Pop for top-3 rotation |

*n = number of zones (8 in v1, 16 in v2)*

---

## Future Improvements

- Replace Bubble Sort with **Merge Sort** → O(n²) → O(n log n)
- Use **adjacency list + min-heap** for Prim's → O(n²) → O(E log V)
- Add **real-time data input** (API / sensors) instead of hardcoded values
- Build a **web dashboard** for visualization
- Implement **fractional knapsack** for partial power allocation

---

## Tech

- **Language:** C
- **Concepts:** Stack, Greedy Algorithm, Prim's MST, Bubble Sort, Weighted Scoring

---

## How to Run

```bash
gcc DSA_atiqsir.c -o power_v1 && ./power_v1      # Version 1 (Stack-based, 8 zones)
gcc Prims\&Greedy_rabea_maam.c -o power_v2 && ./power_v2  # Version 2 (Greedy + Prim's, 16 zones)
```
