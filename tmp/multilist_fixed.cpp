#include<iostream>
#include<stdlib.h>
using namespace std;

// Student Node - stores student number and pointer to next student
struct SNode {
    int SNo;           // Student seat number
    SNode* Snext;      // Pointer to next student in same course
};

// Course Node - stores course number and pointers
struct CNode {
    int CNo;           // Course number
    CNode* Cnext;      // Pointer to next course
    SNode* stu_list;   // Pointer to list of students in this course
};

CNode* Clist = NULL;   // Global pointer to course list

// Insert a new course at the end of course list
void insert_course(int value) {
    CNode* temp = (CNode*)malloc(sizeof(CNode));
    temp->CNo = value;
    temp->Cnext = NULL;
    temp->stu_list = NULL;
    
    if (Clist == NULL) {
        Clist = temp;
    } else {
        CNode* Ccurr = Clist;
        while (Ccurr->Cnext != NULL) {
            Ccurr = Ccurr->Cnext;
        }
        Ccurr->Cnext = temp;
    }
}

// Search for a course
void search_course(int value) {
    CNode* Ccurr = Clist;
    while (Ccurr != NULL) {
        if (Ccurr->CNo == value) {
            cout << "Course found: " << value << endl;
            return;
        }
        Ccurr = Ccurr->Cnext;
    }
    cout << "Course not found: " << value << endl;
}

// Search for a student in a specific course
void search_stu_in_course(int course, int seat) {
    CNode* Ccurr = Clist;
    
    if (Ccurr == NULL) {
        cout << "Course list is empty" << endl;
        return;
    }
    
    // Find the course
    while (Ccurr != NULL) {
        if (course == Ccurr->CNo) {
            SNode* Scurr = Ccurr->stu_list;
            
            if (Scurr == NULL) {
                cout << "No students in course " << course << endl;
                return;
            }
            
            // Search in student list
            while (Scurr != NULL) {
                if (Scurr->SNo == seat) {
                    cout << "Student " << seat << " found in course " << course << endl;
                    return;
                }
                Scurr = Scurr->Snext;
            }
            
            cout << "Student " << seat << " not found in course " << course << endl;
            return;
        }
        Ccurr = Ccurr->Cnext;
    }
    cout << "Course " << course << " not found" << endl;
}

// FIXED: Search for a student across all courses
void search_student(int seat) {
    CNode* Ccurr = Clist;
    int count = 0;
    
    if (Ccurr == NULL) {
        cout << "Course list is empty" << endl;
        return;
    }
    
    // Traverse each course
    while (Ccurr != NULL) {
        SNode* Scurr = Ccurr->stu_list;
        
        // Search in this course's student list
        while (Scurr != NULL) {
            if (Scurr->SNo == seat) {
                count++;
            }
            Scurr = Scurr->Snext;
        }
        Ccurr = Ccurr->Cnext;
    }
    
    if (count == 0) {
        cout << "Student " << seat << " not found in any course" << endl;
    } else {
        cout << "Student " << seat << " found in " << count << " course(s)" << endl;
    }
}

// Display all courses
void display_course() {
    CNode* Ccurr = Clist;
    if (Clist != NULL) {
        cout << "Courses: ";
        while (Ccurr != NULL) {
            cout << Ccurr->CNo << " ";
            Ccurr = Ccurr->Cnext;
        }
        cout << endl;
    } else {
        cout << "No courses" << endl;
    }
}

// Insert student into a course
void insert_stu(int course, int seat) {
    CNode* Ccurr = Clist;
    
    while (Ccurr != NULL) {
        if (course == Ccurr->CNo) {
            SNode* temp = (SNode*)malloc(sizeof(SNode));
            temp->SNo = seat;
            temp->Snext = NULL;
            
            if (Ccurr->stu_list == NULL) {
                Ccurr->stu_list = temp;
            } else {
                SNode* Scurr = Ccurr->stu_list;
                while (Scurr->Snext != NULL) {
                    Scurr = Scurr->Snext;
                }
                Scurr->Snext = temp;
            }
            cout << "Student " << seat << " added to course " << course << endl;
            return;
        }
        Ccurr = Ccurr->Cnext;
    }
    cout << "Course " << course << " not found" << endl;
}

// Delete student from specific course
void Delete_student_from_a_course(int course, int seat) {
    CNode* Ccurr = Clist;
    
    if (Ccurr == NULL) {
        cout << "Course list is empty" << endl;
        return;
    }
    
    while (Ccurr != NULL) {
        if (course == Ccurr->CNo) {
            SNode* Scurr = Ccurr->stu_list;
            SNode* prev = NULL;
            
            if (Scurr == NULL) {
                cout << "No students in course" << endl;
                return;
            }
            
            // If student is first in list
            if (seat == Scurr->SNo) {
                Ccurr->stu_list = Scurr->Snext;
                free(Scurr);
                cout << "Student " << seat << " deleted from course " << course << endl;
                return;
            }
            
            // Search in rest of list
            prev = Scurr;
            Scurr = Scurr->Snext;
            
            while (Scurr != NULL) {
                if (Scurr->SNo == seat) {
                    prev->Snext = Scurr->Snext;
                    free(Scurr);
                    cout << "Student " << seat << " deleted from course " << course << endl;
                    return;
                }
                prev = Scurr;
                Scurr = Scurr->Snext;
            }
            cout << "Student " << seat << " not found in course " << course << endl;
            return;
        }
        Ccurr = Ccurr->Cnext;
    }
    cout << "Course " << course << " not found" << endl;
}

