#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct student
{
    int roll;
    char name[30];
};

int getPos(int roll)
{
    return (roll - 1) * sizeof(student);
}

void insert()
{
    student s;
    cout << "Enter roll: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter name: ";
    cin.getline(s.name, 30);

    fstream file("student.dat", ios::in | ios::out | ios::binary);
    if (!file)
    {
        file.open("student.dat", ios::out | ios::binary);
        file.close();
        file.open("student.dat", ios::in | ios::out | ios::binary);
    }

    file.seekp(getPos(s.roll));
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Inserted.\n";
}

void display()
{
    int roll;
    cout << "Enter the roll: ";
    cin >> roll;

    student s;
    ifstream file("student.dat", ios::binary);
    if (!file)
    {
        cout << "File not found.\n";
        return;
    }

    file.seekg(getPos(roll));
    file.read((char*)&s, sizeof(s));

    if (file && s.roll != -1 && s.roll == roll)
    {
        cout << "Roll: " << s.roll << " Name: " << s.name << endl;
    }
    else
    {
        cout << "Record not found.\n";
    }

    file.close();
}

void del()
{
    int roll;
    cout << "Enter roll: ";
    cin >> roll;

    fstream file("student.dat", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "Unable to open file.\n";
        return;
    }

    student s;
    file.seekg(getPos(roll));
    file.read((char*)&s, sizeof(s));

    if (!file || s.roll == -1 || s.roll != roll)
    {
        cout << "Record not found.\n";
        file.close();
        return;
    }

    s.roll = -1;
    strcpy(s.name, "");

    file.seekp(getPos(roll));
    file.write((char*)&s, sizeof(s));
    cout << "Record Deleted.\n";
    file.close();
}

int main()
{
    int ch;
    while (true)
    {
        cout << "\nSelect one option:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch)
        {
            case 1:
                insert();
                break;
            case 2:
                del();
                break;
            case 3:
                display();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}