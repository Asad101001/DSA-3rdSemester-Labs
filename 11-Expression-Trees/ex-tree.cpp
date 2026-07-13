#include <iostream>
using namespace std;

struct Stack {
    char data;
    Stack* next;
};

struct ETNode {
    char data;
    ETNode* left;
    ETNode* right;
};

struct Node {
    ETNode* data;
    Node* next;
};

Stack* stack = NULL;
Node* tree = NULL;

/* ---------- STACK (CHAR) ---------- */
void pushChar(char c) {
    Stack* temp = new Stack;
    temp->data = c;
    temp->next = stack;
    stack = temp;
}

char popChar() {
    if (stack == NULL) return '\0';
    Stack* temp = stack;
    char c = temp->data;
    stack = stack->next;
    delete temp;
    return c;
}

char peekChar() {
    if (stack == NULL) return '\0';
    return stack->data;
}

int isEmptyChar() {
    return stack == NULL;
}

/* ---------- STACK (ETNode) ---------- */
void pushNode(ETNode* n) {
    Node* temp = new Node;
    temp->data = n;
    temp->next = tree;
    tree = temp;
}

ETNode* popNode() {
    if (tree == NULL) return NULL;
    Node* temp = tree;
    ETNode* n = temp->data;
    tree = tree->next;
    delete temp;
    return n;
}

/* ---------- HELPERS ---------- */
ETNode* createNode(char c) {
    ETNode* n = new ETNode;
    n->data = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int isOperator(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}

int precedence(char c) {
    if (c=='+' || c=='-') return 1;
    if (c=='*' || c=='/') return 2;
    if (c=='^') return 3;
    return 0;
}

int isOperand(char c) {
    if (c >= 'a' && c <= 'z') return 1;
    if (c >= 'A' && c <= 'Z') return 1;
    if (c >= '0' && c <= '9') return 1;
    return 0;
}

/* ---------- INFIX → POSTFIX ---------- */
void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, k = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        if (isOperand(c)) {
            postfix[k++] = c;
        }
        else if (c == '(') {
            pushChar(c);
        }
        else if (c == ')') {
            while (!isEmptyChar() && peekChar() != '(')
                postfix[k++] = popChar();
            popChar();
        }
        else if (isOperator(c)) {
            while (!isEmptyChar() && precedence(peekChar()) >= precedence(c))
                postfix[k++] = popChar();
            pushChar(c);
        }
        i++;
    }

    while (!isEmptyChar())
        postfix[k++] = popChar();

    postfix[k] = '\0';
}

/* ---------- POSTFIX → TREE ---------- */
ETNode* buildTree(char postfix[]) {
    int i = 0;

    while (postfix[i] != '\0') {
        char c = postfix[i];

        if (isOperand(c)) {
            pushNode(createNode(c));
        }
        else if (isOperator(c)) {
            ETNode* right = popNode();
            ETNode* left  = popNode();

            ETNode* root = createNode(c);
            root->left = left;
            root->right = right;

            pushNode(root);
        }
        i++;
    }

    return popNode();
}

/* ---------- TRAVERSAL ---------- */
void inorder(ETNode* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data;
    inorder(root->right);
}

/* ---------- MAIN ---------- */
int main() {
    char infix[100], postfix[100];
    ETNode* root;

    cout << "Enter infix expression: ";
    cin >> infix;

    infixToPostfix(infix, postfix);
    cout << "Postfix: " << postfix << endl;

    root = buildTree(postfix);

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    return 0;
}