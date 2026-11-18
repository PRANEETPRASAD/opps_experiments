#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class Employee {
private:
    int empId;
    string name;
    string designation;
    double basicSalary;

public:
    Employee(int id = 0, string n = "", string desig = "", double basic = 0.0)
        : empId(id), name(n), designation(desig), basicSalary(basic) {}

    int getId() const { return empId; }
    string getName() const { return name; }
    string getDesignation() const { return designation; }
    double getBasicSalary() const { return basicSalary; }

    double getHRA() const { return basicSalary * 0.20; }        // 20% HRA
    double getDA() const { return basicSalary * 0.10; }         // 10% DA
    double getDeductions() const { return basicSalary * 0.12; } // 12% PF/Tax
    double getNetSalary() const {
        return basicSalary + getHRA() + getDA() - getDeductions();
    }

    void printPayslip() const {
        cout << "\n==========================================" << endl;
        cout << "             EMPLOYEE PAYSLIP             " << endl;
        cout << "==========================================" << endl;
        cout << "Employee ID   : " << empId << endl;
        cout << "Name          : " << name << endl;
        cout << "Designation   : " << designation << endl;
        cout << "------------------------------------------" << endl;
        cout << fixed << setprecision(2);
        cout << "Basic Salary  : " << basicSalary << endl;
        cout << "HRA (20%)     : +" << getHRA() << endl;
        cout << "DA (10%)      : +" << getDA() << endl;
        cout << "PF/Tax (12%)  : -" << getDeductions() << endl;
        cout << "------------------------------------------" << endl;
        cout << "Net Salary    : " << getNetSalary() << endl;
        cout << "==========================================\n" << endl;
    }

    string toCSV() const {
        return to_string(empId) + "," + name + "," + designation + "," + to_string(basicSalary);
    }
};

class PayrollSystem {
private:
    vector<Employee> employees;
    const string filename = "payroll.csv";

    void saveToFile() {
        ofstream outFile(filename);
        outFile << "ID,Name,Designation,BasicSalary,NetSalary\n";
        for (const auto& emp : employees) {
            outFile << emp.toCSV() << "," << emp.getNetSalary() << "\n";
        }
    }

    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) return;

        string line;
        getline(inFile, line); // Skip CSV header
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string idStr, name, desig, basicStr;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, desig, ',');
            getline(ss, basicStr, ',');

            employees.emplace_back(stoi(idStr), name, desig, stod(basicStr));
        }
    }

public:
    PayrollSystem() { loadFromFile(); }

    void addEmployee() {
        int id;
        string name, desig;
        double basic;

        cout << "Enter Employee ID: ";
        cin >> id;
        for (const auto& emp : employees) {
            if (emp.getId() == id) {
                cout << "Error: Employee ID already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Designation: ";
        getline(cin, desig);
        cout << "Enter Basic Salary: ";
        cin >> basic;

        if (basic < 0) {
            cout << "Error: Salary cannot be negative!\n";
            return;
        }

        employees.emplace_back(id, name, desig, basic);
        saveToFile();
        cout << "Employee added and saved successfully!\n";
    }

    void displayAll() const {
        if (employees.empty()) {
            cout << "No employee records found.\n";
            return;
        }
        cout << "\n" << left << setw(8) << "ID" << setw(20) << "Name"
             << setw(18) << "Designation" << setw(12) << "Basic" << "Net Salary\n";
        cout << string(70, '-') << "\n";
        cout << fixed << setprecision(2);
        for (const auto& emp : employees) {
            cout << left << setw(8) << emp.getId()
                 << setw(20) << emp.getName()
                 << setw(18) << emp.getDesignation()
                 << setw(12) << emp.getBasicSalary()
                 << emp.getNetSalary() << "\n";
        }
    }

    void generatePayslip() const {
        int id;
        cout << "Enter Employee ID for Payslip: ";
        cin >> id;
        for (const auto& emp : employees) {
            if (emp.getId() == id) {
                emp.printPayslip();
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void deleteEmployee() {
        int id;
        cout << "Enter Employee ID to delete: ";
        cin >> id;
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->getId() == id) {
                employees.erase(it);
                saveToFile();
                cout << "Employee deleted successfully.\n";
                return;
            }
        }
        cout << "Employee not found.\n";
    }
};

int main() {
    PayrollSystem system;
    int choice;

    while (true) {
        cout << "\n--- Employee Payroll Management System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Generate Payslip\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.addEmployee(); break;
            case 2: system.displayAll(); break;
            case 3: system.generatePayslip(); break;
            case 4: system.deleteEmployee(); break;
            case 5: return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}