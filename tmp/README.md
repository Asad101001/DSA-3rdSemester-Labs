# 🎓 Data Structures & Algorithms in C++

```
    ____  _____    _    
   |  _ \/ ____|  / \   
   | | | \___ \ / _ \  
   | |_| |___) / ___ \ 
   |____/|____/_/   \_\
                        
   Journey Through Computer Science Fundamentals
```

> A comprehensive collection of DSA implementations documenting my learning journey through undergraduate computer science concepts.

[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/C++-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![Status](https://img.shields.io/badge/Status-Active-success.svg)]()

---

## 📚 Repository Structure

```
📦 DSA-CPP
├── 📁 Week 0 (Intro to C++)          → C++ Fundamentals
├── 📁 Week 1                          → Searching & Basic Sorting
├── 📁 Week 2                          → Linked Lists & Insertion Sort
├── 📁 Week 3                          → Advanced Linked Lists
├── 📁 Week 4                          → Stacks & Queues
├── 📁 Week 5                          → Hash Tables Introduction
├── 📁 Week 6                          → Open & Closed Hashing
├── 📁 Week 7                          → BST & Advanced Sorting
└── 📁 Week 8                          → BST Operations
```

---

## 🎯 Learning Path

### **Phase 1: Foundations** (Weeks 0-1)
- ✅ C++ Basics (pointers, references, dynamic memory)
- ✅ Linear & Binary Search
- ✅ Bubble & Selection Sort

### **Phase 2: Linear Structures** (Weeks 2-4)
- ✅ Singly Linked Lists
- ✅ Doubly Linked Lists
- ✅ Circular Linked Lists
- ✅ Stacks (Static & Dynamic)
- ✅ Queues (Circular & Dynamic)

### **Phase 3: Hash Tables** (Weeks 5-6)
- ✅ Hash Functions
- ✅ Linear Probing
- ✅ Quadratic Probing
- ✅ Open Hashing (Chaining)
- ✅ Multi-List Structures

### **Phase 4: Trees & Advanced Sorting** (Weeks 7-8)
- ✅ Binary Search Trees
- ✅ Quick Sort
- ✅ Merge Sort
- ✅ BST Operations (Insert, Delete, Search)

---

## 🔥 Featured Implementations

### **Circular Queue**
```cpp
void enQueue(int value) {
    if (count == SIZE) return;
    rear = (rear + 1) % SIZE;  // ← Circular magic!
    queue[rear] = value;
    count++;
}
```

### **Hash Table with Linear Probing**
```cpp
void insert(int value) {
    int index = value % SIZE;
    int i = 0;
    while (i < SIZE) {
        int pos = (index + i) % SIZE;  // Linear probing
        if (table[pos].status != OCCUPIED) {
            table[pos] = value;
            return;
        }
        i++;
    }
}
```

### **Recursive Linked List Display**
```cpp
void displayReverse(Node* node) {
    if (node == NULL) return;
    displayReverse(node->next);  // Recurse first
    cout << node->data << " ";   // Print after
}
```

---

## 📊 Complexity Quick Reference

| Data Structure | Access | Search | Insert | Delete |
|----------------|--------|--------|--------|--------|
| **Array** | O(1) | O(n) | O(n) | O(n) |
| **Linked List** | O(n) | O(n) | O(1)* | O(1)* |
| **Stack** | O(n) | O(n) | O(1) | O(1) |
| **Queue** | O(n) | O(n) | O(1) | O(1) |
| **Hash Table** | - | O(1)† | O(1)† | O(1)† |
| **BST** | O(log n)‡ | O(log n)‡ | O(log n)‡ | O(log n)‡ |

*At known position  
†Average case  
‡Balanced tree

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| **Bubble Sort** | O(n) | O(n²) | O(n²) | O(1) |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | O(1) |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) |

---

## 🛠️ Technologies & Tools

- **Language**: C++ (C++11 standard)
- **Compiler**: g++ 
- **IDE**: VS Code / Visual Studio
- **Build**: Manual compilation with g++

### Compilation Commands
```bash
# Standard compilation
g++ -std=c++11 filename.cpp -o output

# With warnings
g++ -std=c++11 -Wall -Wextra filename.cpp -o output

# With debugging symbols
g++ -std=c++11 -g filename.cpp -o output
```

---

## 📖 Key Concepts Covered

<details>
<summary><b>🔗 Linked Lists</b></summary>

- Singly Linked Lists
- Doubly Linked Lists
- Circular Linked Lists
- Insertion at various positions
- Deletion operations
- Searching and traversal
- Recursive operations

</details>

<details>
<summary><b>📚 Stacks & Queues</b></summary>

- Static implementation (arrays)
- Dynamic implementation (linked lists)
- Circular queues
- LIFO vs FIFO principles
- Applications and use cases

</details>

<details>
<summary><b>#️⃣ Hash Tables</b></summary>

- Hash functions (modulo, polynomial)
- Collision resolution:
  - Linear Probing
  - Quadratic Probing
  - Separate Chaining (Open Hashing)
- Load factor optimization
- Multi-list structures

</details>

<details>
<summary><b>🌳 Binary Search Trees</b></summary>

- BST properties
- Insertion algorithm
- Deletion (0, 1, 2 children cases)
- Traversals:
  - Inorder
  - Preorder
  - Postorder
- Searching operations

</details>

<details>
<summary><b>🔄 Sorting Algorithms</b></summary>

- Simple sorts: Bubble, Selection, Insertion
- Divide & Conquer: Merge Sort, Quick Sort
- Stability and in-place sorting
- Time complexity analysis

</details>

---

## 🎯 Learning Objectives Achieved

- ✅ Understanding pointers and dynamic memory management
- ✅ Implementing classic data structures from scratch
- ✅ Analyzing time and space complexity
- ✅ Solving collision problems in hash tables
- ✅ Mastering recursion through tree operations
- ✅ Comparing different algorithmic approaches

---

## 📝 Code Quality & Style

All implementations follow:
- **Clear naming conventions**
- **Comprehensive inline comments**
- **Step-by-step explanations**
- **Visual diagrams in comments**
- **Python comparisons for reference**
- **Real-world analogies**

### Example Comment Style
```cpp
/*
CIRCULAR QUEUE CONCEPT:
----------------------
Array with wraparound - when rear reaches end, it wraps to beginning

Example:
    [A][B][C][D][E]  capacity=5
    
    After dequeue 2 times: front=2
    [_][_][C][D][E]
    
    Enqueue wraps around:
    [G][H][C][D][E][F]  rear wraps to index 0, 1
     ^     ^
    rear  front

Formula: (index + 1) % capacity
*/
```

---

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++ recommended)
- Basic understanding of C++ syntax
- Terminal/Command prompt access

