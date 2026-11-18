// Implement compile-time polymorphism: function overloading and operator
// overloading for a Matrix or Complex Number class.[cite: 1]

#include <iostream>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 1. Function Overloading (setValue)
    void setValue(double r) {
        real = r;
        imag = 0.0;
    }

    void setValue(double r, double i) {
        real = r;
        imag = i;
    }

    // Function Overloading (add)
    Complex add(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex add(double scalar) const {
        return Complex(real + scalar, imag);
    }

    // 2. Operator Overloading (+)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Operator Overloading (-)
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Operator Overloading (*)
    Complex operator*(const Complex& other) const {
        return Complex(
            (real * other.real) - (imag * other.imag),
            (real * other.imag) + (imag * other.real)
        );
    }

    // Operator Overloading (==)
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // Stream Insertion Operator Overloading (<<)
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real;
        if (c.imag >= 0) {
            out << " + " << c.imag << "i";
        } else {
            out << " - " << -c.imag << "i";
        }
        return out;
    }
};

int main() {
    Complex c1(3.0, 4.0);
    Complex c2;

    // Demonstrating Function Overloading
    c2.setValue(2.0, -5.0);
    Complex c3;
    c3.setValue(7.0);

    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c3 = " << c3 << endl;

    cout << "\n--- Function Overloading ---" << endl;
    cout << "c1.add(c2)  = " << c1.add(c2) << endl;
    cout << "c1.add(5.0) = " << c1.add(5.0) << endl;

    // Demonstrating Operator Overloading
    cout << "\n--- Operator Overloading ---" << endl;
    cout << "c1 + c2 = " << (c1 + c2) << endl;
    cout << "c1 - c2 = " << (c1 - c2) << endl;
    cout << "c1 * c2 = " << (c1 * c2) << endl;
    cout << "c1 == c2: " << (c1 == c2 ? "True" : "False") << endl;

    return 0;
}