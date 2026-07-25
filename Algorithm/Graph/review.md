# Breadth-First Search (BFS) Code Review & Step-by-Step Guide

Welcome! This guide will walk you through the Breadth-First Search (BFS) algorithm as implemented in `BFS.c`. We'll break it down step-by-step so that even a beginner can easily understand what is going on behind the scenes.

**Running Example:**
To make this easy to follow, imagine a small graph with 4 vertices: `0, 1, 2, 3`.
The edges are: `0-1`, `0-2`, and `1-3`. 
Let's trace what happens when we start our BFS at **source vertex `0`**.

## Core Concepts & Variables

Before jumping into the steps, let's understand the key arrays used in our code:

*   **`color[]`**: Keeps track of whether a vertex (node) has been discovered or fully explored.
    *   `WHITE` (0): The vertex is **undiscovered**. It hasn't been seen yet. *(Example: At the very beginning, vertices 1, 2, and 3 are WHITE).*
    *   `GRAY` (1): The vertex is **discovered** (visited) and added to the queue, but its neighbors are not fully explored. *(Example: We just saw vertex 1, so it turns GRAY while we wait to look at its neighbors).*
    *   `BLACK` (2): The vertex and all of its adjacent neighbors have been **fully explored**. *(Example: We finished checking all neighbors of vertex 0, so it turns BLACK).*
*   **`d[]` (Distance)**: Stores the shortest distance from the source vertex to the current vertex. *(Example: Vertex 0 has distance 0, Vertex 1 is 1 jump away, so its distance is 1).*
*   **`prev_[]` (Previous/Parent)**: Stores the predecessor (the vertex from which we arrived at the current vertex). This helps in reconstructing the path back to the source. *(Example: If we reached vertex 3 from vertex 1, then `prev_[3] = 1`).*
*   **`queue[]`**: A First-In-First-Out (FIFO) data structure used to process vertices level by level. *(Example: If we discover 1 then 2, the queue will hold `[1, 2]`, meaning we process 1 before 2).*

---

## Step-by-Step Process of the `BFS(int s)` Function

Let's look at what happens when the `BFS(s)` function is called, where `s` is the source (starting) vertex. In our example, `s = 0`.

### Step 1: Initialization
```c
for (int u = 0; u < n; u++) {
    if (u != s) {
        color[u] = WHITE;
        prev_[u] = -1;
        d[u] = -1;
    }
}
```
*   **What happens here?** We prepare the graph. Every vertex (except the source `s`) is marked as `WHITE` (undiscovered). Their distances (`d`) are set to `-1` (meaning infinity or unreachable for now), and they have no parent (`prev_ = -1`).
*   **Example in Action:** Vertices `1, 2, 3` are updated. 
    * `color[1] = WHITE`, `d[1] = -1`, `prev_[1] = -1`
    * `color[2] = WHITE`, `d[2] = -1`, `prev_[2] = -1`
    * `color[3] = WHITE`, `d[3] = -1`, `prev_[3] = -1`

### Step 2: Setting up the Source Vertex
```c
color[s] = GRAY;
d[s] = 0;
prev_[s] = -1;
```
*   **Color turns `GRAY`**: The source vertex `s` is discovered! It turns `GRAY`. This means "I am currently looking at this vertex, but I haven't checked its neighbors yet."
*   **Distance**: The distance to itself is `0`.
*   **Previous**: It has no parent, so it remains `-1`.
*   **Example in Action:** For our source `0`: `color[0]` becomes `GRAY`, `d[0]` becomes `0`, and `prev_[0]` remains `-1`.

### Step 3: Enqueue the Source
```c
queue[rear++] = s;
```
*   **Queue Action**: We place our discovered source vertex `s` into the `queue`. The `queue` will dictate which vertex's neighbors to explore next.
*   **Example in Action:** The queue now looks like: `[ 0 ]`. The variable `rear` becomes 1.

