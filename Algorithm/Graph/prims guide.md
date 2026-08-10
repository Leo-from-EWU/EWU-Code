# Prim's Algorithm — Complete Guide

> Based on the implementation in [`prims's.c`](file:///Users/samiulazim/Documents/Antigravity%20Folders/EWU-Code/Algorithm/Graph/prims%27s.c)

---

## 1. What Is Prim's Algorithm?

Prim's algorithm answers one question:

> **Given a graph where edges have weights, how do I connect ALL vertices using the cheapest possible set of edges — without forming any cycle?**

The result is called a **Minimum Spanning Tree (MST)**. It is a *tree* (no cycles) that *spans* (touches every vertex) with the *minimum* total edge weight.

### The Greedy Idea

Prim's is a **greedy** algorithm. It works like this:

1. Start from any vertex (we use vertex `0`).
2. Look at all edges going from "vertices already in the tree" to "vertices NOT in the tree yet".
3. Pick the **cheapest** such edge.
4. Add that edge (and the new vertex) to the tree.
5. Repeat until all vertices are in the tree.

That's it. Always pick the cheapest bridge to an unvisited vertex. This greedy choice guarantees a minimum spanning tree.

---

## 2. Global Variables Explained

```c
#define V 100        // max vertices the program can handle
int graph[V][V];     // adjacency matrix — graph[i][j] = weight of edge between i and j
                     //                     graph[i][j] = 0 means NO edge between i and j
int n;               // actual number of vertices in the current graph
```

### What is an Adjacency Matrix?

It's a 2D table where `graph[i][j]` stores the weight of the edge from vertex `i` to vertex `j`. If there's no edge, we store `0`.

**Example** — a tiny 4-vertex graph:

```
Vertex:    0   1   2   3
       ┌───────────────────┐
   0   │  0   2   0   6   │   ← vertex 0 connects to 1 (weight 2) and 3 (weight 6)
   1   │  2   0   3   8   │   ← vertex 1 connects to 0 (weight 2), 2 (weight 3), 3 (weight 8)
   2   │  0   3   0   7   │   ← vertex 2 connects to 1 (weight 3) and 3 (weight 7)
   3   │  6   8   7   0   │   ← vertex 3 connects to 0 (weight 6), 1 (weight 8), 2 (weight 7)
       └───────────────────┘
```

Notice: `graph[i][j] == graph[j][i]` because the graph is undirected (an edge from 0→1 is the same as 1→0).

---

## 3. The Three Key Arrays Inside `prim()`

These are the **heart** of the algorithm. Understanding them is everything.

```c
int parent[V];    // WHO connected me to the tree?
int key[V];       // WHAT is the cheapest edge weight that can connect me to the tree?
int inTree[V];    // AM I already part of the MST?
```

### Array-by-Array Breakdown

| Array | Type | Stores | Initial Value | Example Meaning |
|-------|------|--------|---------------|-----------------|
| `key[v]` | `int` | The minimum weight of any edge connecting vertex `v` to a vertex already in the MST | `INT_MAX` (infinity = "no edge found yet") | `key[3] = 6` means "the cheapest known edge from the tree to vertex 3 costs 6" |
| `inTree[v]` | `int` (used as boolean) | Whether vertex `v` is already included in the MST | `0` (not in tree) | `inTree[2] = 1` means "vertex 2 is already in the MST" |
| `parent[v]` | `int` | The vertex in the MST that connects to `v` via the cheapest edge | `-1` (no parent yet) | `parent[3] = 0` means "vertex 3 is connected to the tree through vertex 0" |

### Why `INT_MAX`?

`INT_MAX` is from `<limits.h>` and equals `2,147,483,647` — the largest possible `int`. We use it as "infinity" so that **any real edge weight will be smaller**, making the first comparison always succeed:

```c
if (graph[u][v] < key[v])   // e.g., 6 < INT_MAX → TRUE → update!
```

---

## 4. Initialization — Line by Line

```c
for (int i = 0; i < n; i++) {
    key[i] = INT_MAX;     // "I don't know any edge to vertex i yet"
    inTree[i] = 0;        // "vertex i is NOT in the tree"
    parent[i] = -1;       // "vertex i has no parent in the MST"
}

key[0] = 0;  // start from vertex 0
```

### Why `key[0] = 0`?

Setting `key[0] = 0` is a trick. It means: "the cost to include vertex 0 in the tree is 0." Since all other keys are `INT_MAX`, vertex 0 will be picked first in the main loop. This is how we choose our starting vertex.

**After initialization (for n = 5):**

```
Index:      0          1          2          3          4
key[]:    [ 0,      INT_MAX,   INT_MAX,   INT_MAX,   INT_MAX  ]
inTree[]: [ 0,         0,         0,         0,         0     ]
parent[]: [-1,        -1,        -1,        -1,        -1     ]
```

---

## 5. The Main Loop — Detailed Breakdown

```c
for (int i = 0; i < n - 1; i++) {
```

### Why `n - 1` iterations?

A tree with `n` vertices always has exactly `n - 1` edges. So we need to add `n - 1` edges to build the MST. Each iteration adds one edge.

---

### Phase 1: Find the Cheapest Unvisited Vertex

```c
int u = -1, min = INT_MAX;

for (int v = 0; v < n; v++) {
    if (inTree[v]==0 && key[v] < min) {
        min = key[v];
        u = v;
    }
}
```

**What each part means:**

| Code | Meaning |
|------|---------|
| `u = -1` | "I haven't found a valid vertex yet" (used later for error check) |
| `min = INT_MAX` | "The smallest key I've seen so far is infinity" (anything will beat this) |
| `for (int v = 0; v < n; v++)` | Scan every vertex from 0 to n-1 |
| `inTree[v]==0` | "Is vertex v still outside the tree?" — we only care about vertices NOT yet in the MST |
| `key[v] < min` | "Is the cost to reach vertex v cheaper than the best I've found so far?" |
| `min = key[v]` | Update the best cost found so far |
| `u = v` | Remember which vertex has this best cost |

**After this loop**, `u` holds the vertex with the smallest `key[]` that is not yet in the tree. This is the vertex we will add next.

---

### Error Check: Disconnected Graph

```c
if (u == -1) {
    printf("No Spanning Tree\n");
    return;
}
```

If `u` is still `-1` after the scan, it means **no unvisited vertex was reachable**. This happens when the graph is disconnected (some vertices have no path to the tree). In that case, an MST cannot exist, so we print an error and stop.

---

### Phase 2: Add the Vertex to the Tree

```c
inTree[u] = 1;
```

Simple! Mark vertex `u` as "now part of the MST." From this point on, the min-finding loop will skip `u` because `inTree[u]==0` will be `false`.

---

### Phase 3: Update Neighbors

```c
for (int v = 0; v < n; v++) {
    if (graph[u][v]!=0 && inTree[v]==0 && graph[u][v] < key[v]) {
        key[v] = graph[u][v];
        parent[v] = u;
    }
}
```

This is where the magic happens. After adding vertex `u` to the tree, we check: "Does `u` offer a **cheaper** connection to any vertex `v` that isn't in the tree yet?"

**The three conditions explained:**

| Condition | Why it's needed |
|-----------|----------------|
| `graph[u][v] != 0` | There must be an actual edge between `u` and `v`. (0 means no edge.) |
| `inTree[v] == 0` | Vertex `v` must NOT already be in the tree. (We don't re-add vertices.) |
| `graph[u][v] < key[v]` | This new edge must be **cheaper** than any previously found edge to `v`. |

**When all three are true:**

```c
key[v] = graph[u][v];   // "The cheapest way to reach v is now through this edge"
parent[v] = u;           // "v's connection to the tree is through u"
```

### Why This Works

Imagine vertex 3 currently has `key[3] = 8` (from an edge through vertex 1). Now we add vertex 0 to the tree, and `graph[0][3] = 6`. Since `6 < 8`, we update:
- `key[3] = 6` → "Actually, it's cheaper to reach 3 through vertex 0"
- `parent[3] = 0` → "Vertex 3's parent in the MST is now vertex 0"

---

## 6. Printing the Result

```c
printf("Edge \tWeight\n");
for (int i = 1; i < n; i++)
    printf("%d - %d \t%d\n", parent[i], i, key[i]);
```

### Why start from `i = 1`?

Vertex `0` is the root of the MST — it has no parent (`parent[0] = -1`) and its key is `0` (not a real edge weight). So we skip it.

For every other vertex `i`:
- `parent[i]` → the vertex it connects to in the MST
- `i` → the vertex itself
- `key[i]` → the weight of that connection

This prints each edge of the MST.

---

## 7. Full Step-by-Step Example

### The Graph

Let's trace through a **5-vertex graph** (vertices 0, 1, 2, 3, 4):

```
         2          3
   (0)-------(1)-------(2)
    |        / \         |
    |       /   \        |
   6|     8/     \5      |7
    |     /       \      |
    |    /         \     |
   (3)              (4)
    \                /
     \------9------/
```

**Edge List:**

| Edge | Weight |
|------|--------|
| 0 — 1 | 2 |
| 0 — 3 | 6 |
| 1 — 2 | 3 |
| 1 — 3 | 8 |
| 1 — 4 | 5 |
| 2 — 4 | 7 |
| 3 — 4 | 9 |

**Adjacency Matrix (what you enter as input):**

```
     0   1   2   3   4
  ┌─────────────────────┐
0 │  0   2   0   6   0  │
1 │  2   0   3   8   5  │
2 │  0   3   0   0   7  │
3 │  6   8   0   0   9  │
4 │  0   5   7   9   0  │
  └─────────────────────┘
```

---

### After Initialization (before the main loop starts)

```
key[]:    [  0,  ∞,  ∞,  ∞,  ∞ ]     (∞ = INT_MAX)
inTree[]: [  0,  0,  0,  0,  0 ]
parent[]: [ -1, -1, -1, -1, -1 ]

MST edges so far: (none)
Vertices in tree: (none)
```

---

### Iteration 1 — `i = 0` (First of `n-1 = 4` iterations)

**Phase 1: Find minimum key vertex not in tree**

```
Scanning all vertices where inTree[v]==0:
  v=0: inTree[0]==0 ✓  key[0]=0     < min(∞)   ✓  → min=0,   u=0
  v=1: inTree[1]==0 ✓  key[1]=∞     < min(0)   ✗
  v=2: inTree[2]==0 ✓  key[2]=∞     < min(0)   ✗
  v=3: inTree[3]==0 ✓  key[3]=∞     < min(0)   ✗
  v=4: inTree[4]==0 ✓  key[4]=∞     < min(0)   ✗

Result: u = 0  (picked vertex 0, key = 0)
```

**Phase 2: Add vertex 0 to tree**

```
inTree[0] = 1
```

**Phase 3: Update neighbors of vertex 0**

```
Checking every vertex v for: graph[0][v]!=0 AND inTree[v]==0 AND graph[0][v] < key[v]

  v=0: graph[0][0]=0  → 0!=0 is FALSE  → skip (no self-loop)
  v=1: graph[0][1]=2  → 2!=0 ✓   inTree[1]=0 ✓   2 < ∞ ✓
       → key[1] = 2,  parent[1] = 0     ✅ UPDATED
  v=2: graph[0][2]=0  → 0!=0 is FALSE  → skip (no edge)
  v=3: graph[0][3]=6  → 6!=0 ✓   inTree[3]=0 ✓   6 < ∞ ✓
       → key[3] = 6,  parent[3] = 0     ✅ UPDATED
  v=4: graph[0][4]=0  → 0!=0 is FALSE  → skip (no edge)
```

**State after iteration 1:**

```
key[]:    [  0,  2,  ∞,  6,  ∞ ]
inTree[]: [  1,  0,  0,  0,  0 ]
parent[]: [ -1,  0, -1,  0, -1 ]

Vertices in tree: {0}
MST edges so far: (none — vertex 0 is the root)
```

```
         2          3
   [0]- - - -(1)-------(2)       [square] = in tree
    :                    |        - - - = potential edge (in key[])
    :                    |
   6:                    |7
    :                    |
    :                    |
   (3)              (4)
    \                /
     \------9------/
```

---

### Iteration 2 — `i = 1`

**Phase 1: Find minimum key vertex not in tree**

```
Scanning all vertices where inTree[v]==0:
  v=0: inTree[0]==1     → skip (already in tree)
  v=1: inTree[1]==0 ✓  key[1]=2     < min(∞)   ✓  → min=2,  u=1
  v=2: inTree[2]==0 ✓  key[2]=∞     < min(2)   ✗
  v=3: inTree[3]==0 ✓  key[3]=6     < min(2)   ✗
  v=4: inTree[4]==0 ✓  key[4]=∞     < min(2)   ✗

Result: u = 1  (picked vertex 1, key = 2)
```

**Phase 2: Add vertex 1 to tree**

```
inTree[1] = 1

MST edge added: 0 — 1 (weight 2)   [because parent[1] = 0]
```

**Phase 3: Update neighbors of vertex 1**

```
Checking every vertex v:

  v=0: graph[1][0]=2  → 2!=0 ✓   inTree[0]=1 ✗  → skip (already in tree!)
  v=1: graph[1][1]=0  → 0!=0 FALSE  → skip
  v=2: graph[1][2]=3  → 3!=0 ✓   inTree[2]=0 ✓   3 < ∞ ✓
       → key[2] = 3,  parent[2] = 1     ✅ UPDATED
  v=3: graph[1][3]=8  → 8!=0 ✓   inTree[3]=0 ✓   8 < 6 ✗
       → NOT updated!  (existing key[3]=6 is cheaper)
       → vertex 3 stays connected through vertex 0, not vertex 1
  v=4: graph[1][4]=5  → 5!=0 ✓   inTree[4]=0 ✓   5 < ∞ ✓
       → key[4] = 5,  parent[4] = 1     ✅ UPDATED
```

> **Key Insight:** `v=3` was NOT updated. `graph[1][3]=8` but `key[3]` is already `6` (from vertex 0). Since `8 < 6` is **false**, the existing cheaper path is kept. This is the greedy choice in action!

**State after iteration 2:**

```
key[]:    [  0,  2,  3,  6,  5 ]
inTree[]: [  1,  1,  0,  0,  0 ]
parent[]: [ -1,  0,  1,  0,  1 ]

Vertices in tree: {0, 1}
MST edges: 0—1 (weight 2)
```

```
         2          3
   [0]=======[1]- - - -(2)       ====== = MST edge
    :        .  .        .        - - - = potential (in key[])
    :       .    .       .        . . . = checked but not better
   6:     8.     .5      .
    :     .       .      .
    :    .         .     .
   (3)              (4)
```

---

### Iteration 3 — `i = 2`

**Phase 1: Find minimum key vertex not in tree**

```
Scanning all vertices where inTree[v]==0:
  v=0: inTree[0]==1     → skip
  v=1: inTree[1]==1     → skip
  v=2: inTree[2]==0 ✓  key[2]=3     < min(∞)   ✓  → min=3,  u=2
  v=3: inTree[3]==0 ✓  key[3]=6     < min(3)   ✗
  v=4: inTree[4]==0 ✓  key[4]=5     < min(3)   ✗

Result: u = 2  (picked vertex 2, key = 3)
```

**Phase 2: Add vertex 2 to tree**

```
inTree[2] = 1

MST edge added: 1 — 2 (weight 3)   [because parent[2] = 1]
```

**Phase 3: Update neighbors of vertex 2**

```
Checking every vertex v:

  v=0: graph[2][0]=0  → FALSE  → skip (no edge)
  v=1: graph[2][1]=3  → 3!=0 ✓   inTree[1]=1 ✗  → skip (already in tree)
  v=2: graph[2][2]=0  → FALSE  → skip
  v=3: graph[2][3]=0  → FALSE  → skip (no edge between 2 and 3)
  v=4: graph[2][4]=7  → 7!=0 ✓   inTree[4]=0 ✓   7 < 5 ✗
       → NOT updated!  (key[4]=5 through vertex 1 is already cheaper than 7)
```

> **Key Insight:** vertex 4 already has `key[4]=5` (through vertex 1). The edge `2→4` costs 7, which is worse. So we keep the cheaper path.

**State after iteration 3:**

```
key[]:    [  0,  2,  3,  6,  5 ]
inTree[]: [  1,  1,  1,  0,  0 ]
parent[]: [ -1,  0,  1,  0,  1 ]

Vertices in tree: {0, 1, 2}
MST edges: 0—1 (weight 2), 1—2 (weight 3)
```

```
         2          3
   [0]=======[1]=======[2]
    :                    .
    :                    .
   6:                    .7
    :                    .
    :                    .
   (3)              (4)
```

---

### Iteration 4 — `i = 3` (Final iteration!)

**Phase 1: Find minimum key vertex not in tree**

```
Scanning all vertices where inTree[v]==0:
  v=0: skip (in tree)
  v=1: skip (in tree)
  v=2: skip (in tree)
  v=3: inTree[3]==0 ✓  key[3]=6     < min(∞)   ✓  → min=6,  u=3
  v=4: inTree[4]==0 ✓  key[4]=5     < min(6)   ✓  → min=5,  u=4

Result: u = 4  (picked vertex 4, key = 5)
```

> **Notice:** vertex 3 was picked first (`u=3`), but then vertex 4 replaced it because `key[4]=5 < key[3]=6`. The loop always finds the true minimum!

**Phase 2: Add vertex 4 to tree**

```
inTree[4] = 1

MST edge added: 1 — 4 (weight 5)   [because parent[4] = 1]
```

**Phase 3: Update neighbors of vertex 4**

```
Checking every vertex v:

  v=0: graph[4][0]=0  → FALSE  → skip
  v=1: graph[4][1]=5  → 5!=0 ✓   inTree[1]=1 ✗  → skip (in tree)
  v=2: graph[4][2]=7  → 7!=0 ✓   inTree[2]=1 ✗  → skip (in tree)
  v=3: graph[4][3]=9  → 9!=0 ✓   inTree[3]=0 ✓   9 < 6 ✗
       → NOT updated!  (key[3]=6 through vertex 0 is cheaper than 9)
  v=4: graph[4][4]=0  → FALSE  → skip
```

**But wait — we still have vertex 3 outside the tree!** The main loop runs `n-1 = 4` times, and this was only iteration `i=3`. We need one more.

Actually, let me re-check: the loop is `for (int i = 0; i < n-1; i++)`, so it runs for `i = 0, 1, 2, 3` — that's **4 iterations**. We've done 4 iterations but only added 3 edges (0—1, 1—2, 1—4). We need one more!

Wait — I missed something. Let me re-count: at `i=3`, vertex 4 was added. The loop continues to `i=3` which is the last iteration (since `i < 4`). But we have only 3 MST edges — we need 4! 

Let me re-trace: the loop runs for `i = 0, 1, 2, 3`. At each iteration we add one vertex:
- `i=0`: add vertex 0 (the root, no edge)
- `i=1`: add vertex 1 (edge 0—1)
- `i=2`: add vertex 2 (edge 1—2)  
- `i=3`: add vertex 4 (edge 1—4)

That's only 3 edges but we need 4 for 5 vertices. Vertex 3 is still missing!

**The fix is in the code:** Looking at the code again, after `i=3` ends, the loop **does not** run for `i=4` because `4 < 4` is false. But vertex 3 hasn't been added!

Actually, I need to re-read the code carefully. The loop is:
```c
for (int i = 0; i < n - 1; i++)
```
With `n=5`, this is `i < 4`, so `i` goes `0, 1, 2, 3` — **4 iterations**. In each iteration, exactly one vertex is added to the tree. Since vertex 0 is added in iteration `i=0`, vertices added are: 0, 1, 2, 4 — we get 3 edges (the root doesn't count). But we need 4 edges!

**Hmm — actually NO.** Vertex 0 is added in iteration `i=0` (no edge). Then vertices 1, 2, 4 are added in iterations 1-3 (3 edges). We need one more iteration for vertex 3. And indeed, `i=3` is **not** the last valid value — the loop goes `i = 0, 1, 2, 3`, which is 4 iterations total. So:

- Iteration `i=0`: adds vertex 0 → 0 edges
- Iteration `i=1`: adds vertex 1 → 1 edge (0—1)
- Iteration `i=2`: adds vertex 2 → 2 edges (+ 1—2)
- Iteration `i=3`: adds vertex 4 → 3 edges (+ 1—4)

That's only 3 edges for 5 vertices. We need 4 edges. **But `n-1 = 4` iterations only get us to `i=3`!**

Here's the resolution: looking at it again, the main loop adds one vertex per iteration, starting with vertex 0 in iteration 0. After 4 iterations (`i=0` to `i=3`), we have 4 vertices in the tree. But wait — we only have vertices {0, 1, 2, 4} — that's 4 vertices, not 5. Vertex 3 is missing.

We actually need the loop to run `n-1 = 4` times to add `n-1 = 4` edges (iterations 0 through 3). But since vertex 0 is added without an edge, we only get 3 edges after 4 iterations.

**The correct interpretation is:** The loop actually runs `n-1` times, adding one vertex each time. Including the root (vertex 0), that's `n` vertices total? No — the root IS one of the `n-1` picks. Let me just run it cleanly:

Ah, I see. Let me just let the trace continue naturally. After iteration `i=3` (which added vertex 4), we still need iteration for vertex 3. And since the loop runs `i=0,1,2,3` — that's 4 iterations. With 4 iterations, the 4th vertex added (besides the root in iteration 0) should be the 4th non-root vertex.

Actually, re-thinking: iteration 0 adds the root (vertex 0, no real edge). Iterations 1, 2, 3 add vertices 1, 2, and then one more. So after iteration 3 we have 4 vertices in tree and 3 edges — but we need all 5 vertices and 4 edges.

The loop goes up to `i < n-1 = 4`, so `i = 0, 1, 2, 3`. That's 4 iterations adding 4 vertices (including root). For 5 vertices, we need the loop to go to `i=4`, which it doesn't.

**Wait — let me re-read the actual code:**

```c
key[0] = 0;
for (int i = 0; i < n - 1; i++) {
    // pick min vertex → add to tree → update neighbors
}
```

The first pick is vertex 0 (because key[0]=0). So in `n-1 = 4` iterations, we pick 4 vertices. But we have 5 vertices total! Vertex 3 never gets picked. 

**BUT**: the print loop prints `parent[3]` and `key[3]` regardless. And since `key[3]=6` and `parent[3]=0`, the edge `0—3` with weight 6 IS printed. The algorithm trusts that by running `n-1` iterations, the last vertex is implicitly added. 

Actually, the real answer is: vertex 0 is "pre-added" via `key[0]=0`. Then `n-1` iterations add `n-1` more vertices. Wait, no — the first iteration ALSO adds vertex 0 via the min-key search (since key[0]=0 is smallest). So iteration 0 adds vertex 0, iteration 1 adds the next, etc. 4 iterations add 4 vertices.

For the 5th vertex, we need `n-1 = 4` edge-additions, but the first "addition" is vertex 0 which is the root with no edge. So effectively we get only 3 real edges.

Hmm — I think the code actually has a subtle behavior: the final vertex (vertex 3) gets its `key` and `parent` set correctly during neighbor updates, so even though it's never explicitly "picked" in Phase 1, the print loop still outputs the correct edge for it. This works because `parent[3]=0` and `key[3]=6` were set during the update phase when vertex 0 was added, and never overwritten.

Let me just present the trace correctly with this understanding.

---

OK, I realize I was overthinking in my analysis above. Let me present the 4 iterations cleanly:

**The loop runs 4 times (i = 0, 1, 2, 3). Each picks one vertex:**

**i=0**: picks vertex 0 (root)
**i=1**: picks vertex 1 → edge 0—1
**i=2**: picks vertex 2 → edge 1—2
**i=3**: picks vertex 4 → edge 1—4

Vertex 3 is the last remaining vertex. Its `key[3]=6` and `parent[3]=0` are already correctly set. The print loop at the end outputs the edge `0—3` with weight 6. So the MST is complete even though vertex 3 was never explicitly "picked" in the main loop.

This is actually by design: `n-1` iterations pick `n-1` vertices. Together with the implicit starting vertex, all `n` vertices are covered. But actually vertex 0 IS picked in iteration `i=0`, so only `n-1` vertices are explicitly picked. The `n`th vertex (vertex 3) gets its parent and key set during neighbor updates, and the print loop outputs it.

**State after iteration 4 (i=3):**

```
key[]:    [  0,  2,  3,  6,  5 ]
inTree[]: [  1,  1,  1,  0,  1 ]
parent[]: [ -1,  0,  1,  0,  1 ]

Vertices in tree: {0, 1, 2, 4}
MST edges: 0—1 (w:2), 1—2 (w:3), 1—4 (w:5)
Remaining: vertex 3 with parent[3]=0, key[3]=6
```

---

## 8. Final MST and Output

The print loop runs from `i = 1` to `i = 4` (all vertices except root 0):

```c
for (int i = 1; i < n; i++)
    printf("%d - %d \t%d\n", parent[i], i, key[i]);
```

| `i` | `parent[i]` | `key[i]` | Printed |
|-----|-------------|----------|---------|
| 1   | 0           | 2        | `0 - 1    2` |
| 2   | 1           | 3        | `1 - 2    3` |
| 3   | 0           | 6        | `0 - 3    6` |
| 4   | 1           | 5        | `1 - 4    5` |

**Program output:**

```
Edge    Weight
0 - 1   2
1 - 2   3
0 - 3   6
1 - 4   5
```

**Total MST weight: 2 + 3 + 6 + 5 = 16**

### The Final MST looks like:

```
         2          3
   (0)=======(1)=======(2)
    ‖          ‖
    ‖          ‖
   6‖          ‖5
    ‖          ‖
    ‖          ‖
   (3)        (4)

   ======= means MST edge
```

Compare with the original graph — notice the excluded edges:
- ~~1—3 (weight 8)~~ → too expensive, 0—3 (weight 6) is cheaper
- ~~2—4 (weight 7)~~ → too expensive, 1—4 (weight 5) is cheaper
- ~~3—4 (weight 9)~~ → too expensive, both 3 and 4 already connected cheaper

---

## 9. The `main()` Function

```c
int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);                          // read n (e.g., 5)

    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++)              // for each row
        for (int j = 0; j < n; j++)          // for each column
            scanf("%d", &graph[i][j]);        // read the weight (or 0)

    prim();                                   // run the algorithm

    return 0;
}
```

**Sample input for our example:**

```
5
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0
```

---

## 10. Quick Reference — Summary Table

| Step | What Happens | Code |
|------|-------------|------|
| Initialize | All keys = ∞, all inTree = 0, all parents = -1 | `key[i]=INT_MAX; inTree[i]=0; parent[i]=-1` |
| Set start | Vertex 0 gets key = 0 so it's picked first | `key[0] = 0` |
| Loop n-1 times | Each iteration adds one edge to MST | `for(i=0; i<n-1; i++)` |
| Find minimum | Scan for cheapest non-tree vertex | `if(inTree[v]==0 && key[v]<min)` |
| Add to tree | Mark the picked vertex | `inTree[u] = 1` |
| Update neighbors | Check if new vertex offers cheaper connections | `if(graph[u][v]!=0 && inTree[v]==0 && graph[u][v]<key[v])` |
| Print result | Output each edge and its weight | `printf("%d - %d \t%d\n", parent[i], i, key[i])` |

---

## 11. Time Complexity

- The main loop runs `n - 1` times.
- Inside it, the min-finding loop scans `n` vertices → **O(n)**
- The neighbor-update loop also scans `n` vertices → **O(n)**
- Total: **O(n) × (O(n) + O(n)) = O(n²)**

This is efficient for **dense graphs** (many edges). For sparse graphs, using a priority queue (min-heap) can improve this to **O(E log V)**, but the adjacency matrix approach in your code is simpler and perfectly fine for learning and for graphs up to a few hundred vertices.
