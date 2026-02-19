/*
================================================================================
HASH TABLE - LINEAR AND QUADRATIC PROBING
================================================================================

CONCEPT:
--------
Array + Hash function = Fast lookup!

hash("Alice") → 5  (store at index 5)
lookup("Alice") → check index 5  (O(1)!)

COLLISION:
Two keys hash to same index.
Solution: Probing (try next positions)

LINEAR: Try 5, 6, 7, 8, 9...
QUADRATIC: Try 5, 6, 9, 14, 21... (i²)

Python:
d = {"Alice": 25}
*/

#include <iostream>
#include <cstring>
using namespace std;

struct Entry {
    char key[50];
    int value;
    int status;  // 0=empty, 1=occupied, 2=deleted
};

Entry table[11];  // Global hash table (size 11 - prime number)
int Size = 11;

int hashFunc(const char* key) {
    int h = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        h = (h * 31 + key[i]) % Size;
    }
    return h;
}

//==============================================================================
// LINEAR PROBING
//==============================================================================

void insertLinear(const char* key, int val) {
    int index = hashFunc(key);
    int i = 0;
    
    while (i < Size) {
        int pos = (index + i) % Size;  // Linear: i=0,1,2,3...
        
        if (table[pos].status != 1) {  // Not occupied
            strcpy(table[pos].key, key);
            table[pos].value = val;
            table[pos].status = 1;
            cout << "Inserted " << key << " at index " << pos;
            if (i > 0) cout << " (probed " << i << " times)";
            cout << endl;
            return;
        }
        
        if (strcmp(table[pos].key, key) == 0) {  // Update
            table[pos].value = val;
            return;
        }
        i++;
    }
}

void searchLinear(const char* key) {
    int index = hashFunc(key);
    int i = 0;
    
    while (i < Size) {
        int pos = (index + i) % Size;
        
        if (table[pos].status == 0) {  // Empty
            cout << key << " not found" << endl;
            return;
        }
        
        if (table[pos].status == 1 && strcmp(table[pos].key, key) == 0) {
            cout << "Found " << key << ": " << table[pos].value << endl;
            return;
        }
        i++;
    }
    cout << key << " not found" << endl;
}

//==============================================================================
// QUADRATIC PROBING
//==============================================================================

void insertQuadratic(const char* key, int val) {
    int index = hashFunc(key);
    int i = 0;
    
    while (i < Size) {
        int pos = (index + i*i) % Size;  // Quadratic: i²=0,1,4,9,16...
        
        if (table[pos].status != 1) {
            strcpy(table[pos].key, key);
            table[pos].value = val;
            table[pos].status = 1;
            cout << "Inserted " << key << " at index " << pos;
            if (i > 0) cout << " (probed " << i << " times)";
            cout << endl;
            return;
        }
        
        if (strcmp(table[pos].key, key) == 0) {
            table[pos].value = val;
            return;
        }
        i++;
    }
}

void searchQuadratic(const char* key) {
    int index = hashFunc(key);
    int i = 0;
    
    while (i < Size) {
        int pos = (index + i*i) % Size;
        
        if (table[pos].status == 0) {
            cout << key << " not found" << endl;
            return;
        }
        
        if (table[pos].status == 1 && strcmp(table[pos].key, key) == 0) {
            cout << "Found " << key << ": " << table[pos].value << endl;
            return;
        }
        i++;
    }
    cout << key << " not found" << endl;
}

void display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < Size; i++) {
        cout << i << ": ";
        if (table[i].status == 1) {
            cout << table[i].key << "=" << table[i].value;
        } else {
            cout << "EMPTY";
        }
        cout << endl;
    }
}

int main() {
    // Initialize
    for (int i = 0; i < Size; i++) {
        table[i].status = 0;  // Empty
    }
    
    cout << "=== LINEAR PROBING ===\n\n";
    
    insertLinear("Alice", 25);
    insertLinear("Bob", 30);
    insertLinear("Charlie", 35);
    insertLinear("Diana", 28);
    insertLinear("Eve", 32);
    
    display();
    
    searchLinear("Charlie");
    searchLinear("Diana");
    searchLinear("Zoe");
    
    // Reset for quadratic
    cout << "\n=== QUADRATIC PROBING ===\n\n";
    
    for (int i = 0; i < Size; i++) {
        table[i].status = 0;
    }
    
    insertQuadratic("Alice", 25);
    insertQuadratic("Bob", 30);
    insertQuadratic("Charlie", 35);
    insertQuadratic("Diana", 28);
    insertQuadratic("Eve", 32);
    
    display();
    
    searchQuadratic("Alice");
    searchQuadratic("Eve");
    
    return 0;
}

/*
EXPLANATION:
------------

1. HASH FUNCTION
   Converts string to number
   
   hashFunc("Alice"):
   h = 0
   h = (0*31 + 'A') % 11 = 65 % 11 = 10
   h = (10*31 + 'l') % 11 = 418 % 11 = 0
   ... continues
   
   Goal: Distribute keys uniformly

2. LINEAR PROBING
   Formula: (hash + i) % size
   
   If hash("Alice") = 5 and occupied:
   Try (5+0)%11 = 5  <- occupied
   Try (5+1)%11 = 6  <- insert here
   
   Problem: CLUSTERING
   Consecutive occupied cells form clusters
   Makes further probing slower

3. QUADRATIC PROBING
   Formula: (hash + i²) % size
   
   If hash("Alice") = 5 and occupied:
   Try (5+0²)%11 = 5   <- occupied
   Try (5+1²)%11 = 6   <- occupied
   Try (5+4)%11 = 9    <- insert here
   Try (5+9)%11 = 3
   
   Advantage: Reduces clustering
   Jumps around instead of sequential

4. STATUS VALUES
   0 = Empty (never used)
   1 = Occupied (has data)
   2 = Deleted (had data, now removed)
   
   Why not just 0 and 1?
   
   Without deleted state:
   Insert "Alice" at 5
   Insert "Bob" at 6 (collided from 5)
   Delete "Alice" → 5 becomes empty
   Search "Bob" → starts at 5, sees empty, STOPS!
                 Can't find Bob!
   
   With deleted (2):
   Delete "Alice" → 5 becomes deleted
   Search "Bob" → starts at 5, sees deleted, CONTINUES
                 Finds Bob at 6!

5. TIME COMPLEXITY
   Average: O(1)
   Worst: O(n) when clustered
   
   Keep load factor < 0.7 for good performance
   Load factor = elements / size

6. SPACE
   O(n) where n = table size
   Fixed size array

7. PROS/CONS
   Linear Probing:
   ✓ Simple
   ✓ Cache friendly (sequential)
   ✗ Clustering problem
   
   Quadratic Probing:
   ✓ Less clustering
   ✗ May not probe all positions
   ✗ Needs prime table size
*/
