#include <string>
using namespace std;
const int TABLE_SIZE = 11;  
enum CellStatus {
    EMPTY,     
    OCCUPIED,  
    DELETED    
};
template <typename K, typename V>
struct HashEntry {
    K key;               
    V value;             
    CellStatus status;   
    HashEntry() : status(EMPTY) {}  
};
template <typename K, typename V>
struct HashTable {
    HashEntry<K, V>* table;  
    int size;                
    int capacity;            
};
int hashInt(int key, int tableSize) {
    return key % tableSize;
}
int hashString(const string& key, int tableSize) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i]) % tableSize;
    }
    return hash;
}
template <typename K>
int hashFunction(K key, int tableSize) {
    return hashString(key, tableSize);
}
template <typename K, typename V>
struct LinearProbingHashTable {
    HashEntry<K, V>* table;
    int capacity;
    int size;
    LinearProbingHashTable(int cap = TABLE_SIZE) {
        capacity = cap;
        size = 0;
        table = new HashEntry<K, V>[capacity];
    }
    ~LinearProbingHashTable() {
        delete[] table;
    }
};
template <typename K, typename V>
void linearInsert(LinearProbingHashTable<K, V>* ht, K key, V value) {
    }
    int i = 0;  
        int probedIndex = (index + i) % ht->capacity;
            ht->table[probedIndex].value = value;
            ht->table[probedIndex].status = OCCUPIED;
            cout << "  Inserted '" << key << "' at index " << probedIndex;
            if (i > 0) {
                cout << " (after " << i << " probes)";
            }
            cout << endl;
            return;
        }
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            ht->table[probedIndex].value = value;
            cout << "  Updated '" << key << "' at index " << probedIndex << endl;
            return;
        }
}
template <typename K, typename V>
bool linearSearch(LinearProbingHashTable<K, V>* ht, K key, V* result) {
        int probedIndex = (index + i) % ht->capacity;
            return false;
        }
            return true;
        }
        i++;
