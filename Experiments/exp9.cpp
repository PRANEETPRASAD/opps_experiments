// Create a custom exception hierarchy. Write a program that throws and catches
// specific exceptions for a banking transaction scenario.[cite: 1]

#include <iostream>
#include <exception>
#include <string>

using namespace std;

// Base Custom Exception Class
class BankingException : public exception {
protected:
    string message;

public:
    BankingException(const string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Derived Exception 1: Invalid Amount
class InvalidAmountException : public BankingException {
public:
    InvalidAmountException(double amount)
        : BankingException("Invalid Amount Error: Transaction amount (" + to_string(amount) + ") must be greater than zero.") {}
};

// Derived Exception 2: Insufficient Funds
class InsufficientFundsException : public BankingException {
public:
    InsufficientFundsException(double balance, double requested)
        : BankingException("Insufficient Funds Error: Available balance (" + to_string(balance) +
                           ") is less than requested withdrawal (" + to_string(requested) + ").") {}
};

// Derived Exception 3: Daily Limit Exceeded
class DailyLimitExceededException : public BankingException {
public:
    DailyLimitExceededException(double limit)
        : BankingException("Daily Limit Error: Withdrawal exceeds single-transaction limit of " + to_string(limit) + ".") {}
};

class BankAccount {
private:
    string holderName;
    double balance;
    const double MAX_WITHDRAWAL_LIMIT = 10000.0;

public:
    BankAccount(string name, double initialBalance)
        : holderName(name), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException(amount);
        }
        balance += amount;
        cout << "Deposited " << amount << " | New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException(amount);
        }
        if (amount > MAX_WITHDRAWAL_LIMIT) {
            throw DailyLimitExceededException(MAX_WITHDRAWAL_LIMIT);
        }
        if (amount > balance) {
            throw InsufficientFundsException(balance, amount);
        }
        balance -= amount;
        cout << "Withdrawn " << amount << " | Remaining Balance: " << balance << endl;
    }
};

int main() {
    BankAccount account("Praneet Prasad", 8000.0);

    // Test Case 1: Valid Deposit
    try {
        account.deposit(4000.0);
    } catch (const BankingException& e) {
        cerr << "Caught Exception: " << e.what() << endl;
    }

    // Test Case 2: Invalid Amount Exception
    try {
        account.deposit(-500.0);
    } catch (const InvalidAmountException& e) {
        cerr << "Caught Specific Exception -> " << e.what() << endl;
    }

    // Test Case 3: Daily Limit Exceeded Exception
    try {
        account.withdraw(11000.0);
    } catch (const DailyLimitExceededException& e) {
        cerr << "Caught Specific Exception -> " << e.what() << endl;
    }

    // Test Case 4: Insufficient Funds Exception
    try {
        account.withdraw(13000.0); // Exceeds limit first if > 10000; let's withdraw 9500 after withdrawing 4000
    } catch (const BankingException& e) {
        cerr << "Caught Exception -> " << e.what() << endl;
    }

    // Test Case 5: Valid Withdrawal followed by Insufficient Funds
    try {
        account.withdraw(5000.0);
        account.withdraw(8000.0); // Balance is 7000, within 10000 limit, triggers InsufficientFundsException
    } catch (const InsufficientFundsException& e) {
        cerr << "Caught Specific Exception -> " << e.what() << endl;
    } catch (const BankingException& e) {
        cerr << "Caught Base Banking Exception -> " << e.what() << endl;
    }

    return 0;
}