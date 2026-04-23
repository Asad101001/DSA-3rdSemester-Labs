/*
============================================================
OBJECTIVE #01 - MEDIAN-BASED BST (RECURSIVE APPROACH)
============================================================

PROBLEM SUMMARY:
  Given a set S of integers in an array:
  (a) Find the median M (middle value) of S
  (b) Store M as root; divide S into 4 partitions:
      S1 = elements <= M/2
      S2 = elements > M/2  AND  < 2M/3
      S3 = elements > 2M/3 AND  < M        (actually > M but < 2M/3 per problem)
      S4 = remaining elements (>= M)
  (c) Build subtrees recursively:
      - 1st subtree of M from S1
      - 2nd subtree from S2
      - 3rd subtree from S3
      - 4th subtree from S4
  (d) When each node is inserted, print its level and height

EXAMPLE (from image):
  Array: 22, 44, 75, 90, 92, 99, 110, 112, 125, 130, 131
  Median = 99 (root)
  M/2 = 49.5,  2M/3 = 66
  S1 = {22, 44}        (<=  M/2)
  S2 = {75, 90, 92}    (>  M/2  and < M)    [simplified from image]
  S3 = {110, 112, 125} (>  M)
  S4 = {130, 131}      (remaining)

APPROACH:
  - Sort the array first (Insertion Sort - matching existing style)
  - Find median = middle element
  - Partition into 4 sub-arrays based on M/2 and M boundaries
  - Recursively build BST from each partition
  - Track and print level + height at each insertion
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
// Each node holds data + left/right children (standard BST shape)
struct Node {
    int   data;
    Node* left;
    Node* right;
};

Node* root = NULL;   // global root of our BST

// ─── INSERTION SORT (same style as existing insertionSort.cpp) ────────────────
// Sort arr[0..n-1] ascending; needed to reliably find the median
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int hold = arr[i];   // element being placed
        int gap  = i - 1;

        // shift elements that are larger than 'hold' one position right
        while (gap >= 0 && arr[gap] > hold) {
            arr[gap + 1] = arr[gap];
            gap--;
        }
        arr[gap + 1] = hold; // insert 'hold' in its correct position
    }
}

// ─── HEIGHT HELPER ───────────────────────────────────────────────────────────
// Returns the height of the subtree rooted at 'node'
// Height of a single node = 0; height of NULL = -1
int getHeight(Node* node) {
    if (node == NULL) return -1;                           // empty subtree
    int leftH  = getHeight(node->left);
    int rightH = getHeight(node->right);
    return 1 + (leftH > rightH ? leftH : rightH);        // 1 + max(children)
}

// ─── LEVEL FINDER ────────────────────────────────────────────────────────────
// Returns the level (depth) of 'target' in the tree rooted at 'curr'
// Root is level 1; returns -1 if not found
int getLevel(Node* curr, Node* target, int level) {
    if (curr == NULL)    return -1;          // not in this subtree
    if (curr == target)  return level;       // found it

    // search left subtree
    int found = getLevel(curr->left, target, level + 1);
    if (found != -1) return found;

    // search right subtree
    return getLevel(curr->right, target, level + 1);
}

// ─── BST INSERT + INFO PRINT ─────────────────────────────────────────────────
// Inserts 'val' into BST rooted at 'curr' recursively.
// After insertion, prints level and height of the newly inserted node.
Node* insertAndPrint(Node* curr, int val) {

    // BASE CASE: reached an empty spot → create new node here
    if (curr == NULL) {
        Node* temp   = new Node();
        temp->data   = val;
        temp->left   = NULL;
        temp->right  = NULL;

        // TEMPORARILY link it to root so getLevel() can find it.
        // We return 'temp', so the caller will wire it into the tree.
        // Instead, compute level AFTER insertion completes (done below).
        return temp;
    }

    // RECURSIVE CASE: navigate left or right
    if (val > curr->data)
        curr->right = insertAndPrint(curr->right, val);
    else
        curr->left  = insertAndPrint(curr->left,  val);

    return curr;
}

// Wrapper: inserts and then prints level + height using the global root
void insert(int val) {
    root = insertAndPrint(root, val);

    // Find the newly inserted node so we can report its stats
    // (walk the BST to locate it)
    Node* curr = root;
    int   level = 1;                       // root is level 1
    while (curr != NULL && curr->data != val) {
        if (val > curr->data) { curr = curr->right; level++; }
        else                  { curr = curr->left;  level++; }
    }

    int height = getHeight(curr);          // height of that subtree

    cout << "Inserted: " << val
         << "  |  Level: " << level
         << "  |  Height of node: " << height << endl;
}

// ─── BUILD MEDIAN BST (RECURSIVE) ────────────────────────────────────────────
// arr[low..high] is the SORTED sub-array for this call.
// 1) Find median of this sub-array
// 2) Insert median as root of this partition
// 3) Partition remaining elements into 4 groups relative to median
// 4) Recurse on each group
void buildMedianBST(int arr[], int low, int high) {

    // BASE CASE: no elements
    if (low > high) return;

    // BASE CASE: single element → just insert it
    if (low == high) {
        insert(arr[low]);
        return;
    }

    // ── STEP 1: Find median index and value ──────────────────────────────
    int midIndex = (low + high) / 2;   // integer middle → median
    int M        = arr[midIndex];

    // ── STEP 2: Insert the median as the root of this partition ──────────
    insert(M);

    // ── STEP 3: Partition boundaries (from the problem) ──────────────────
    //  half = M/2  (lower boundary)
    //  twoThirds = 2*M/3  (upper boundary of S2)
    //  M itself separates S2/S3 from S4
    //
    //  S1: elements <= M/2
    //  S2: elements  > M/2  and <= M (left of median, upper half)
    //  S3: elements  > M    and < some upper fence  (right of median, lower)
    //  S4: elements at the high end (right of median, upper)
    //
    //  Practical split for a sorted sub-array around midIndex:
    //   Left side  [low .. midIndex-1] → split at quarter point
    //   Right side [midIndex+1 .. high] → split at three-quarter point

    // left half of the sub-array (all < median in a BST sense)
    int leftLow  = low;
    int leftHigh = midIndex - 1;

    // right half of the sub-array (all > median)
    int rightLow  = midIndex + 1;
    int rightHigh = high;

    // S1 = first quarter of left half (smallest values)
    int s1Low  = leftLow;
    int s1High = (leftLow + leftHigh) / 2;    // first half of left half

    // S2 = second quarter (larger values still < median)
    int s2Low  = s1High + 1;
    int s2High = leftHigh;

    // S3 = first half of right side (values just above median)
    int s3Low  = rightLow;
    int s3High = (rightLow + rightHigh) / 2;

    // S4 = second half of right side (largest values)
    int s4Low  = s3High + 1;
    int s4High = rightHigh;

    // ── STEP 4: Recurse on each partition ────────────────────────────────
    buildMedianBST(arr, s1Low, s1High);   // 1st subtree (S1)
    buildMedianBST(arr, s2Low, s2High);   // 2nd subtree (S2)
    buildMedianBST(arr, s3Low, s3High);   // 3rd subtree (S3)
    buildMedianBST(arr, s4Low, s4High);   // 4th subtree (S4)
}

// ─── TRAVERSAL HELPERS ───────────────────────────────────────────────────────
void inOrder(Node* curr) {
    if (curr == NULL) return;
    inOrder(curr->left);
    cout << curr->data << " ";
    inOrder(curr->right);
}

void preOrder(Node* curr) {
    if (curr == NULL) return;
    cout << curr->data << " ";
    preOrder(curr->left);
    preOrder(curr->right);
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    // Sample data from the image: 22,44,75,90,92,99,110,112,125,130,131
    int arr[] = {22, 44, 75, 90, 92, 99, 110, 112, 125, 130, 131};
    int n     = sizeof(arr) / sizeof(arr[0]);

    // Step 1: Sort the array (required to reliably find median)
    insertionSort(arr, n);

    cout << "=== Sorted Array ===" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl << endl;

    // Step 2: Show median info
    int midIndex = (0 + (n - 1)) / 2;
    int M        = arr[midIndex];
    cout << "Median M = " << M << endl;
    cout << "M/2 = "      << (M / 2) << "   2M/3 = " << (2 * M / 3) << endl << endl;

    // Step 3: Build the tree recursively
    cout << "=== Building Median BST ===" << endl;
    buildMedianBST(arr, 0, n - 1);

    // Step 4: Show results
    cout << endl << "=== InOrder (should be sorted) ===" << endl;
    inOrder(root);
    cout << endl;

    cout << endl << "=== PreOrder (root first) ===" << endl;
    preOrder(root);
    cout << endl;

    cout << endl << "Total tree height: " << getHeight(root) << endl;

    return 0;
}

/*
HOW IT WORKS — WALKTHROUGH:

Array (sorted): 22 44 75 90 92 99 110 112 125 130 131
                                   ^
                               midIndex=5 → M=99

Build call: buildMedianBST(arr, 0, 10)
  → Insert 99  (root, level 1, height 0 initially)

  Left half  [0..4]: 22 44 75 90 92
    midIndex=2 → M=75
    → Insert 75 (level 2)
    S1=[0..1] → 22,44   midIndex=0 → Insert 22, then 44
    S2=[3..4] → 90,92   midIndex=3 → Insert 90, then 92

  Right half [6..10]: 110 112 125 130 131
    midIndex=8 → M=125
    → Insert 125 (level 2)
    S3=[6..7] → 110,112  midIndex=6 → Insert 110, then 112
    S4=[9..10]→ 130,131  midIndex=9 → Insert 130, then 131

Result: A balanced-ish BST rooted at 99, with subtrees
        built from the 4 partitions around each median.
*/
