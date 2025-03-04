#include <iostream>
#include <fstream>
#include <string>
using namespace std;

fstream file;
string filename = "data.txt";

struct Person {
    string id, firstName, lastName;
    float income;
};

struct Person* search(string id) {
    struct Person* p2 = new Person;
    char empId[6], firstName[15], lastName[15], incomeStr[10];
    file.clear();
    file.seekg(0, ios::beg);
    
    while (file.read(empId, 5)) {
        empId[5] = '\0';
        p2->id = empId;
        
        if (p2->id == id) {
            file.read(firstName, 15);
            file.read(lastName, 15);
            file.read(incomeStr, 10);
            p2->firstName = firstName;
            p2->lastName = lastName;
            p2->income = stof(incomeStr);
            return p2;
        }
        file.seekg(40, ios::cur);
    }
    return nullptr;
}

void get_employee() {
    string empId;
    cout << "Enter employee id: ";
    cin >> empId;

    Person* p = search(empId);
    if (p == nullptr) {
        cout << "Employee not found!" << endl;
    } else {
        cout << "Employee ID: " << p->id << endl;
        cout << "First Name: " << p->firstName << endl;
        cout << "Last Name: " << p->lastName << endl;
        cout << "Income: " << p->income << endl;
        delete p;
    }
}

void list() {
    char id[6], firstName[15], lastName[15], incomeStr[10];
    file.clear();
    file.seekg(0, ios::beg);
    while (file.read(id, 5)) {
        file.read(firstName, 15);
        file.read(lastName, 15);
        file.read(incomeStr, 10);
        
        float income = atof(incomeStr);
        
        cout << id << " " << firstName << " " << lastName << " " << income << endl;
    }
}

void write_data(Person p) {
    file.clear();
    file.write(p.id.c_str(), 5);
    file.write(p.firstName.c_str(), 15);
    file.write(p.lastName.c_str(), 15);
    file.write(to_string(p.income).c_str(), 10);
    file.flush();
}

void new_employee() {
    string empId;
    while (true) {
        cout << "\n*** New Employee ***\n";
        cout << "Enter employee id (-1 to end): ";
        cin >> empId;
        
        if (empId == "-1") break;

        Person* p = search(empId);
        if (p != nullptr) {
            cout << "Employee with this ID already exists!" << endl;
            delete p;
            continue;
        }

        Person pNew;
        pNew.id = empId;
        cout << "Enter first name: ";
        cin >> pNew.firstName;
        cout << "Enter last name: ";
        cin >> pNew.lastName;
        cout << "Enter income: ";
        cin >> pNew.income;

        cout << "Saving data...\n";
        write_data(pNew);
    }
}

int main() {
    file.open(filename, ios::in | ios::out);
    if (!file) {
        file.open(filename, ios::out);
        file.close();
        file.open(filename, ios::in | ios::out);
    }

    int option = -1;
    while (true) {
        cout << "*** Menu ***" << endl;
        cout << "1) New employee\n";
        cout << "2) Search employee information\n";
        cout << "3) List employee\n";
        cout << "option: ";
        cin >> option;

        switch (option) {
            case 1: new_employee(); break;
            case 2: get_employee(); break;
            case 3: list(); break;
            default: return 0;
        }
    }

    file.close();
    return 0;
}
