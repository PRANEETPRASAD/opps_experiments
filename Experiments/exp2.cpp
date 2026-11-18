// Design and implement a class hierarchy for a real-world entity (e.g., BankAccount, Vehicle).
// Demonstrate access specifiers and member functions.

#include <iostream>
#include <string>

using namespace std;

// Base Class
class BankAccount {
private:
    // Private: Accessible only within BankAccount
    string pin;

protected:
    // Protected: Accessible within BankAccount and derived classes
    string accountNumber;
    string holderName;
    double balance;

public:
    // Public: Accessible from anywhere
    BankAccount(string accNum, string name, double initialBalance, string accountPin) {
        accountNumber = accNum;
        holderName = name;
        balance = initialBalance;
        pin = accountPin;
    }

    bool verifyPin(string inputPin) {
        return pin == inputPin;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount, string inputPin) {
        if (!verifyPin(inputPin)) {
            cout << "Incorrect PIN. Transaction denied." << endl;
            return;
        }
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | Remaining Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds or invalid amount." << endl;
        }
    }

    void displayDetails() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << holderName << endl;
        cout << "Current Balance: " << balance << endl;
    }
};

// Derived Class
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string name, double initialBalance, string accountPin, double rate)
        : BankAccount(accNum, name, initialBalance, accountPin) {
        interestRate = rate;
    }

    void applyInterest() {
        // Accessing protected member 'balance' from base class
        double interest = balance * (interestRate / 100.0);
        balance += interest;
        cout << "Interest Added (" << interestRate << "%): " << interest << endl;
    }

    void displaySavingsSummary() {
        displayDetails();
        cout << "Account Type: Savings (" << interestRate << "% p.a.)" << endl;
    }
};

int main() {
    SavingsAccount acc("SB1024", "Praneet Prasad", 5000.0, "1234", 4.5);

    acc.displaySavingsSummary();
    cout << endl;

    acc.deposit(1500.0);
    acc.applyInterest();
    acc.withdraw(2000.0, "1234");
    cout << endl;

    acc.displaySavingsSummary();

    return 0;
}