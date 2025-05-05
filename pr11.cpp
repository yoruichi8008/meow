#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name;
    string div;
    string add;
};

void addStudent() {
    Student s;
    ofstream w("student.txt", ios::app);
    if (!w) {
        cout << "Unable to open file!" << endl;
        return;
    }

    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Division: ";
    getline(cin, s.div);
    cout << "Enter Address: ";
    getline(cin, s.add);

    w << s.roll << endl;
    w << s.name << endl;
    w << s.div << endl;
    w << s.add << endl;

    w.close();
    cout << "Record added successfully." << endl;
}

void displayStudent(int roll) {
    Student s;
    ifstream r("student.txt");
    if (!r) {
        cout << "Unable to open file!" << endl;
        return;
    }

    bool found = false;
    while (r >> s.roll) {
        r.ignore();
        getline(r, s.name);
        getline(r, s.div);
        getline(r, s.add);

        if (s.roll == roll) {
            cout << "\n--- Student Record Found ---" << endl;
            cout << "Roll Number : " << s.roll << endl;
            cout << "Name        : " << s.name << endl;
            cout << "Division    : " << s.div << endl;
            cout << "Address     : " << s.add << endl;
            found = true;
            break;
        }
    }

    r.close();
    if (!found) {
        cout << "Record not found." << endl;
    }
}

void deleteStudent(int roll) {
    Student s;
    ifstream r("student.txt");
    ofstream w("temp.txt", ios::trunc);

    if (!r || !w) {
        cout << "Unable to open file!" << endl;
        return;
    }

    bool found = false;
    while (r >> s.roll) {
        r.ignore();
        getline(r, s.name);
        getline(r, s.div);
        getline(r, s.add);

        if (s.roll == roll) {
            cout << "Record with roll " << roll << " deleted." << endl;
            found = true;
        }

        w << s.roll << endl;
        w << s.name << endl;
        w << s.div << endl;
        w << s.add << endl;
    }

    r.close();
    w.close();

    if (found) {
        remove("student.txt");
        rename("temp.txt", "student.txt");
    } else {
        cout << "Record not found." << endl;
        remove("temp.txt");
    }
}

int main() {
    int choice, roll_no;

    while (true) {
        cout << "\n--- Student Information System ---" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Display Student Record" << endl;
        cout << "3. Delete Student Record" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to display: ";
                cin >> roll_no;
                displayStudent(roll_no);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> roll_no;
                deleteStudent(roll_no);
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again!" << endl;
        }
    }

    return 0;
}