// Delete student from ALL courses
void Delete_student(int seat) {
    CNode* Ccurr = Clist;
    int count = 0;
    
    if (Ccurr == NULL) {
        cout << "Course list is empty" << endl;
        return;
    }
    
    while (Ccurr != NULL) {
        SNode* Scurr = Ccurr->stu_list;
        SNode* prev = NULL;
        
        while (Scurr != NULL) {
            if (Scurr->SNo == seat) {
                SNode* temp = Scurr;
                
                if (prev == NULL) {
                    // Student is first in list
                    Ccurr->stu_list = Scurr->Snext;
                    Scurr = Ccurr->stu_list;
                } else {
                    // Student is in middle or end
                    prev->Snext = Scurr->Snext;
                    Scurr = prev->Snext;
                }
                
                free(temp);
                count++;
                cout << "Student " << seat << " deleted from course " << Ccurr->CNo << endl;
                continue;
            }
            
            prev = Scurr;
            Scurr = Scurr->Snext;
        }
        Ccurr = Ccurr->Cnext;
    }
    
    if (count == 0) {
        cout << "Student " << seat << " not found in any course" << endl;
    } else {
        cout << "Total: Student " << seat << " deleted from " << count << " course(s)" << endl;
    }
}

// Delete entire course with all its students
void Delete_course(int value) {
    CNode* Ccurr = Clist;
    CNode* prev = NULL;
    
    if (Ccurr == NULL) {
        cout << "Course list is empty" << endl;
        return;
    }
    
    // If course is first in list
    if (value == Ccurr->CNo) {
        Clist = Ccurr->Cnext;
        
        // Delete all students in this course
        SNode* Scurr = Ccurr->stu_list;
        while (Scurr != NULL) {
            SNode* temp = Scurr;
            Scurr = Scurr->Snext;
            free(temp);
        }
        
        free(Ccurr);
        cout << "Course " << value << " deleted" << endl;
        return;
    }
    
    // Search in rest of list
    prev = Ccurr;
    Ccurr = Ccurr->Cnext;
    
    while (Ccurr != NULL) {
        if (value == Ccurr->CNo) {
            prev->Cnext = Ccurr->Cnext;
            
            // Delete all students
            SNode* Scurr = Ccurr->stu_list;
            while (Scurr != NULL) {
                SNode* temp = Scurr;
                Scurr = Scurr->Snext;
                free(temp);
            }
            
            free(Ccurr);
            cout << "Course " << value << " deleted" << endl;
            return;
        }
        prev = Ccurr;
        Ccurr = Ccurr->Cnext;
    }
    cout << "Course " << value << " not found" << endl;
}

// Display all courses with their students
void display_all() {
    CNode* Ccurr = Clist;
    
    if (Clist == NULL) {
        cout << "No courses" << endl;
        return;
    }
    
    while (Ccurr != NULL) {
        cout << "\nCourse " << Ccurr->CNo << ":" << endl;
        
        SNode* Scurr = Ccurr->stu_list;
        if (Scurr == NULL) {
            cout << "  No students enrolled" << endl;
        } else {
            cout << "  Students: ";
            while (Scurr != NULL) {
                cout << Scurr->SNo << " ";
                Scurr = Scurr->Snext;
            }
            cout << endl;
        }
        Ccurr = Ccurr->Cnext;
    }
}

int main() {
    int choice, val, val1, val2;
    string state;
    
    while (true) {
        cout << "\n=== COURSE REGISTRATION SYSTEM ===" << endl;
        cout << "1. Insert course" << endl;
        cout << "2. Insert student into course" << endl;
        cout << "3. Search course" << endl;
        cout << "4. Search student (all courses)" << endl;
        cout << "5. Search student in specific course" << endl;
        cout << "6. Delete course" << endl;
        cout << "7. Delete student from course" << endl;
        cout << "8. Delete student from ALL courses" << endl;
        cout << "9. Display all" << endl;
        cout << "10. Display courses only" << endl;
        cout << "11. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                while(true) {
                    cout << "Enter course number: ";
                    cin >> val;
                    insert_course(val);
                    cout << "Add more courses? (y/n): ";
                    cin >> state;
                    if (state != "y") break;
                }
                break;
            
            case 2:
                while(true) {
                    cout << "Enter course number: ";
                    cin >> val1;
                    cout << "Enter student seat number: ";
                    cin >> val2;
                    insert_stu(val1, val2);
                    cout << "Add more students? (y/n): ";
                    cin >> state;
                    if (state != "y") break;
                }
                break;
            
            case 3:
                cout << "Enter course number to search: ";
                cin >> val;
                search_course(val);
                break;
            
            case 4:
                cout << "Enter student seat number: ";
                cin >> val;
                search_student(val);
                break;
            
            case 5:
                cout << "Enter course number: ";
                cin >> val1;
                cout << "Enter student seat number: ";
                cin >> val2;
                search_stu_in_course(val1, val2);
                break;
            
            case 6:
                cout << "Enter course number to delete: ";
                cin >> val;
                Delete_course(val);
                break;
            
            case 7:
                cout << "Enter course number: ";
                cin >> val1;
                cout << "Enter student seat number: ";
                cin >> val2;
                Delete_student_from_a_course(val1, val2);
                break;
            
            case 8:
                cout << "Enter student seat number: ";
                cin >> val;
                Delete_student(val);
                break;
            
            case 9:
                display_all();
                break;
            
            case 10:
                display_course();
                break;
            
            case 11:
                exit(0);
            
            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
