// Write a generic Stack or Queue class using templates. Test with int, float, and std::string.[cite: 1]

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Stack {
private:
    T* arr;
    int top;
    int capacity;

public:
    Stack(int size = 5) {
        capacity = size;
        arr = new T[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == capacity - 1;
    }

    void push(T item) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << item << endl;
            return;
        }
        arr[++top] = item;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Stack is empty." << endl;
            return;
        }
        top--;
    }

    T peek() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return arr[top];
    }

    void display() const {
        if (isEmpty()) {
            cout << "[Empty]" << endl;
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // 1. Testing with int
    cout << "--- Integer Stack ---" << endl;
    Stack<int> intStack(3);
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    cout << "Stack elements (top to bottom): ";
    intStack.display();
    cout << "Top element: " << intStack.peek() << endl;
    intStack.pop();
    cout << "After pop: ";
    intStack.display();

    // 2. Testing with float
    cout << "\n--- Float Stack ---" << endl;
    Stack<float> floatStack(3);
    floatStack.push(1.5f);
    floatStack.push(2.75f);
    floatStack.push(3.14f);
    cout << "Stack elements (top to bottom): ";
    floatStack.display();
    cout << "Top element: " << floatStack.peek() << endl;
    floatStack.pop();
    cout << "After pop: ";
    floatStack.display();

    // 3. Testing with std::string
    cout << "\n--- String Stack ---" << endl;
    Stack<string> stringStack(3);
    stringStack.push("First");
    stringStack.push("Second");
    stringStack.push("Third");
    cout << "Stack elements (top to bottom): ";
    stringStack.display();
    cout << "Top element: " << stringStack.peek() << endl;
    stringStack.pop();
    cout << "After pop: ";
    stringStack.display();

    return 0;
}