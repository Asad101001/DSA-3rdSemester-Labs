#include <iostream>
using namespace std;
const int SIZE = 10;
int HT[SIZE];
void insert(int value){
    int index = value % SIZE;
    for (int i = 0; i < SIZE;i++){
        int pos = (index + i*i) % SIZE;
        if (HT[pos] == -1 || HT[pos] == -2){
            HT[pos] = value;
            cout << "Quadratically inserted " << value << " @ index " << pos << endl;
            return;
        }
    }
    cout << " " << endl;
}
void search (int value){
    int index = value % SIZE;
    for (int i = 0; i < SIZE;i++){
        int pos = (index + i*i) % SIZE;
        if(HT[pos]==-1)
            break;
        if (HT[pos]==value){
            cout << "Found " << value << " @ index " << pos << endl;
            return;
        }    
    }
    cout << value << " not found" << endl;
}
void display(){
    for (int i = 0; i < SIZE;i++){
        cout << i << ":";
        if(HT[i]==-1)
            cout << "Empty";
        else if(HT[i]==-2)
            cout << "Deleted";
        else
            cout << HT[i];
        cout << endl;
    }
}
int main() {
    for (int i = 0; i < SIZE; i++) HT[i] = -1;
    insert(5); insert(15); insert(25);
    display();
    search(15);
    return 0;
}
