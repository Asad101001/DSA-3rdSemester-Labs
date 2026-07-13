# DSA Finals Lab - Past Papers Master Guide 🚀

This guide provides deep, thorough explanations and pseudocode for all 12 objectives found in the `Past Papers` directory. This is designed for your final lab exam preparation, focusing on the core manual C-style implementations without relying on high-level abstractions.

---

## 🌳 Objective 01: Median 4-ary Tree
**Concept:** Instead of a binary tree (2 children), we build a 4-ary tree (4 children) by splitting a sorted list into 4 equal quadrants using the median as the root.
**Deep Dive:** We recursively find the exact median index. The array is split into $S_1$, $S_2$, $S_3$, and $S_4$. We then recursively generate 4 subtrees. This approach ensures maximum tree balance.

### 📝 Pseudocode (Recursive Construction)
```text
function build4aryTree(arr, start, end, level):
    if start > end:
        return NULL
    
    // Find absolute median
    mid = start + (end - start) / 2
    root = createNode(arr[mid], level)
    
    // Calculate boundaries for 4 quadrants
    quarter = (end - start + 1) / 4
    
    // Recursively build 4 children
    root->child1 = build4aryTree(arr, start, start + quarter - 1, level + 1)
    root->child2 = build4aryTree(arr, start + quarter, mid - 1, level + 1)
    root->child3 = build4aryTree(arr, mid + 1, end - quarter, level + 1)
    root->child4 = build4aryTree(arr, end - quarter + 1, end, level + 1)
    
    return root
```

---

## 🪞 Objective 02: Float Binary Tree Mirror
**Concept:** Construct a binary tree using Level-Order (Heap-style) insertion for floating-point numbers, and then generate its exact mirror image.
**Deep Dive:** Heap-style insertion requires a Queue. Since we can't use STL, we build a static array-based queue to track nodes. Mirroring simply swaps the left and right pointers of every single node in the tree recursively.

### 📝 Pseudocode (Mirroring a Tree)
```text
function mirrorTree(root):
    if root == NULL:
        return
    
    // Post-order or Pre-order swap
    mirrorTree(root->left)
    mirrorTree(root->right)
    
    // Swap pointers
    temp = root->left
    root->left = root->right
    root->right = temp
```

---

## ⚡ Objective 03: Doubly Linked List QuickSort
**Concept:** Performing the QuickSort algorithm purely on a Doubly Linked List (in-place) without converting it to an array.
**Deep Dive:** We use Lomuto's Partition scheme. We pick the last node as a pivot. We maintain a pointer `i` that tracks the boundary of elements smaller than the pivot. When traversing with `j`, if `j->data < pivot->data`, we advance `i` and swap the data of `i` and `j`.

### 📝 Pseudocode (DLL Partition)
```text
function partition(startNode, endNode):
    pivotValue = endNode->data
    i = startNode->prev // Tracks smaller elements
    
    for j = startNode to endNode (exclusive):
        if j->data <= pivotValue:
            if i == NULL: i = startNode
            else: i = i->next
            swap(i->data, j->data)
    
    if i == NULL: i = startNode
    else: i = i->next
    
    swap(i->data, endNode->data)
    return i
```

---

## 🔍 Objective 04: BST Search, Pred & Succ
**Concept:** In a Binary Search Tree, perform basic node searching, count total nodes, and find the In-Order Predecessor and Successor for a given value.
**Deep Dive:** The predecessor is the maximum value in the left subtree. The successor is the minimum value in the right subtree.

### 📝 Pseudocode (Finding Predecessor & Successor)
```text
function findPredSucc(root, target, pred, succ):
    if root == NULL: return
    
    if root->data == target:
        // Pred is max of left subtree
        if root->left != NULL:
            temp = root->left
            while temp->right != NULL: temp = temp->right
            pred = temp
        
        // Succ is min of right subtree
        if root->right != NULL:
            temp = root->right
            while temp->left != NULL: temp = temp->left
            succ = temp
        return
        
    if root->data > target:
        succ = root // Potential successor
        findPredSucc(root->left, target, pred, succ)
    else:
        pred = root // Potential predecessor
        findPredSucc(root->right, target, pred, succ)
```

