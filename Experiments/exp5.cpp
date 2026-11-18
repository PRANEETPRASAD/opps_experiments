// Demonstrate runtime polymorphism using virtual functions and an abstract base class.
// Implement a Shape hierarchy (Circle, Rectangle, Triangle) with an area() method.

#include <iostream>
#include <cmath>

using namespace std;

// Abstract Base Class
class Shape {
public:
    // Pure virtual function
    virtual double area() const = 0;

    // Virtual function
    virtual void display() const {
        cout << "Area: " << area() << endl;
    }

    // Virtual destructor
    virtual ~Shape() {}
};

// Derived Class: Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    void display() const override {
        cout << "Circle (Radius = " << radius << ") -> Area: " << area() << endl;
    }
};

// Derived Class: Rectangle
class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double area() const override {
        return length * width;
    }

    void display() const override {
        cout << "Rectangle (" << length << " x " << width << ") -> Area: " << area() << endl;
    }
};

// Derived Class: Triangle
class Triangle : public Shape {
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    double area() const override {
        return 0.5 * base * height;
    }

    void display() const override {
        cout << "Triangle (Base = " << base << ", Height = " << height << ") -> Area: " << area() << endl;
    }
};

int main() {
    // Base class pointers pointing to derived class objects (Runtime Polymorphism)
    Shape* shapes[3];

    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 6.0);
    shapes[2] = new Triangle(3.0, 8.0);

    for (int i = 0; i < 3; i++) {
        shapes[i]->display();
    }

    // Free allocated memory
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }

    return 0;
}