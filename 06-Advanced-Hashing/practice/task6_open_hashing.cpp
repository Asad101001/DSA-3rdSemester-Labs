/*
================================================================================
OPEN HASHING (SEPARATE CHAINING)
================================================================================

CONCEPT:
--------
Each index in array holds a LINKED LIST.
Collisions? Add to the list!

Example:
Index 0: NULL
Index 1: [11]→[21]→[31]→NULL
Index 2: [12]→[22]→NULL
Index 3: NULL
...

hash(11) = 1
hash(21) = 1  ← Collision! Add to list at index 1
hash(31) = 1  ← Another collision! Add to list

No probing needed - just add to chain!

Python:
table = [[] for _ in range(10)]
table[hash(key)].append(value)
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node HT[10];      // Hash table array
int Size = 10;

void insert(int val) {
    int index = val % Size;  // Hash function: modulo
    
    if (HT[index].data == -1) {
        // First element at this index
        HT[index].data = val;
    } else {
        // Collision - add to linked list
        Node* curr = new Node;
        curr->data = val;
        curr->next = HT[index].next;
        HT[index].next = curr;
    }
    cout << "Inserted " << val << " at index " << index << endl;
}

void search(int val) {
    int index = val % Size;
    
    // Check first node
    if (HT[index].data == val) {
        cout << "Found " << val << " at index " << index << " (position 0)" << endl;
        return;
    }
    
    // Check linked list
    Node* temp = HT[index].next;
    int pos = 1;
    
    while (temp != NULL) {
        if (temp->data == val) {
            cout << "Found " << val << " at index " << index << " (position " << pos << ")" << endl;
            return;
        }
        temp = temp->next;
        pos++;
    }
    
    cout << val << " not found" << endl;
}

void display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < Size; i++) {
        cout << i << ": ";
        
        if (HT[i].data == -1) {
            cout << "EMPTY";
        } else {
            cout << HT[i].data;
            Node* temp = HT[i].next;
            while (temp != NULL) {
                cout << "→" << temp->data;
                temp = temp->next;
            }
        }
        cout << endl;
    }
}

int main() {
    // Initialize table
    for (int i = 0; i < Size; i++) {
        HT[i].data = -1;
        HT[i].next = NULL;
    }
    
    cout << "=== OPEN HASHING (SEPARATE CHAINING) ===\n\n";
    
    // Insert values
    insert(3);
    insert(13);   // Collision with 3
    insert(23);   // Collision with 3,13
    insert(5);
    insert(15);   // Collision with 5
    insert(7);
    insert(27);   // Collision with 7
    
    display();
    
    // Search
    cout << "\nSearching:\n";
    search(13);
    search(5);
    search(27);
    search(100);
    
    return 0;
}

/*
EXPLANATION:
------------

1. HASH FUNCTION
   val % Size
   
   Examples:
   13 % 10 = 3
   23 % 10 = 3  ← Same index!
   5 % 10 = 5
   
   Distributes values across array

2. SEPARATE CHAINING
   Each array index has:
   - Main node (in array itself)
   - Linked list for collisions
   
   Index 3: HT[3] stores first value (3)
            HT[3].next → linked list (13→23→NULL)

3. INSERT OPERATION
   
   Step 1: Calculate index
   index = val % Size
   
   Step 2: Check if index empty
   If HT[index].data == -1:
       Store directly
   Else:
       Add to linked list
   
   Example inserting 13:
   index = 13 % 10 = 3
   HT[3].data = 3 (occupied)
   Create node with 13
   Link: HT[3].next = [13]→NULL

4. SEARCH OPERATION
   
   Step 1: Calculate index
   index = val % Size
   
   Step 2: Check main node
   If HT[index].data == val:
       Found!
   
   Step 3: Traverse linked list
   temp = HT[index].next
   while (temp != NULL):
       if temp->data == val:
           Found!
       temp = temp->next

5. ADVANTAGES
   ✓ Simple to implement
   ✓ Never "full" - chains grow
   ✓ Good for unknown data size
   ✓ Deletion is easy
   ✓ Less clustering than closed hashing

6. DISADVANTAGES
   ✗ Extra memory for pointers
   ✗ Cache unfriendly (pointers scattered)
   ✗ Chains can become long
   ✗ Performance degrades if many collisions

7. TIME COMPLEXITY
   Average: O(1 + α) where α = load factor
   
   Load factor = n/m
   n = number of elements
   m = table size
   
   If α < 1: Average O(1)
   If α >> 1: Chains get long, O(n) worst case
   
   Keep α around 0.7 for good performance

8. SPACE COMPLEXITY
   O(n + m)
   n = elements (nodes)
   m = table size (array)

9. OPEN vs CLOSED HASHING
   
   OPEN (Separate Chaining):
   - Uses linked lists
   - Never full
   - Simple deletion
   - Extra memory for pointers
   
   CLOSED (Open Addressing):
   - Array only
   - Can become full
   - Complex deletion
   - Better cache performance

10. HASH FUNCTION QUALITY
    Good hash function:
    - Distributes uniformly
    - Fast to compute
    - Deterministic (same input = same output)
    
    val % Size is simple but:
    - Works well if values distributed
    - Poor if values clustered (e.g., multiples of 10)
    
    Better hash for strings:
    h = 0
    for each char c:
        h = (h * prime + c) % Size
*/