---

## 🌲 Objective 05: Heap Tree Mirror & Pred/Succ Combo
**Concept:** A complete fusion of Objective 02 and Objective 04. Insert using Queue (Level-Order), mirror it, and then find Predecessor and Successor.
**Deep Dive:** Because this is a Heap-style tree (complete binary tree) and NOT a Binary Search Tree, finding Pred/Succ requires an entirely different approach: In-Order traversal into an array, and then finding the target to get `arr[i-1]` and `arr[i+1]`.

### 📝 Pseudocode (Heap Pred/Succ via Array)
```text
function inOrderToArray(root, arr, index):
    if root == NULL: return
    inOrderToArray(root->left, arr, index)
    arr[index++] = root
    inOrderToArray(root->right, arr, index)

function findPredSuccInHeap(root, target):
    arr = new Array()
    inOrderToArray(root, arr, 0)
    
    for i = 0 to length(arr):
        if arr[i]->data == target:
            pred = (i > 0) ? arr[i-1] : NULL
            succ = (i < length-1) ? arr[i+1] : NULL
            print(pred, succ)
            return
```

---

## 🔗 Objective 06: SLL Sorted Insert & Reverse
**Concept:** Insert elements into a Singly Linked List so it remains perfectly sorted, then create a deep copy of the list that is completely reversed.
**Deep Dive:** Sorted insert requires maintaining a trailing pointer or checking `current->next->data`. Copy-reverse is elegantly solved by traversing the original list and always inserting the copied node at the `HEAD` of the new list.

### 📝 Pseudocode (Sorted Insert & Head-Insert Reverse)
```text
function sortedInsert(head, value):
    newNode = createNode(value)
    if head == NULL OR head->data >= value:
        newNode->next = head
        head = newNode
        return
        
    current = head
    while current->next != NULL AND current->next->data < value:
        current = current->next
        
    newNode->next = current->next
    current->next = newNode

function copyReverse(head):
    newHead = NULL
    current = head
    while current != NULL:
        newNode = createNode(current->data)
        newNode->next = newHead // Insert at HEAD!
        newHead = newNode
        current = current->next
    return newHead
```

---

## 🔄 Objective 07: DLL Sorted Insert & Copy Reverse
**Concept:** Same logic as Objective 06, but strictly applied to a Doubly Linked List, requiring careful management of the `prev` pointers.
**Deep Dive:** When inserting into a DLL, if you insert between `A` and `B`, you must update `A->next`, `newNode->prev`, `newNode->next`, and crucially `B->prev`.

### 📝 Pseudocode (DLL Sorted Insert Edge Cases)
```text
function dllSortedInsert(head, value):
    newNode = createNode(value)
    
    // Case 1: Empty or replacing head
    if head == NULL OR head->data >= value:
        newNode->next = head
        if head != NULL: head->prev = newNode
        head = newNode
        return
        
    // Case 2: Middle or End
    current = head
    while current->next != NULL AND current->next->data < value:
        current = current->next
        
    newNode->next = current->next
    if current->next != NULL:
        current->next->prev = newNode
        
    current->next = newNode
    newNode->prev = current
```

---

## ⚖️ Objective 08: BST Equality & Structure Descending
**Concept:** Compare two separate BSTs to check if they are identical (data + structure), check if they just share the same structure, and print a tree in descending order.
**Deep Dive:** Traversing `Right -> Root -> Left` automatically yields a descending order in a valid BST. Structural equality simply ignores the `data` comparison step.

