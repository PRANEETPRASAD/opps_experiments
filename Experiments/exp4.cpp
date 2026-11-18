// Implement Single and Multilevel Inheritance for a university management scenario
// (Person -> Student -> GraduateStudent).

#include <iostream>
#include <string>

using namespace std;

// Base Class (Level 1)
class Person {
protected:
    string name;
    int age;

public:
    Person(string personName, int personAge) : name(personName), age(personAge) {}

    void displayPerson() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

// Derived Class from Person (Single Inheritance - Level 2)
class Student : public Person {
protected:
    string studentId;
    string course;

public:
    Student(string personName, int personAge, string id, string courseName)
        : Person(personName, personAge), studentId(id), course(courseName) {}

    void displayStudent() {
        displayPerson();
        cout << "Student ID: " << studentId << endl;
        cout << "Course: " << course << endl;
    }
};

// Derived Class from Student (Multilevel Inheritance - Level 3)
class GraduateStudent : public Student {
private:
    string thesisTitle;
    string advisorName;

public:
    GraduateStudent(string personName, int personAge, string id, string courseName,
                    string thesis, string advisor)
        : Student(personName, personAge, id, courseName),
          thesisTitle(thesis), advisorName(advisor) {}

    void displayGraduateStudent() {
        displayStudent();
        cout << "Thesis Title: " << thesisTitle << endl;
        cout << "Research Advisor: " << advisorName << endl;
    }
};

int main() {
    cout << "--- Single Inheritance (Person -> Student) ---" << endl;
    Student undergrad("Aarav Sharma", 19, "UG202601", "B.Tech AI & Data Science");
    undergrad.displayStudent();

    cout << "\n--- Multilevel Inheritance (Person -> Student -> GraduateStudent) ---" << endl;
    GraduateStudent grad("Praneet Prasad", 23, "PG202645", "M.Tech Computer Science",
                         "Adaptive Memory Models in Agentic AI", "Dr. R. K. Verma");
    grad.displayGraduateStudent();

    return 0;
}