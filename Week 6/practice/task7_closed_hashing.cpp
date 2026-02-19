/*
================================================================================
CLOSED HASHING (OPEN ADDRESSING)
================================================================================

CONCEPT:
--------
All elements stored directly in array (no linked lists).
Collision? Find next empty spot by PROBING.

Example:
Insert 13: hash(13)=3, table[3] = 13
Insert 23: hash(23)=3, occupied! Try 4, table[4] = 23
Insert 33: hash(33)=3, occupied! Try 4, occupied! Try 5, table[5] = 33

Table:
[_][_][_][13][23][33][_][_][_][_]
         3   4   5

No pointers - just array!

Python:
table = [None] * 10
index = hash(key)
while table[index] is not None:
    index = (index + 1) % 10
table[index] = key
*/

#include <iostream>
using namespace std;

struct Entry {
    int data;
    int status;  // 0=empty, 1=occupied, 2=deleted
};

Entry HT[10];
int Size = 10;

void insert(int val) {
    int index = val % Size;
    int i = 0;
    
    while (i < Size) {
        int pos = (index + i) % Size;  // Linear probing
        
        if (HT[pos].status != 1) {  // Empty or deleted
            HT[pos].data = val;
            HT[pos].status = 1;
            cout << "Inserted " << val << " at index " << pos;
            if (i > 0) cout << " (probed " << i << " times)";
            cout << endl;
            return;
        }
        i++;
    }
    cout << "Table FULL!" << endl;
}

void search(int val) {
    int index = val % Size;
    int i = 0;
    
    while (i < Size) {
        int pos = (index + i) % Size;
        
        if (HT[pos].status == 0) {  // Empty - not found
            cout << val << " not found" << endl;
            return;
        }
        
        if (HT[pos].status == 1 && HT[pos].data == val) {
            cout << "Found " << val << " at index " << pos << endl;
            return;
        }
        i++;
    }
    cout << val << " not found" << endl;
}

void display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < Size; i++) {
        cout << i << ": ";
        if (HT[i].status == 1) {
            cout << HT[i].data;
        } else if (HT[i].status == 2) {
            cout << "DELETED";
        } else {
            cout << "EMPTY";
        }
        cout << endl;
    }
}

int main() {
    // Initialize
    for (int i = 0; i < Size; i++) {
        HT[i].data = -1;
        HT[i].status = 0;  // Empty
    }
    
    cout << "=== CLOSED HASHING (OPEN ADDRESSING) ===\n\n";
    
    // Insert with collisions
    insert(3);
    insert(13);   // Collision at 3, goes to 4
    insert(23);   // Collision at 3,4, goes to 5
    insert(5);
    insert(15);   // Collision at 5, goes to 6
    insert(7);
    
    display();
    
    // Search
    cout << "\nSearching:\n";
    search(13);
    search(23);
    search(5);
    search(100);
    
    return 0;
}

/*
EXPLANATION:
------------

1. CLOSED HASHING (OPEN ADDRESSING)
   
   "Closed" = closed to new chains
   "Open" = open to finding address
   
   All data in main array
   No linked lists!

2. LINEAR PROBING
   
   Formula: (hash + i) % Size
   where i = 0, 1, 2, 3, ...
   
   Example inserting 23:
   hash(23) = 23 % 10 = 3
   
   Try (3+0)%10 = 3  ← occupied by 13
   Try (3+1)%10 = 4  ← occupied by something
   Try (3+2)%10 = 5  ← empty! Insert here

3. STATUS VALUES
   
   0 = EMPTY (never used)
   1 = OCCUPIED (has data)
   2 = DELETED (was occupied, now removed)
   
   Why DELETED state?
   
   Without it:
   Insert 13 at index 3
   Insert 23 at index 4 (probed from 3)
   Delete 13 → index 3 becomes EMPTY
   Search 23 → starts at hash(23)=3
              sees EMPTY at 3
              STOPS searching!
              Can't find 23 even though it's at 4!
   
   With DELETED:
   Delete 13 → index 3 becomes DELETED
   Search 23 → starts at 3
              sees DELETED
              CONTINUES probing
              Finds 23 at 4!

4. INSERT ALGORITHM
   
   index = hash(val)
   i = 0
   while (i < Size):
       pos = (index + i) % Size
       if HT[pos] is empty or deleted:
           Insert here
           Return
       i++
   
   If loop completes: Table full

5. SEARCH ALGORITHM
   
   index = hash(val)
   i = 0
   while (i < Size):
       pos = (index + i) % Size
       if HT[pos] is empty:
           Not found (would have been here)
           Return
       if HT[pos] has val:
           Found!
           Return
       i++
   Not found

6. CLUSTERING PROBLEM
   
   Primary clustering:
   Consecutive occupied cells form clusters
   
   Example:
   [_][_][A][B][C][D][_][_][_][_]
          Cluster!
   
   New element hashing to 2,3,4,5 must probe through entire cluster
   Makes operations slower

7. ADVANTAGES
   ✓ No extra memory for pointers
   ✓ Cache friendly (array)
   ✓ Simple implementation
   ✓ Good for small datasets

8. DISADVANTAGES
   ✗ Fixed size (can become full)
   ✗ Clustering degrades performance
   ✗ Deletion is complex (need DELETED state)
   ✗ Performance drops as table fills

9. TIME COMPLEXITY
   
   Average case:
   - Insert: O(1)
   - Search: O(1)
   - Delete: O(1)
   
   Worst case (high load factor):
   - All operations: O(n)
   
   Keep load factor α < 0.7
   α = elements / size

10. LOAD FACTOR
    
    α = n / m
    n = number of elements
    m = table size
    
    α = 0.5 → 50% full, very fast
    α = 0.7 → 70% full, good performance
    α = 0.9 → 90% full, slow! Resize table
    
    When α > 0.7, create larger table and rehash

11. PROBING STRATEGIES
    
    Linear: (hash + i) % Size
    - Simple
    - Clustering problem
    
    Quadratic: (hash + i²) % Size
    - Reduces clustering
    - May not probe all positions
    
    Double hashing: (hash1 + i*hash2) % Size
    - Best distribution
    - More complex

12. COMPARISON
    
    Open (Chaining):
    ✓ Never full
    ✓ Simple deletion
    ✗ Extra memory
    
    Closed (Addressing):
    ✓ Less memory
    ✓ Better cache
    ✗ Can become full
    ✗ Complex deletion
*/