### Step 4: The Main Loop - Exploring Neighbors
```c
while (front < rear) {
    int u = queue[front++]; // Dequeue
```
*   As long as the queue is not empty (`front < rear`), we take the first vertex out of the front of the queue. Let's call it `u`.
*   **Example in Action:** We dequeue `0`. So now `u = 0`. The queue is temporarily empty.

Now, we look at all possible neighbors `v` of `u`:
```c
    for (int v = 0; v < n; v++) {
        if (adj[u][v] == 1 && color[v] == WHITE) {
```
*   If there is an edge between `u` and `v` (`adj[u][v] == 1`) AND `v` is undiscovered (`color[v] == WHITE`):

```c
            color[v] = GRAY;
            d[v] = d[u] + 1;
            prev_[v] = u;
            queue[rear++] = v;
        }
    }
```
*   **Color turns `GRAY`**: We have just discovered neighbor `v`! We mark it `GRAY` immediately so we don't accidentally discover it again later.
*   **Distance Updates**: The distance to `v` is the distance to `u` plus 1 (`d[v] = d[u] + 1`).
*   **Previous Updates**: We reached `v` from `u`, so `u` becomes the parent (`prev_[v] = u`).
*   **Queue Action**: We add `v` to the back of the queue to explore *its* neighbors later on.
*   **Example in Action:** The neighbors of `u=0` are `1` and `2`.
    *   **Looking at neighbor `1`**: It is `WHITE`. `color[1]` turns `GRAY`. `d[1]` becomes `d[0] + 1 = 1`. `prev_[1]` becomes `0`. We add `1` to the queue. Queue: `[ 1 ]`.
    *   **Looking at neighbor `2`**: It is `WHITE`. `color[2]` turns `GRAY`. `d[2]` becomes `d[0] + 1 = 1`. `prev_[2]` becomes `0`. We add `2` to the queue. Queue: `[ 1, 2 ]`.

### Step 5: Marking the Vertex as Fully Explored (BLACK)
```c
    color[u] = BLACK;
}
```
*   **Color turns `BLACK`**: After the `for` loop finishes, we have checked *all* adjacent neighbors of `u`. We are completely done with `u`. It turns `BLACK`. This guarantees we will never process it again, preventing infinite loops and marking the end of its processing cycle.
*   **Example in Action:** We finished checking all neighbors (`1` and `2`) of vertex `0`. Therefore, `color[0]` becomes `BLACK`. The loop repeats, and next time we will dequeue `1` from the queue (`[ 1, 2 ]`) to check its neighbor, `3`.

---

## Summary of the Color Cycle

1.  **WHITE (0):** "I don't know this vertex exists yet." *(Example: Node 3 at the very beginning of the program)*
2.  **GRAY (1):** "I found this vertex! I've put it in the queue, and I will check its neighbors soon." *(Example: Node 1 right after we saw it from Node 0, while it sits in the queue)*
3.  **BLACK (2):** "I have checked all the neighbors of this vertex. I am completely finished with it." *(Example: Node 0 after we checked both Nodes 1 and 2)*

---

## Full Graph Walkthrough Example

Let's trace the algorithm on a larger graph with nodes `0` through `6`.

**Graph Structure:**
*   `0` is connected with `1` and `3`
*   `1` is connected with `0`, `2`, `3`, `5`, and `6`
*   `2` is connected with `1`, `3`, `4`, and `5`
*   `3` is connected with `0`, `1`, `2`, and `4`
*   `4` is connected with `2`, `3`, and `6`
*   `5` is connected with `1` and `2`
*   `6` is connected with `1` and `4`

Let's say we have chosen our source vertex **`s = 1`**.

### Step 1: Initialization
All vertices (except `1`) are set to `WHITE`. Their `d` (distance) and `prev_` are set to `-1`.

### Step 2 & 3: Setting up and Enqueuing the Source
*   `color[1] = GRAY`
*   `d[1] = 0`
*   `prev_[1] = -1`
*   **Queue:** `[ 1 ]`