### Running the Code

1. **Clone the repository**
```bash
git clone <your-repo-url>
cd DSA-CPP
```

2. **Navigate to desired week**
```bash
cd "Week 4 (Introduction to Stack & Queue)"
```

3. **Compile**
```bash
g++ -std=c++11 staticQueue.cpp -o queue
```

4. **Run**
```bash
./queue        # Linux/Mac
queue.exe      # Windows
```

---

## 📈 Progress Tracking

```
Week 0  ████████████████████ 100%  C++ Fundamentals
Week 1  ████████████████████ 100%  Search & Sort Basics
Week 2  ████████████████████ 100%  Linked Lists
Week 3  ████████████████████ 100%  Advanced Lists
Week 4  ████████████████████ 100%  Stacks & Queues
Week 5  ████████████████████ 100%  Hash Tables
Week 6  ████████████████████ 100%  Advanced Hashing
Week 7  ████████████████████ 100%  BST & Sorting
Week 8  ████████████████████ 100%  BST Operations
```

---

## 🎓 Academic Context

**Course**: Data Structures & Algorithms  
**Level**: Undergraduate (3rd Semester)  
**Focus**: Practical implementation and understanding  
**Approach**: Learn by coding from scratch

---

## 💡 Key Takeaways

> **"Understanding data structures is not about memorizing code—it's about understanding how data flows and transforms."**

### What I Learned

1. **Memory Management**: How `new` and `delete` work, preventing memory leaks
2. **Pointer Mastery**: When to use `*`, `&`, and `->` 
3. **Algorithm Efficiency**: Why O(n²) doesn't scale
4. **Problem Solving**: Breaking complex problems into smaller steps
5. **Code Organization**: Writing maintainable, readable code

### Common Pitfalls Avoided

- ❌ Forgetting to update `rear = NULL` when queue empties
- ❌ Using `EMPTY` instead of `DELETED` in hash tables
- ❌ Not handling edge cases in BST deletion
- ❌ Incorrect modulo arithmetic in circular queues

---

## 🔮 Future Enhancements

- [ ] Graph implementations (BFS, DFS)
- [ ] AVL Trees (self-balancing BST)
- [ ] Heap data structure
- [ ] Advanced sorting (Heap Sort, Radix Sort)
- [ ] Dynamic programming problems
- [ ] STL comparisons and usage

---

## 📚 Resources & References

### Books
- *Introduction to Algorithms* - CLRS
- *Data Structures and Algorithm Analysis in C++* - Mark Allen Weiss

### Online Resources
- [GeeksforGeeks DSA](https://www.geeksforgeeks.org/data-structures/)
- [VisualAlgo](https://visualgo.net/) - Algorithm visualizations
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/)

### Practice Platforms
- LeetCode
- HackerRank
- Codeforces

---

## 🤝 Contributing

This is a personal learning repository, but suggestions are welcome!

If you spot an error or have an optimization suggestion:
1. Open an issue
2. Describe the problem/improvement
3. Provide context (which file, line number)

---

## 📜 License

This repository is for educational purposes. Feel free to learn from it, but please maintain academic integrity if you're a student.

---

## 🙏 Acknowledgments

- Course instructors and TAs
- Online DSA communities
- Fellow students who helped debug tricky pointer issues
- Stack Overflow for those 3 AM compilation errors

---

## 📞 Connect

Questions? Feedback? Found a bug?

Open an issue or reach out through the repository!

---

<div align="center">

**⭐ If you found this helpful, consider starring the repo!**

```
 _____                _    _                       _             
|_   _|__  __ _ _ __ | | _| |__   ___  _ __     __| | __ _ _   _ 
  | |/ _ \/ _` | '_ \| |/ / '_ \ / _ \| '_ \   / _` |/ _` | | | |
  | |  __/ (_| | | | |   <| | | | (_) | | | | | (_| | (_| | |_| |
  |_|\___|\__,_|_| |_|_|\_\_| |_|\___/|_| |_|  \__,_|\__,_|\__, |
                                                            |___/ 
```

**Made with 💻