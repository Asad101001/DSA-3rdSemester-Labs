#include <iostream> 
using namespace std;

int main() {

    cout << "Hello, World!" << endl;
    
    int age = 21;             
    double gpa = 3.75;        
    char grade = 'A';        
    bool isPassing = true;     
    string name = "Ahmad";    
    
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "GPA: " << gpa << endl;
    cout << "Grade: " << grade << endl;
    cout << "Passing: " << isPassing << endl;
    
    int userNumber;
    cout << "\nEnter a number: ";
    cin >> userNumber;  
    cout << "You entered: " << userNumber << endl;
    
    return 0; 
}
