#include <iostream>
using namespace std;

struct Stack {
    int data;
    Stack* next;
};

Stack* top = NULL;

void push(int x) {
    Stack* t = new Stack;
    t->data = x;
    t->next = top;
    top = t;
}

int pop() {
    if (top == NULL) return 0;
    Stack* t = top;
    int x = t->data;
    top = top->next;
    delete t;
    return x;
}

int isOp(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/';
}

int eval(int a, int b, char op) {
    if (op=='+') return a+b;
    if (op=='-') return a-b;
    if (op=='*') return a*b;
    if (op=='/') return a/b;
    return 0;
}

int main() {
    char post[100];

    cout << "Enter postfix: ";
    cin >> post;

    int i = 0;

    while (post[i] != '\0') {
        char c = post[i];

        if (c >= '0' && c <= '9') {
            push(c - '0');
        }
        else if (isOp(c)) {
            int b = pop();
            int a = pop();
            push(eval(a, b, c));
        }
        i++;
    }

    cout << "Result: " << pop();

    return 0;
}