template <typename K, typename V>
    int index = hashFunction(key, ht->capacity);
    int i = 0;
    while (i < ht->capacity) {
        int probedIndex = (index + i) % ht->capacity;
        if (ht->table[probedIndex].status == EMPTY) {
            return false;  
        }
        if (ht->table[probedIndex].status == OCCUPIED && 
            cout << "  Deleted '" << key << "' from index " << probedIndex << endl;
        }
        i++;
    }
    return false;
}
template <typename K, typename V>
void displayLinear(LinearProbingHashTable<K, V>* ht) {
    cout << "\nHash Table Contents (Linear Probing):\n";
    cout << "Index | Status    | Key       | Value\n";
    cout << "------|-----------|-----------|----------\n";
        cout << "  " << i << "   | ";
        if (ht->table[i].status == EMPTY) {
            cout << "EMPTY     | -         | -\n";
        }
        else if (ht->table[i].status == DELETED) {
            cout << "DELETED   | -         | -\n";
        }
        else {
            cout << "OCCUPIED  | " << ht->table[i].key << " | " 
                 << ht->table[i].value << "\n";
        }
    }
    cout << "Size: " << ht->size << "/" << ht->capacity << endl;
}
template <typename K, typename V>
struct QuadraticProbingHashTable {
    int capacity;
    int size;
    QuadraticProbingHashTable(int cap = TABLE_SIZE) {
        capacity = cap;
        size = 0;
        table = new HashEntry<K, V>[capacity];
    }
    ~QuadraticProbingHashTable() {
        delete[] table;
    }
};
template <typename K, typename V>
void quadraticInsert(QuadraticProbingHashTable<K, V>* ht, K key, V value) {
    if (ht->size >= ht->capacity) {
        return;
    }
    while (i < ht->capacity) {
        int probedIndex = (index + i * i) % ht->capacity;
        if (ht->table[probedIndex].status == EMPTY || 
            ht->table[probedIndex].status = OCCUPIED;
            cout << "  Inserted '" << key << "' at index " << probedIndex;
            if (i > 0) {
                cout << " (after " << i << " probes, sequence: ";
                for (int j = 0; j <= i; j++) {
                    cout << (index + j * j) % ht->capacity;
                    if (j < i) cout << "→";
                }
                cout << ")";
            }
            cout << endl;
            return;
        }
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            ht->table[probedIndex].value = value;
            cout << "  Updated '" << key << "' at index " << probedIndex << endl;
            return;
        }
        i++;
    }
    cout << "Error: Could not insert" << endl;
}
template <typename K, typename V>
bool quadraticSearch(QuadraticProbingHashTable<K, V>* ht, K key, V* result) {
    int index = hashFunction(key, ht->capacity);
    int i = 0;
    while (i < ht->capacity) {
        int probedIndex = (index + i * i) % ht->capacity;
        if (ht->table[probedIndex].status == EMPTY) {
            return false;
        }
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            *result = ht->table[probedIndex].value;
            return true;
        }
        i++;
    }
    return false;
}
template <typename K, typename V>
bool quadraticDelete(QuadraticProbingHashTable<K, V>* ht, K key) {
    int i = 0;
    while (i < ht->capacity) {
        int probedIndex = (index + i * i) % ht->capacity;
        if (ht->table[probedIndex].status == EMPTY) {
            return false;
        }
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            ht->table[probedIndex].status = DELETED;
            ht->size--;
            return true;
        i++;
    return false;
}
template <typename K, typename V>
    cout << "\nHash Table Contents (Quadratic Probing):\n";
    cout << "Index | Status    | Key       | Value\n";
    cout << "------|-----------|-----------|----------\n";
    for (int i = 0; i < ht->capacity; i++) {
        cout << "  " << i << "   | ";
        if (ht->table[i].status == EMPTY) {
            cout << "EMPTY     | -         | -\n";
        }
        else if (ht->table[i].status == DELETED) {
            cout << "DELETED   | -         | -\n";
        }
            cout << "OCCUPIED  | " << ht->table[i].key << " | " 
                 << ht->table[i].value << "\n";
        }
    cout << "Size: " << ht->size << "/" << ht->capacity << endl;
}
void demonstrateLinearProbing() {
    cout << "\n====================================================\n";
    cout << "  LINEAR PROBING DEMONSTRATION\n";
    cout << "====================================================\n\n";
    LinearProbingHashTable<string, int> ht(11);
    cout << "Inserting key-value pairs:\n";
    linearInsert(&ht, string("Alice"), 25);
    linearInsert(&ht, string("Bob"), 30);
    linearInsert(&ht, string("Charlie"), 35);
    linearInsert(&ht, string("Diana"), 28);
    linearInsert(&ht, string("Eve"), 32);
    cout << "\nSearching:\n";
    int value;
    if (linearSearch(&ht, string("Charlie"), &value)) {
        cout << "  Found Charlie: " << value << endl;
    }
    if (!linearSearch(&ht, string("Frank"), &value)) {
        cout << "  Frank not found" << endl;
    cout << "\nDeleting Bob:\n";
    linearDelete(&ht, string("Bob"));
    displayLinear(&ht);
    cout << "\nInserting Frank (will use deleted spot):\n";
    linearInsert(&ht, string("Frank"), 27);
}
void demonstrateQuadraticProbing() {
    cout << "\n====================================================\n";
    cout << "  QUADRATIC PROBING DEMONSTRATION\n";
    cout << "====================================================\n\n";
    QuadraticProbingHashTable<string, int> ht(11);
    cout << "Inserting key-value pairs:\n";
    quadraticInsert(&ht, string("Alice"), 25);
    quadraticInsert(&ht, string("Bob"), 30);
    quadraticInsert(&ht, string("Charlie"), 35);
    quadraticInsert(&ht, string("Diana"), 28);
    displayQuadratic(&ht);
    cout << "\nSearching:\n";
    int value;
    if (quadraticSearch(&ht, string("Diana"), &value)) {
    }
    cout << "\nDeleting Charlie:\n";
    quadraticDelete(&ht, string("Charlie"));
    displayQuadratic(&ht);
    cout << "\nInserting George:\n";
    quadraticInsert(&ht, string("George"), 29);
}
void compareProbing() {
    cout << "\n====================================================\n";
    cout << "====================================================\n\n";
    cout << "Same keys inserted in both tables:\n\n";
    QuadraticProbingHashTable<string, int> quadratic(11);
    string keys[] = {"Alice", "Bob", "Charlie", "Diana", "Eve", "Frank"};
    int values[] = {25, 30, 35, 28, 32, 27};
    for (int i = 0; i < 6; i++) {
        linearInsert(&linear, keys[i], values[i]);
        quadraticInsert(&quadratic, keys[i], values[i]);
    }
    displayLinear(&linear);
    displayQuadratic(&quadratic);
    cout << "\nNotice the different distributions!\n";
    cout << "Linear: More clustering (consecutive occupied cells)\n";
    cout << "Quadratic: Better distribution (less clustering)\n";
int main() {
    cout << "========================================================\n";
    cout << "  TASK 4: HASH TABLE WITH LINEAR & QUADRATIC PROBING\n";
    cout << "========================================================\n";
    demonstrateLinearProbing();
    compareProbing();
    cout << "\n========================================================\n";
    cout << "  All demonstrations completed!\n";
    cout << "========================================================\n\n";
    return 0;
}
