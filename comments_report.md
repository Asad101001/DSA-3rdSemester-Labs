# Comments Found in Repository

**Total Comments Found:** 550

The following files contain comments. Review them to decide which ones to remove.


## `00-Intro-to-CPP\beginner\dsa_intro.cpp` (73 comments)
```cpp
L1: // Detailed Introduction to Data Structures and Algorithms (DSA) Concepts for Beginners in C++
L2: // This file provides a comprehensive overview of fundamental DSA concepts with C++ implementations.
L3: // Each section includes explanations, code examples, and key points to understand.
L5: // Include necessary headers
L14: // ===========================================
L15: // 1. ARRAYS
L16: // ===========================================
L17: // Arrays are fixed-size containers that store elements of the same type in contiguous memory.
L18: // Time Complexity: Access O(1), Insert/Delete O(n) in worst case.
L19: // Use cases: When size is known and doesn't change frequently.
L24: // Static array
L27: // Accessing elements
L34: // Dynamic array using vector (recommended in C++)
L36: vec.push_back(6); // Add element
L44: // ===========================================
L45: // 2. LINKED LISTS
L46: // ===========================================
L47: // Linked lists are dynamic data structures where elements are stored in nodes.
L48: // Each node contains data and a pointer to the next node.
L49: // Time Complexity: Access O(n), Insert/Delete O(1) at known position.
L50: // Use cases: When frequent insertions/deletions are needed.
L61: // Creating nodes
L66: // Traversing
L75: // Using std::list (doubly linked list)
L84: // Clean up memory
L90: // ===========================================
L91: // 3. STACKS
L92: // ===========================================
L93: // Stacks follow LIFO (Last In, First Out) principle.
L94: // Operations: push (add), pop (remove), top (peek).
L95: // Time Complexity: All operations O(1).
L96: // Use cases: Function calls, undo operations, expression evaluation.
L110: // Manual stack implementation
L121: // ===========================================
L122: // 4. QUEUES
L123: // ===========================================
L124: // Queues follow FIFO (First In, First Out) principle.
L125: // Operations: enqueue (add), dequeue (remove), front (peek).
L126: // Time Complexity: All operations O(1).
L127: // Use cases: Task scheduling, breadth-first search.
L141: // Manual queue implementation
L152: // ===========================================
L153: // 5. SORTING ALGORITHMS
L154: // ===========================================
L155: // Sorting arranges elements in a specific order (ascending/descending).
L156: // Common algorithms: Bubble Sort, Insertion Sort, Selection Sort.
L158: // Bubble Sort: Repeatedly swap adjacent elements if they are in wrong order.
L159: // Time Complexity: O(n^2) worst/average, O(n) best case.
L171: // Insertion Sort: Build sorted array one element at a time.
L172: // Time Complexity: O(n^2) worst/average, O(n) best case.
L186: // Selection Sort: Find minimum element and place it at beginning.
L187: // Time Complexity: O(n^2) always.
L210: // Bubble Sort
L217: // Insertion Sort
L224: // Selection Sort
L232: // ===========================================
L233: // 6. SEARCHING ALGORITHMS
L234: // ===========================================
L235: // Searching finds the position of a target element in a data structure.
L237: // Linear Search: Check each element sequentially.
L238: // Time Complexity: O(n)
L246: // Binary Search: Divide and conquer on sorted array.
L247: // Time Complexity: O(log n)
L265: // Linear Search
L271: // Binary Search
L278: // ===========================================
L279: // 7. TIME COMPLEXITY BASICS
L280: // ===========================================
L281: // Time complexity measures how the runtime of an algorithm grows with input size.
L282: // Common complexities: O(1), O(log n), O(n), O(n log n), O(n^2), O(2^n)
L295: // ===========================================
L296: // MAIN FUNCTION
L297: // ===========================================
```

## `00-Intro-to-CPP\beginner+\03_functions_pass_by.cpp` (12 comments)
```cpp
L21: // x = 50; ERROR: can't modify const reference
L43: // ============ TESTING PASS BY VALUE ============
L48: cout << "After: " << num1 << endl;  // Still 10 - unchanged
L50: // ============ TESTING PASS BY REFERENCE ============
L55: cout << "After: " << num2 << endl;  // Changed to 200
L57: // ============ TESTING PASS BY POINTER ============
L61: passByPointer(&num3);  // Pass address
L62: cout << "After: " << num3 << endl;  // Changed to 300
L64: // ============ TESTING CONST REFERENCE ============
L69: // ============ TESTING ARRAY MODIFICATION ============
L79: // ============ RETURN BY REFERENCE ============
L82: getElement(myArray, 2) = 999;  // Can assign to it!
```

