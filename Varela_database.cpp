#include <iostream>
#include <fstream>
#include <string>
using namespace std;
fstream file;
string filename = "data.txt";
struct Person {
string id, firstName, lastName;
int income;
}; 

int main() {
Person p;
file.open(filename);
file >> p.id >> p.firstName >> p.lastName >> p.income;
file.close();
cout << "ID: " << p.id << endl;
cout << "First name: " << p.firstName << endl;
cout << "Last name: " << p.lastName << endl;
cout << "Income: $" << p.income << endl;
return 0;
}