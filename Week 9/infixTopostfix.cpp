#include <iostream>
using namespace std;

struct Node{
    char data;
    Node *next;
};

Node *top = NULL;

void push(char z)
{
    Node *temp = new Node();
    temp->data = z;
    temp->next = top;
    top = temp;
}

char peek()
{
    if(top == NULL)
        return '\0';

    return top->data;
}

char pop()
{
    if (top == NULL){
        cout << "Stack underflow" << endl;
        return '\0';
    }

    Node* temp = top;
    char z = temp->data;
    top = top->next;
    delete temp;
    return z;
}

int precedence(char op)
{
    switch(op)
    {
        case '*':
        case '/':
            return 6;

        case '+':
        case '-':
            return 5;

        case '=':
        case '!':
            return 4;

        case '<':
        case '>':
            return 3;

        case '&':
            return 2;

        case '|':
            return 1;

        default:
            return 0;
    }
}

int IsOperand(char x)
{
    if((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z') || (x >= '0' && x <= '9'))
        return 1;

    return 0;
}

void InfixToPostfix(char str[])
{
    int i = 0;
    char x;

    while(str[i] != '\0')
    {
        x = str[i];

        if(IsOperand(x))
        {
            cout << x;
        }
        else
        {
            while(top != NULL && precedence(peek()) >= precedence(x))
            {
                cout << pop();
            }

            push(x);
        }

        i++;
    }

    while(top != NULL)
    {
        cout << pop();
    }
}

int main()
{
    char xyz[100];

    cout << "Enter expression for conversion: ";
    cin >> xyz;

    InfixToPostfix(xyz);

    return 0;
}