## `00-Intro-to-CPP\beginner+\04_dynamic_memory.cpp` (17 comments)
```cpp
L76: // BAD: Memory leak
L80: // Never deleted - memory leaked!
L82: // 3 integers worth of memory lost forever (until program ends)
L84: // GOOD: Proper cleanup
L88: delete noLeak;  // Properly freed
L91: // ============ DANGLING POINTERS ============
L98: // ptr3 now points to freed memory (dangling pointer)
L99: // Accessing it is undefined behavior
L100: // cout << *ptr3 << endl;  // DANGEROUS - don't do this
L102: ptr3 = nullptr;  // Good practice - makes it safe to check
L112: /*
L142: Node* newNode = new Node();  // Allocate on heap
L143: // ... use the node ...
L144: delete newNode;  // Clean up when done
L162: C++: int* arr = new int[3]; // You control memory
L163: // ... use array ...
L164: delete[] arr;  // You clean up
```

## `01-Searching-and-Sorting\Home Task\assisted practice\bubbleSort.cpp` (29 comments)
```cpp
L1: // 11_sorting_comparison.cpp
L2: // Side-by-side comparison and performance analysis
L12: // ============ INSTRUMENTED VERSIONS ============
L13: // Track comparisons, swaps, and passes
L32: // Bubble Sort with statistics
L62: // Selection Sort with statistics
L93: // ============ COMPARISON TESTS ============
L108: // Test Bubble Sort
L113: // Test Selection Sort
L118: // Comparison
L138: // ============ VISUALIZATION ============
L146: // Print initial state
L152: // Bubble sort visualization
L158: // Show comparison
L187: // Selection sort visualization
L223: // ============ PRACTICE PROBLEMS ============
L234: // Simulate one pass
L253: // Find minimum and swap
L288: // ============ MAIN ============
L293: // Test 1: Random array
L297: // Test 2: Already sorted (best case for bubble)
L301: // Test 3: Reverse sorted (worst case)
L305: // Test 4: Nearly sorted
L309: // Test 5: Many duplicates
L313: // Test 6: Large array
L318: // Visualizations
L329: // Practice problems
L332: // Summary table
L356: /*
```

## `02-Singly-Linked-Lists\Home Task\linkedlist.cpp` (3 comments)
```cpp
L15: //This method below is more C than  C++, leading to some discrepancies
L17: //only writing Node* temp; -> works in C not C++
L18: //temp = (Node *)malloc(sizeof(Node)); //malloc -> allocates memory & sizeof defines size in bits of memory to be allocated : Node
```

## `02-Singly-Linked-Lists\Lab Task\linkedList_InsertionAndDisplay.cpp` (2 comments)
```cpp
L13: Node* temp = new Node();  //only writing Node* temp; -> works in C not C++
L14: // temp = (Node *)malloc(sizeof(Node)); //malloc -> allocates memory & sizeof defines size in bits of memory to be allocated : Node
```

## `03-Doubly-and-Circular-Lists\Lab Task\linkedList_Delete.cpp` (2 comments)
```cpp
L13: Node* temp = new Node();  //only writing Node* temp; -> works in C not C++
L14: // temp = (Node *)malloc(sizeof(Node)); //malloc -> allocates memory & sizeof defines size in bits of memory to be allocated : Node
```

## `04-Stacks-and-Queues\Lab Task\dynamicQueue.cpp` (3 comments)
```cpp
L59: //Added elements to rear
L65: //Removed (dequeued) element from front
L69: //Emptyin' the queue
```

