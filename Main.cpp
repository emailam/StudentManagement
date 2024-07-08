#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <string>
#include "Student.h"
#include "BST.h"
#include "AVL.h"
using namespace std;

template<typename T>
void loadDataFromFile(T &tree){
    ifstream file("StudentsData.txt");
    string line;
    if (file.is_open()){
        int cnt = 1 ;
        Student student;
        getline(file,line);
        int n = stoi(line);
        while (getline(file, line)){
            if(cnt == 1){
                student.id = stoi(line);
            }
            else if(cnt == 2){
                student.name = line;
            }
            else if(cnt == 3){
                student.gpa = stod(line);
            }
            else if(cnt == 4){
                student.department = line;
                tree.insertStudent(student);
                cnt=0;
            }
            cnt++;
        }
        file.close();
    }
    else cout << "File not found !" << endl;
}

int main(){
    int choice = 0 ;
    while(choice != 5){
        cout << "Choose Data Structure: " << endl;
        cout << "1- BST" << endl;
        cout << "2- AVL" << endl;
        cout << "3- Min Heap" << endl;
        cout << "4- Max Heap" << endl;
        cout << "5- Exit Program" << endl;
        cin >> choice;
        if(choice == 1){
            BST bst;
            loadDataFromFile(bst);
            while(true){
                cout << "Choose one of the following options:" << endl;
                cout << "1- Add student" << endl;
                cout << "2- Remove student" << endl;
                cout << "3- Search student" << endl;
                cout << "4- Print All" << endl;
                cout << "5- Return to main menu" << endl;
                int innerChoice ;
                cin >> innerChoice;
                if(innerChoice == 1){
                    Student student;
                    cout << "Enter student ID : " ;
                    cin >> student.id ;
                    cout << "Enter student Name : " ;
                    cin >> student.name ;
                    cout << "Enter student GPA : " ;
                    cin >> student.gpa ;
                    cout << "Enter student Department : " ;
                    cin >> student.department ;
                    bst.insertStudent(student);
                    cout << "Student added successfully :)" << endl;
                }
                else if(innerChoice == 2){
                    cout << "Enter ID of the student you want to delete : " << endl;
                    int id; cin >> id;
                    Student student = bst.search(id);
                    if(student.name != "NULL"){
                        bst.removeStudent(student);
                        cout << "Student deleted successfully :)" << endl;
                    }
                }
                else if(innerChoice == 3){
                    cout << "Enter student ID : " ;
                    int id ; cin >> id ;
                    bst.search(id);
                }
                else if(innerChoice == 4){
                    bst.print();
                    cout << endl;
                }
                else if(innerChoice == 5){
                    break;
                }
            }
        }
        else if(choice == 2){
            AVL tree ;
            loadDataFromFile(tree);
            while(true){
                cout << "Choose one of the following options:" << endl;
                cout << "1- Add student" << endl;
                cout << "2- Remove student" << endl;
                cout << "3- Search student" << endl;
                cout << "4- Print All" << endl;
                cout << "5- Return to main menu" << endl;
                int innerChoice ;
                cin >> innerChoice;
                if(innerChoice == 1){
                    Student student;
                    cout << "Enter student ID : " ;
                    cin >> student.id ;
                    cout << "Enter student Name : " ;
                    cin >> student.name ;
                    cout << "Enter student GPA : " ;
                    cin >> student.gpa ;
                    cout << "Enter student Department : " ;
                    cin >> student.department ;
                    tree.insertStudent(student);
                    cout << "Student added successfully :)" << endl;
                }
                else if(innerChoice == 2){
                    cout << "Enter ID of the student you want to delete : " << endl;
                    int id; cin >> id;
                    Student student = tree.search(id);
                    if(student.name == "NULL") cout << "Student not found !" << endl;
                    else{
                        tree.removeStudent(student);
                        cout << "Student deleted successfully :)" << endl;
                    }
                }
                else if(innerChoice == 3){
                    cout << "Enter student ID : " ;
                    int id ; cin >> id ;
                    if(tree.search(id).name == "NULL") cout << "Student not found !" << endl;
                }
                else if(innerChoice == 4){
                    tree.inOrderPrint();
                    cout << endl;
                    tree.printDepartments();
                }
                else if(innerChoice == 5){
                    break;
                }
            }
        }
        else if(choice == 5){
            exit(0);
        }
    }
}