### 📝 Pseudocode (Structural Equality & Descending Sort)
```text
function hasSameStructure(tree1, tree2):
    if tree1 == NULL AND tree2 == NULL: return TRUE
    if tree1 == NULL OR tree2 == NULL: return FALSE
    
    return hasSameStructure(tree1->left, tree2->left) AND 
           hasSameStructure(tree1->right, tree2->right)

function printDescending(root):
    if root == NULL: return
    printDescending(root->right)
    print(root->data)
    printDescending(root->left)
```

---

## 🗺️ Objective 09 & 12: Maze BFS (Dynamic & Static)
**Concept:** Given a grid maze of 0s (path) and 1s (walls), map it into a Graph using an Adjacency List, then find the shortest path from `(0,0)` to `(n-1,m-1)` using Breadth-First Search. Objective 09 is dynamically allocated, 12 is static array.
**Deep Dive:** The hardest part is graph conversion. A grid `n x m` has `n*m` nodes. Node ID = `row * m + col`. From each cell, check 8 valid directions. If a neighbor is valid and `0`, add a directed edge in the Adjacency List. BFS then uses a Queue to find the path, utilizing a `parent` array to backtrack the final route.

### 📝 Pseudocode (Grid to Graph Mapping & BFS)
```text
function buildAdjacencyList(grid, n, m):
    for i = 0 to n-1:
        for j = 0 to m-1:
            if grid[i][j] == 1: continue // Wall
            
            nodeId = i * m + j
            for each direction (dx, dy) in 8_directions:
                ni = i + dx
                nj = j + dy
                if isValid(ni, nj) AND grid[ni][nj] == 0:
                    neighborId = ni * m + nj
                    addEdge(nodeId, neighborId)

function BFS(start, target):
    queue.push(start)
    visited[start] = TRUE
    parent[start] = -1
    
    while queue is not empty:
        current = queue.pop()
        if current == target: break
        
        for neighbor in adjList[current]:
            if not visited[neighbor]:
                visited[neighbor] = TRUE
                parent[neighbor] = current
                queue.push(neighbor)
                
    // Backtrack path
    path = []
    curr = target
    while curr != -1:
        path.prepend(curr)
        curr = parent[curr]
    print(path)
```

---

## ↕️ Objective 10: DLL Reverse & MinMax
**Concept:** Reverse a Doubly Linked List purely by manipulating pointers (no copying), and find the Min and Max values.
**Deep Dive:** To reverse a DLL in place, you simply iterate through every node and swap its `next` and `prev` pointers. The original `tail` becomes the new `head`.

### 📝 Pseudocode (In-Place DLL Reverse)
```text
function reverseDLL(head):
    if head == NULL: return NULL
    
    current = head
    temp = NULL
    
    while current != NULL:
        // Swap next and prev
        temp = current->prev
        current->prev = current->next
        current->next = temp
        
        // Move to the next node (which is now in prev)
        current = current->prev
        
    // temp->prev is the new head
    if temp != NULL:
        head = temp->prev
        
    return head
```

---

## 🎯 Objective 11: DLL MinMax & Middle Extraction
**Concept:** Advanced pointer manipulation in a Doubly Linked List. Find the absolute Minimum and move it to the `HEAD`. Find the Maximum and move it to the `TAIL`. Find the exact middle node in one pass.
**Deep Dive:** Detaching a node requires bypassing it (`node->prev->next = node->next`). The middle node is found using the "Tortoise and Hare" algorithm (slow and fast pointers).

### 📝 Pseudocode (Move to Ends & Tortoise/Hare)
```text
function moveMinToFirst(head):
    minNode = findMinNode(head)
    if minNode == head: return
    
    // Detach minNode
    minNode->prev->next = minNode->next
    if minNode->next != NULL:
        minNode->next->prev = minNode->prev
        
    // Attach to Head
    minNode->next = head
    minNode->prev = NULL
    head->prev = minNode
    head = minNode

function findMiddle(head):
    slow = head
    fast = head
    
    // Fast moves 2x speed, Slow moves 1x speed
    while fast != NULL AND fast->next != NULL:
        fast = fast->next->next
        slow = slow->next
        
    return slow->data // Slow is at exact middle
```