## `05-Hash-Tables\Home Task\task3_templates.cpp` (84 comments)
```cpp
L1: /*
L13: template <typename T>    // T is a placeholder for any type
L17: template <class T>       // Equivalent to typename
L25: // Must rewrite same logic for each type!
L30: // Write once, use for all types!
L52: //==============================================================================
L53: // PART 1: TEMPLATE STACK (LINKED LIST IMPLEMENTATION)
L54: //==============================================================================
L56: /*
L63: T data;              // Can be int, double, string, or any type
L64: StackNode<T>* next;  // Pointer to next node
L66: /*
L80: /*
L86: StackNode<T>* top;  // Pointer to top node
L87: int size;           // Number of elements
L90: /*
L96: // Initialize stack
L103: // Check if empty
L109: // Get size
L115: // Push operation - O(1)
L118: // Create new node
L123: // Update top
L127: /*
L132: newNode->data = 42;  // Stores integer
L136: newNode->data = "hello";  // Stores string
L142: // Pop operation - O(1)
L160: // Peek operation - O(1)
L170: // Display stack
L187: // Destroy stack
L195: //==============================================================================
L196: // PART 2: TEMPLATE QUEUE (LINKED LIST IMPLEMENTATION)
L197: //==============================================================================
L199: /*
L209: /*
L220: /*
L225: // Initialize queue
L233: // Check if empty
L239: // Get size
L245: // Enqueue operation - O(1)
L264: // Dequeue operation - O(1)
L286: // Front operation - O(1)
L296: // Display queue
L313: // Destroy queue
L321: //==============================================================================
L322: // PART 3: CUSTOM DATA TYPE EXAMPLE
L323: //==============================================================================
L325: /*
L335: // Overload << operator for easy printing
L342: //==============================================================================
L343: // DEMONSTRATIONS
L344: //==============================================================================
L351: // 1. Stack of integers
L363: // 2. Stack of doubles
L374: // 3. Stack of strings
L384: // 4. Stack of custom type (Student)
L401: /*
L413: // Cleanup
L425: // 1. Queue of integers
L437: // 2. Queue of characters
L448: // 3. Queue of strings
L458: // 4. Queue of custom type
L475: // Cleanup
L482: //==============================================================================
L483: // TEMPLATE SPECIALIZATION EXAMPLE (ADVANCED)
L484: //==============================================================================
L486: /*
L495: // Specialized display for bool stack
L524: displayStack(&boolStack);  // Uses specialized version
L529: //==============================================================================
L530: // PRACTICAL APPLICATION: Expression Evaluator
L531: //==============================================================================
L538: // Expression: 5 3 + 2 *  (means: (5+3)*2 = 16)
L545: // Push 5
L550: // Push 3
L555: // Addition (+)
L562: // Push 2
L567: // Multiplication (*)
L579: //==============================================================================
L580: // MAIN FUNCTION
L581: //==============================================================================
L600: /*
L619: T data;  // T can be any type
L624: // Use T as if it's a normal type
L638: // Special behavior for int only
```

## `05-Hash-Tables\Home Task\task4_hashtable.cpp` (78 comments)
```cpp
L1: /*
L53: //==============================================================================
L54: // CONSTANTS AND ENUMS
L55: //==============================================================================
L57: const int TABLE_SIZE = 11;  // Prime number for better distribution
L59: // Status of each cell in hash table
L61: EMPTY,     // Never used
L62: OCCUPIED,  // Currently has data
L63: DELETED    // Had data but was deleted (important for probing!)
L66: /*
L80: //==============================================================================
L81: // HASH TABLE ENTRY
L82: //==============================================================================
L86: K key;               // The key (e.g., "Alice")
L87: V value;             // The value (e.g., phone number)
L88: CellStatus status;   // EMPTY, OCCUPIED, or DELETED
L90: HashEntry() : status(EMPTY) {}  // Default constructor
L93: //==============================================================================
L94: // HASH TABLE STRUCTURE
L95: //==============================================================================
L99: HashEntry<K, V>* table;  // Array of entries
L100: int size;                // Current number of elements
L101: int capacity;            // Maximum capacity
L103: /*
L112: //==============================================================================
L113: // HASH FUNCTIONS
L114: //==============================================================================
L116: /*
L127: /*
L144: /*
L159: // Generic hash function (we'll use string version)
L162: // For demonstration, we'll assume K is string
L163: // In real implementation, you'd specialize for different types
L167: //==============================================================================
L168: // LINEAR PROBING HASH TABLE
L169: //==============================================================================
L171: /*
L214: /*
L225: // Calculate initial hash
L227: int i = 0;  // Probe counter
L229: // Linear probing: try index, index+1, index+2, ...
L233: /*
L245: // Check if spot is available
L249: // Found empty spot - insert here
L263: // If key already exists, update value
L271: i++;  // Try next position
L277: /*
L289: // If empty (never used), key doesn't exist
L294: // If occupied and key matches, found it!
L301: // If deleted or wrong key, continue probing
L305: return false;  // Not found after checking entire table
L308: /*
L321: return false;  // Not found
L327: // Mark as DELETED (not EMPTY!)
L340: /*
L367: //==============================================================================
L368: // QUADRATIC PROBING HASH TABLE
L369: //==============================================================================
L371: /*
L418: /*
L433: // Quadratic probing: (index + i²) % capacity
L436: /*
L484: /*
L512: /*
L543: /*
L570: //==============================================================================
L571: // DEMONSTRATIONS
L572: //==============================================================================
L590: // Search
L601: // Delete
L606: // Insert after delete
L628: // Search
L635: // Delete
L640: // Insert after delete
L672: //==============================================================================
L673: // MAIN FUNCTION
L674: //==============================================================================
L692: /*
```

