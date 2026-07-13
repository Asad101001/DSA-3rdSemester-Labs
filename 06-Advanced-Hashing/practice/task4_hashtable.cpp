#include <iostream>
#include <cstring>
using namespace std;
struct Entry {
    char key[50];
    int value;
    int status;  
};
Entry table[11];  
int Size = 11;
int hashFunc(const char* key) {
    int h = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        h = (h * 31 + key[i]) % Size;
    }
    return h;
}
void insertLinear(const char* key, int val) {
    int index = hashFunc(key);
    int i = 0;
    while (i < Size) {
        int pos = (index + i) % Size;  
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
void searchLinear(const char* key) {
    int index = hashFunc(key);
    int i = 0;
    while (i < Size) {
        int pos = (index + i) % Size;
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
void insertQuadratic(const char* key, int val) {
    int index = hashFunc(key);
    int i = 0;
    while (i < Size) {
        int pos = (index + i*i) % Size;  
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
    for (int i = 0; i < Size; i++) {
        table[i].status = 0;  
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
