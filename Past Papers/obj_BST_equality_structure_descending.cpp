/*
============================================================
OBJECTIVE - TWO BSTs: EQUALITY, STRUCTURE, DESCENDING SORT
============================================================

PROBLEM SUMMARY (from New Text Document.txt):
  Construct TWO binary search trees and check if they are:
  1. EQUAL       → same structure AND same values at every node
  2. SAME STRUCTURE → same shape (same positions of nodes)
                     but values may differ
  3. SORT NODES IN DESCENDING ORDER
     (InOrder of a BST gives ascending; reverse InOrder gives descending)

APPROACH:
  - Use recursive BST insertion (same as existing BST.cpp)
  - Equal: recursively compare data AND structure simultaneously
  - Same structure: recursively compare only left/right presence, not data
  - Descending sort: reverse InOrder traversal (right → root → left)
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
struct Node {
    int   data;
    Node* left;
    Node* right;
};

// ─── BST INSERT (recursive — same as existing BST.cpp) ───────────────────────
Node* insert(Node* curr, int val) {
    if (curr == NULL) {
        Node* temp  = new Node();
        temp->data  = val;
        temp->left  = NULL;
        temp->right = NULL;
        return temp;
    }
    if (val > curr->data) curr->right = insert(curr->right, val);
    else                  curr->left  = insert(curr->left,  val);
    return curr;
}

// ─── TRAVERSALS (from existing BST.cpp) ─────────────────────────────────────
void inOrder(Node* curr) {
    if (!curr) return;
    inOrder(curr->left);
    cout << curr->data << " ";
    inOrder(curr->right);
}

void preOrder(Node* curr) {
    if (!curr) return;
    cout << curr->data << " ";
    preOrder(curr->left);
    preOrder(curr->right);
}

// ─── OPERATION 3: DESCENDING SORT (Reverse InOrder) ─────────────────────────
// InOrder = Left → Root → Right  → ascending
// Reverse = Right → Root → Left  → descending
// For a BST, this gives all values from largest to smallest
void descendingOrder(Node* curr) {
    if (!curr) return;
    descendingOrder(curr->right);  // visit RIGHT subtree first
    cout << curr->data << " ";     // then print root
    descendingOrder(curr->left);   // then visit LEFT subtree
}

// ─── OPERATION 1: ARE TWO TREES EQUAL? ───────────────────────────────────────
// Two trees are equal if:
//   a) Both are NULL → equal (base case, empty subtrees match)
//   b) One is NULL and other isn't → NOT equal
//   c) Both non-NULL:
//      - current nodes have same data
//      - AND left subtrees are equal
//      - AND right subtrees are equal
bool areEqual(Node* t1, Node* t2) {
    // Both empty → equal
    if (t1 == NULL && t2 == NULL) return true;

    // One empty, other not → not equal
    if (t1 == NULL || t2 == NULL) return false;

    // Both non-empty: check data AND recurse on children
    return (t1->data == t2->data)          // same value here?
        && areEqual(t1->left,  t2->left)   // same left subtree?
        && areEqual(t1->right, t2->right); // same right subtree?
}

// ─── OPERATION 2: DO THEY HAVE THE SAME STRUCTURE? ───────────────────────────
// Same structure means: at every corresponding position,
// both trees have a node (or both don't) — regardless of value.
// Also called "isomorphic structure" (without value check).
bool sameStructure(Node* t1, Node* t2) {
    // Both empty → same (neither has a node here)
    if (t1 == NULL && t2 == NULL) return true;

    // One empty, other not → different structure
    if (t1 == NULL || t2 == NULL) return false;

    // Both non-empty → compare children (ignore values)
    return sameStructure(t1->left,  t2->left)
        && sameStructure(t1->right, t2->right);
}

// ─── HEIGHT AND COUNT HELPERS ─────────────────────────────────────────────────
int getHeight(Node* n) {
    if (!n) return -1;
    int l = getHeight(n->left), r = getHeight(n->right);
    return 1 + (l > r ? l : r);
}

int countNodes(Node* n) {
    if (!n) return 0;
    return 1 + countNodes(n->left) + countNodes(n->right);
}

// ─── PRINT TREE INFO ─────────────────────────────────────────────────────────
void printTreeInfo(const char* name, Node* root) {
    cout << name << ":" << endl;
    cout << "  InOrder (ascending):   ";
    inOrder(root);
    cout << endl;
    cout << "  PreOrder:              ";
    preOrder(root);
    cout << endl;
    cout << "  Descending order:      ";
    descendingOrder(root);
    cout << endl;
    cout << "  Height: " << getHeight(root)
         << "  |  Nodes: " << countNodes(root) << endl;
}

// ─── COMPARE TWO TREES ────────────────────────────────────────────────────────
void compareTrees(Node* t1, Node* t2, const char* name1, const char* name2) {
    cout << endl << "=== Comparing " << name1 << " and " << name2 << " ===" << endl;

    // Equality
    if (areEqual(t1, t2)) {
        cout << "EQUAL: YES — both trees have identical structure AND values." << endl;
    } else {
        cout << "EQUAL: NO — the trees differ." << endl;

        // More detail
        if (sameStructure(t1, t2)) {
            cout << "SAME STRUCTURE: YES — same shape, but different values." << endl;
        } else {
            cout << "SAME STRUCTURE: NO — different shapes." << endl;
        }
    }
}

// ─── FREE TREE ────────────────────────────────────────────────────────────────
void freeTree(Node* curr) {
    if (!curr) return;
    freeTree(curr->left);
    freeTree(curr->right);
    delete curr;
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== Two BSTs: Equality, Structure, Descending Sort ===" << endl << endl;

    // ── Test Case 1: Identical trees ─────────────────────────────────────
    cout << "──────────────────────────────────────────" << endl;
    cout << "Test 1: Identical Trees" << endl;
    cout << "──────────────────────────────────────────" << endl;

    Node* tree1A = NULL;
    Node* tree1B = NULL;

    int vals1[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        tree1A = insert(tree1A, vals1[i]);
        tree1B = insert(tree1B, vals1[i]);   // same values → identical
    }

    printTreeInfo("Tree A", tree1A);
    printTreeInfo("Tree B", tree1B);
    compareTrees(tree1A, tree1B, "Tree A", "Tree B");

    // ── Test Case 2: Same structure, different values ─────────────────────
    cout << endl << "──────────────────────────────────────────" << endl;
    cout << "Test 2: Same Structure, Different Values" << endl;
    cout << "──────────────────────────────────────────" << endl;

    Node* tree2A = NULL;
    Node* tree2B = NULL;

    // Tree 2A: insert 50, 30, 70 (root + left + right)
    tree2A = insert(tree2A, 50);
    tree2A = insert(tree2A, 30);
    tree2A = insert(tree2A, 70);

    // Tree 2B: insert 100, 60, 140 → same shape (root + left + right)
    tree2B = insert(tree2B, 100);
    tree2B = insert(tree2B, 60);
    tree2B = insert(tree2B, 140);

    printTreeInfo("Tree 2A (50,30,70)", tree2A);
    printTreeInfo("Tree 2B (100,60,140)", tree2B);
    compareTrees(tree2A, tree2B, "Tree 2A", "Tree 2B");

    // ── Test Case 3: Different structure ──────────────────────────────────
    cout << endl << "──────────────────────────────────────────" << endl;
    cout << "Test 3: Different Structure" << endl;
    cout << "──────────────────────────────────────────" << endl;

    Node* tree3A = NULL;
    Node* tree3B = NULL;

    // Tree 3A: balanced shape
    tree3A = insert(tree3A, 50);
    tree3A = insert(tree3A, 30);
    tree3A = insert(tree3A, 70);

    // Tree 3B: right-skewed (inserted in ascending order)
    tree3B = insert(tree3B, 10);
    tree3B = insert(tree3B, 20);
    tree3B = insert(tree3B, 30);

    printTreeInfo("Tree 3A (balanced)", tree3A);
    printTreeInfo("Tree 3B (right-skewed)", tree3B);
    compareTrees(tree3A, tree3B, "Tree 3A", "Tree 3B");

    // ── Test Case 4: Descending sort focus ────────────────────────────────
    cout << endl << "──────────────────────────────────────────" << endl;
    cout << "Test 4: Descending Sort Demonstration" << endl;
    cout << "──────────────────────────────────────────" << endl;

    Node* tree4 = NULL;
    int vals4[] = {55, 25, 75, 15, 35, 65, 85, 10, 20, 30, 50};
    for (int i = 0; i < 11; i++) tree4 = insert(tree4, vals4[i]);

    cout << "BST with values: 55,25,75,15,35,65,85,10,20,30,50" << endl;
    cout << "  InOrder (ascending):   "; inOrder(tree4);    cout << endl;
    cout << "  Descending order:      "; descendingOrder(tree4); cout << endl;

    // ── Interactive Menu ──────────────────────────────────────────────────
    cout << endl << "=== Interactive Mode ===" << endl;

    Node* userTree1 = NULL;
    Node* userTree2 = NULL;

    int choice, val;
    do {
        cout << "\n1. Insert into Tree 1\n2. Insert into Tree 2\n";
        cout << "3. Print Tree 1\n4. Print Tree 2\n5. Compare Trees\n";
        cout << "6. Descending sort Tree 1\n7. Descending sort Tree 2\n8. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Value: "; cin >> val;
                userTree1 = insert(userTree1, val);
                break;
            case 2:
                cout << "Value: "; cin >> val;
                userTree2 = insert(userTree2, val);
                break;
            case 3:
                printTreeInfo("Tree 1", userTree1);
                break;
            case 4:
                printTreeInfo("Tree 2", userTree2);
                break;
            case 5:
                compareTrees(userTree1, userTree2, "Tree 1", "Tree 2");
                break;
            case 6:
                cout << "Tree 1 descending: ";
                descendingOrder(userTree1); cout << endl;
                break;
            case 7:
                cout << "Tree 2 descending: ";
                descendingOrder(userTree2); cout << endl;
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid" << endl;
        }
    } while (choice != 8);

    // Cleanup
    freeTree(tree1A); freeTree(tree1B);
    freeTree(tree2A); freeTree(tree2B);
    freeTree(tree3A); freeTree(tree3B);
    freeTree(tree4);
    freeTree(userTree1); freeTree(userTree2);

    return 0;
}

/*
DESCENDING ORDER — REVERSE INORDER EXPLAINED:

BST:       50
          /  \
        30    70
       /  \  /  \
      20  40 60  80

Regular InOrder (L→Root→R):   20 30 40 50 60 70 80  (ascending)

Reverse InOrder (R→Root→L):
  descendingOrder(50):
    descendingOrder(70):
      descendingOrder(80): print 80
      print 70
      descendingOrder(60): print 60
    print 50
    descendingOrder(30):
      descendingOrder(40): print 40
      print 30
      descendingOrder(20): print 20

Output: 80 70 60 50 40 30 20  (descending) ✓

EQUALITY CHECK WALKTHROUGH:
  Two trees with same values inserted in same order:
  areEqual(50, 50):
    data match: 50==50 ✓
    areEqual(30, 30): ✓ (recurse left)
    areEqual(70, 70): ✓ (recurse right)
  → EQUAL = true

STRUCTURE CHECK WALKTHROUGH:
  Tree A: root has left and right child
  Tree B: root has left and right child
  sameStructure(A.root, B.root):
    both non-NULL ✓
    sameStructure(A.left, B.left):   both non-NULL ✓
    sameStructure(A.right, B.right): both non-NULL ✓
  → SAME STRUCTURE = true (even if values differ)
*/