## `06-Advanced-Hashing\mutli_list.cpp` (25 comments)
```cpp
L326: if (Scurr==NULL) // if the stu list is empty
L360: Scurr=Scurr->Snext; // moves forward the scurr to the second elemnt
L362: prev=Ccurr->stu_list; // prev points to the stu_list
L393: SNode* temp = Scurr; // Store node to free it later
L395: if (prev == NULL) // Case: Student is at the head
L398: Scurr = Ccurr->stu_list; // Move Scurr to the new head
L400: else // Case: Student is in the middle or end
L403: Scurr = prev->Snext; // Move Scurr to the next valid node
L436: while(Ccurr!=NULL) // this for the loop to run until the Ccurr is not null for the course traversing
L440: if (value==Ccurr->CNo) // first case if the value matches the first course in the list
L442: Clist=Clist->Cnext; // joins the course list to the second elemnt
L443: SNode* Scurr = Ccurr->stu_list; // scurr points to the stu_list
L445: while(Scurr!=NULL) // iterates until the scurr is not null
L447: Ccurr->stu_list=Ccurr->stu_list->Snext;  //joins the stu list to the list's second elemnt
L449: free(Scurr); // frees the scurr which is in first run is at first elemnt
L451: Scurr= Ccurr->stu_list; // points the scurr again at the list's first elemnt so that the elemnt deletion is always from the first element
L452: // Scurr=Scurr->Snext;
L454: free(Ccurr); // when the scurr is null and all the students gets deleted the Ccurr is now freed
L455: return; // returned from here so that now the Ccurr is not moved to the next
L468: while(Scurr!=NULL) // iterates until the scurr is not null
L472: free(Scurr); // frees the scurr which is in first run is at first elemnt
L477: free(Ccurr); // when the scurr is null and all the students gets deleted the Ccurr is now freed
L495: while(Ccurr!=NULL) // while loop for the course lists
L503: while(Scurr!=NULL) // another while loop for the student list
L510: // }
```

## `06-Advanced-Hashing\quadraticProbing.cpp` (4 comments)
```cpp
L9: hashTable[i] = -1;  // -1 means empty
L18: int i = 0;  // step counter
L21: int newIndex = (index + i * i) % SIZE;  // quadratic probing
L44: if (hashTable[newIndex] == -1) break; // empty spot, key not present
```

## `06-Advanced-Hashing\practice\task1_circular_queue.cpp` (4 comments)
```cpp
L12: CircularQueue q;  // Global queue
L20: q.rear = (q.rear + 1) % q.capacity;  // Circular increment
L33: q.front = (q.front + 1) % q.capacity;  // Circular increment
L83: /*
```

## `06-Advanced-Hashing\practice\task2_linked_queue.cpp` (13 comments)
```cpp
L1: /*
L39: Queue q;  // Global queue
L42: Node* curr = new Node;  // Allocate memory
L47: // First element
L51: // Add to rear
L69: // CRITICAL: If empty now, update rear too!
L74: delete temp;  // Free memory
L95: // Initialize
L102: // Add elements
L110: // Remove 2
L116: // Add more (shows dynamic growth)
L123: // Remove all
L134: /*
```

