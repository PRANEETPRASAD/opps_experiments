// Set up a GitHub repository. Write a C++ program to demonstrate data types,
// constants, variables, operators, and I/O. Commit with a meaningful message.

#include <iostream>
#include <string>

using namespace std;

int main() {
    // 1. Constants
    const double TAX_RATE = 0.05;
    constexpr int MAX_ITEMS = 100;

    // 2. Data Types & Variables
    string itemName;
    int quantity;
    double unitPrice;
    char categoryCode;
    bool isMember;

    // 3. Input (I/O)
    cout << "Enter item name: ";
    getline(cin, itemName);

    cout << "Enter category code (A/B/C): ";
    cin >> categoryCode;

    cout << "Enter quantity (max " << MAX_ITEMS << "): ";
    cin >> quantity;

    cout << "Enter unit price: ";
    cin >> unitPrice;

    cout << "Are you a member? (1 for Yes, 0 for No): ";
    cin >> isMember;

    // 4. Operators
    // Arithmetic Operators
    double subtotal = quantity * unitPrice;
    double tax = subtotal * TAX_RATE;
    double total = subtotal + tax;

    // Relational, Logical & Ternary Operators
    bool eligibleForDiscount = (quantity >= 5) && isMember;
    double discount = eligibleForDiscount ? (total * 0.10) : 0.0;

    // Compound Assignment Operator
    total -= discount;

    // Increment Operator
    int receiptNumber = 1000;
    receiptNumber++;

    // 5. Output (I/O)
    cout << "\n--- Receipt #" << receiptNumber << " ---" << endl;
    cout << "Item: " << itemName << " [" << categoryCode << "]" << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Subtotal: " << subtotal << endl;
    cout << "Tax (5%): " << tax << endl;
    cout << "Discount Applied: " << (eligibleForDiscount ? "Yes" : "No") << " (-" << discount << ")" << endl;
    cout << "Final Total: " << total << endl;

    return 0;
}