### Step 4: The Main Loop Begins

**Iteration 1: Dequeue `1`**
*   `u = 1`. **Queue is now empty:** `[ ]`.
*   Neighbors of `1` are `0, 2, 3, 5, 6`. All of them are currently `WHITE`, so we discover them one by one:
    *   **`v = 0`**: `color[0]=GRAY`, `d[0]=d[1]+1=1`, `prev_[0]=1`. **Queue:** `[ 0 ]`.
    *   **`v = 2`**: `color[2]=GRAY`, `d[2]=d[1]+1=1`, `prev_[2]=1`. **Queue:** `[ 0, 2 ]`.
    *   **`v = 3`**: `color[3]=GRAY`, `d[3]=d[1]+1=1`, `prev_[3]=1`. **Queue:** `[ 0, 2, 3 ]`.
    *   **`v = 5`**: `color[5]=GRAY`, `d[5]=d[1]+1=1`, `prev_[5]=1`. **Queue:** `[ 0, 2, 3, 5 ]`.
    *   **`v = 6`**: `color[6]=GRAY`, `d[6]=d[1]+1=1`, `prev_[6]=1`. **Queue:** `[ 0, 2, 3, 5, 6 ]`.
*   We've checked all neighbors of `1`. So, `color[1] = BLACK`.

**Iteration 2: Dequeue `0`**
*   `u = 0`. **Queue is now:** `[ 2, 3, 5, 6 ]`.
*   Neighbors of `0` are `1, 3`.
    *   **`v = 1`** is `BLACK` (already fully explored). We skip it.
    *   **`v = 3`** is `GRAY` (already discovered and in the queue). We skip it.
*   We've checked all neighbors of `0`. So, `color[0] = BLACK`.

**Iteration 3: Dequeue `2`**
*   `u = 2`. **Queue is now:** `[ 3, 5, 6 ]`.
*   Neighbors of `2` are `1, 3, 4, 5`.
    *   `1` is `BLACK`. Skip.
    *   `3` and `5` are `GRAY`. Skip.
    *   **`v = 4`** is `WHITE`! We discover it: `color[4]=GRAY`, `d[4]=d[2]+1=2`, `prev_[4]=2`. **Queue:** `[ 3, 5, 6, 4 ]`.
*   We've checked all neighbors of `2`. So, `color[2] = BLACK`.

**Iteration 4: Dequeue `3`**
*   `u = 3`. **Queue is now:** `[ 5, 6, 4 ]`.
*   Neighbors of `3` are `0, 1, 2, 4`.
    *   `0, 1, 2` are `BLACK`. Skip.
    *   `4` is `GRAY`. Skip.
*   We've checked all neighbors of `3`. So, `color[3] = BLACK`.

**Iteration 5: Dequeue `5`**
*   `u = 5`. **Queue is now:** `[ 6, 4 ]`.
*   Neighbors of `5` are `1, 2`. Both are `BLACK`. Skip.
*   We've checked all neighbors of `5`. So, `color[5] = BLACK`.

**Iteration 6: Dequeue `6`**
*   `u = 6`. **Queue is now:** `[ 4 ]`.
*   Neighbors of `6` are `1, 4`. Both are already `BLACK` or `GRAY`. Skip.
*   We've checked all neighbors of `6`. So, `color[6] = BLACK`.

**Iteration 7: Dequeue `4`**
*   `u = 4`. **Queue is now empty:** `[ ]`.
*   Neighbors of `4` are `2, 3, 6`. All are `BLACK`. Skip.
*   We've checked all neighbors of `4`. So, `color[4] = BLACK`.

### Step 5: Final Result
The queue is now empty (`front == rear`), meaning the `while` loop finishes. Every single node has been fully explored and is now `BLACK`. 
We successfully explored the entire graph level by level, starting from node `1`!