## `06-Advanced-Hashing\practice\task3_stack_queue.cpp` (24 comments)
```cpp
L1: /*
L25: //==============================================================================
L26: // STACK
L27: //==============================================================================
L39: Stack s;  // Global stack
L78: //==============================================================================
L79: // QUEUE
L80: //==============================================================================
L93: Queue q;  // Global queue
L144: //==============================================================================
L145: // MAIN
L146: //==============================================================================
L149: // Initialize stack
L153: // Initialize queue
L160: // Demonstrate Stack (LIFO)
L171: cout << "Popped: " << pop() << endl;  // 50 (last in)
L172: cout << "Popped: " << pop() << endl;  // 40
L175: // Demonstrate Queue (FIFO)
L186: cout << "Dequeued: " << dequeue() << endl;  // 10 (first in)
L187: cout << "Dequeued: " << dequeue() << endl;  // 20
L190: // Show the difference
L203: // Add same data to both
L222: // Remove all and show order
L244: /*
```

## `06-Advanced-Hashing\practice\task4_hashtable.cpp` (18 comments)
```cpp
L1: /*
L31: int status;  // 0=empty, 1=occupied, 2=deleted
L34: Entry table[11];  // Global hash table (size 11 - prime number)
L45: //==============================================================================
L46: // LINEAR PROBING
L47: //==============================================================================
L54: int pos = (index + i) % Size;  // Linear: i=0,1,2,3...
L56: if (table[pos].status != 1) {  // Not occupied
L66: if (strcmp(table[pos].key, key) == 0) {  // Update
L81: if (table[pos].status == 0) {  // Empty
L95: //==============================================================================
L96: // QUADRATIC PROBING
L97: //==============================================================================
L104: int pos = (index + i*i) % Size;  // Quadratic: i²=0,1,4,9,16...
L159: // Initialize
L161: table[i].status = 0;  // Empty
L178: // Reset for quadratic
L199: /*
```

## `06-Advanced-Hashing\practice\task5_recursive_display.cpp` (15 comments)
```cpp
L1: /*
L30: Node* head = NULL;  // Global list head
L50: return;  // Base case: reached end
L53: cout << node->data << " ";     // Print current
L54: displayForward(node->next);    // Recurse on rest
L59: return;  // Base case
L62: displayReverse(node->next);    // Recurse FIRST
L63: cout << node->data << " ";     // Print AFTER recursion
L93: /*
L109: if (node == NULL) return;  // Base case
L110: cout << node->data;         // Process
L111: displayForward(node->next); // Recurse
L124: if (node == NULL) return;   // Base case
L125: displayReverse(node->next); // Recurse FIRST
L126: cout << node->data;          // Process AFTER
```

## `06-Advanced-Hashing\practice\task6_open_hashing.cpp` (15 comments)
```cpp
L1: /*
L37: Node HT[10];      // Hash table array
L41: int index = val % Size;  // Hash function: modulo
L44: // First element at this index
L47: // Collision - add to linked list
L59: // Check first node
L65: // Check linked list
L101: // Initialize table
L109: // Insert values
L111: insert(13);   // Collision with 3
L112: insert(23);   // Collision with 3,13
L114: insert(15);   // Collision with 5
L116: insert(27);   // Collision with 7
L120: // Search
L130: /*
```

## `06-Advanced-Hashing\practice\task7_closed_hashing.cpp` (13 comments)
```cpp
L1: /*
L35: int status;  // 0=empty, 1=occupied, 2=deleted
L46: int pos = (index + i) % Size;  // Linear probing
L48: if (HT[pos].status != 1) {  // Empty or deleted
L68: if (HT[pos].status == 0) {  // Empty - not found
L98: // Initialize
L101: HT[i].status = 0;  // Empty
L106: // Insert with collisions
L108: insert(13);   // Collision at 3, goes to 4
L109: insert(23);   // Collision at 3,4, goes to 5
L111: insert(15);   // Collision at 5, goes to 6
L116: // Search
L126: /*
```

## `07-Binary-Search-Trees\Sorting Algorithm\non-recursiveSort.cpp` (2 comments)
```cpp
L50: //
L60: //
```

## `07-Binary-Search-Trees\Sorting Algorithm\recursiveSort.cpp` (1 comments)
```cpp
L62: //
```

## `08-BST-Deletion\deletionBST.cpp` (4 comments)
```cpp
L76: //0 child
L82: //1 child on right
L89: //1 child on left
L96: //2 children
```

## `11-Expression-Trees\ex-tree.cpp` (7 comments)
```cpp
L23: /* ---------- STACK (CHAR) ---------- */
L49: /* ---------- STACK (ETNode) ---------- */
L66: /* ---------- HELPERS ---------- */
L93: /* ---------- INFIX → POSTFIX ---------- */
L125: /* ---------- POSTFIX → TREE ---------- */
L151: /* ---------- TRAVERSAL ---------- */
L159: /* ---------- MAIN ---------- */
```

## `13-Graphs\adj_list.cpp` (2 comments)
```cpp
L98: //for edge from v1 to v2
L112: //for edge from v2 to v1
```

## `13-Graphs\AjacencyList.cpp` (8 comments)
```cpp
L23: // ================= QUEUE STRUCTURE =================
L33: // ================= QUEUE FUNCTIONS =================
L67: // ================= GRAPH FUNCTIONS =================
L113: // v1 -> v2
L128: // v2 -> v1 (undirected)
L190: // ================= BFS FUNCTION =================
L197: // reset visited
L231: // ================= MAIN =================
```

## `13-Graphs\graph.cpp` (45 comments)
```cpp
L47: if (front ==NULL & rear == NULL) // if both front and rear is null the assign the temp to front and rear which is the first cond if queueing the first elemnt
L51: // temp->next=front;
L59: rear->next=temp; // used the rear because it is always pointing to the end
L60: rear=temp;  // then we point the rear to the new last elemnt
L62: // temp->next=front;
L81: if(front==NULL) // cond 1 queue is empty
L87: if (front==rear) // cond 2 only one element present
L98: else // cond 3 more than one element
L100: // rear->next=front->next;
L114: // int arrmat[5][5];
L119: vertex*temp;  // temp for the courses
L122: temp->vnext=NULL;  //
L125: temp->edgelist=NULL; //
L405: // void MatrixForm()
L406: // {
L407: //     int n=5;
L408: //     int arraymat[n][n];
L410: //     for (size_t i = 0; i < n; i++)
L411: //     {
L412: //         for (size_t j = 0; j < n; j++)
L413: //         {
L414: //             arraymat[i][j]=0;
L415: //         }
L417: //     }
L420: //     vertex* curr=graph;
L424: //     int i=0;
L425: //     int j=0;
L426: //     while(curr!=NULL)
L427: //     {
L428: //         edge* ecurr=curr->edgelist;
L430: //         while (ecurr!=NULL)
L431: //         {
L432: //             if (ecurr->v->data==curr->data)
L433: //             {
L434: //                 arraymat[i][j]=1;
L435: //             }
L436: //             j++;
L437: //             curr=curr->vnext;
L438: //         }
L440: //         ecurr=ecurr->enext;
L442: //     }
L447: // }
L492: // case 5:
L493: //     MatrixForm();
L494: //     break;
```

## `Practice\Binary Search Tree\BST.cpp` (47 comments)
```cpp
L121: // Node* minNode(Node* curr) {
L122: //     Node* temp = curr;
L123: //     while (temp->left != NULL) {
L124: //         temp = temp->left;
L125: //     }
L126: //     return temp;
L127: // }
L130: // Node* deleteNode(Node* curr, int val) {
L131: //     if (curr == NULL) {
L132: //         cout << "Value not found\n";
L133: //         return NULL;
L134: //     }
L136: //     if (val < curr->data) {
L137: //         curr->left = deleteNode(curr->left, val);
L138: //     }
L139: //     else if (val > curr->data) {
L140: //         curr->right = deleteNode(curr->right, val);
L141: //     }
L142: //     else {
L144: //         //0 child
L145: //         if (curr->left == NULL && curr->right == NULL) {
L146: //             delete curr;
L147: //             return NULL;
L148: //         }
L150: //         //1 child on right
L151: //         if (curr->left == NULL) {
L152: //             Node* temp = curr->right;
L153: //             delete curr;
L154: //             return temp;
L155: //         }
L157: //         //1 child on left
L158: //         if (curr->right == NULL) {
L159: //             Node* temp = curr->left;
L160: //             delete curr;
L161: //             return temp;
L162: //         }
L164: //         //2 children
L165: //         Node* temp = minNode(curr->right);
L166: //         curr->data = temp->data;
L167: //         curr->right = deleteNode(curr->right, temp->data);
L168: //     }
L170: //     return curr;
L171: // }
L178: //Insertions done both recursively and iteratively
L188: //Iterative searching
L200: //Recursive searching
L212: //All three forms of tree traversals done recursively
```