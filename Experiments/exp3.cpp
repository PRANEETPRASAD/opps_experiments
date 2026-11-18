// Implement a class demonstrating all constructor types (Default, Parameterized, Copy, Move).
// Apply the Rule of 5. Verify with Valgrind for memory leaks.

#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

class Buffer {
private:
    char* data;
    size_t size;

public:
    // 1. Default Constructor
    Buffer() : data(nullptr), size(0) {
        cout << "Default Constructor called" << endl;
    }

    // 2. Parameterized Constructor
    Buffer(const char* str) {
        size = strlen(str);
        data = new char[size + 1];
        strcpy(data, str);
        cout << "Parameterized Constructor called for: " << data << endl;
    }

    // 3. Destructor (Rule of 5 - #1)
    ~Buffer() {
        cout << "Destructor called for: " << (data ? data : "null") << endl;
        delete[] data;
    }

    // 4. Copy Constructor (Rule of 5 - #2)
    Buffer(const Buffer& other) : size(other.size) {
        if (other.data) {
            data = new char[size + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
        cout << "Copy Constructor called for: " << (data ? data : "null") << endl;
    }

    // 5. Copy Assignment Operator (Rule of 5 - #3)
    Buffer& operator=(const Buffer& other) {
        cout << "Copy Assignment Operator called" << endl;
        if (this == &other) {
            return *this;
        }
        delete[] data;
        size = other.size;
        if (other.data) {
            data = new char[size + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
        return *this;
    }

    // 6. Move Constructor (Rule of 5 - #4)
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Move Constructor called for: " << (data ? data : "null") << endl;
    }

    // 7. Move Assignment Operator (Rule of 5 - #5)
    Buffer& operator=(Buffer&& other) noexcept {
        cout << "Move Assignment Operator called" << endl;
        if (this == &other) {
            return *this;
        }
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        return *this;
    }

    void display() const {
        cout << "Buffer Content: " << (data ? data : "[Empty]") << endl;
    }
};

int main() {
    Buffer b1;                          // Default Constructor
    Buffer b2("Hello C++");             // Parameterized Constructor
    Buffer b3 = b2;                     // Copy Constructor
    b1 = b2;                            // Copy Assignment Operator

    Buffer b4 = std::move(b2);          // Move Constructor
    Buffer b5;
    b5 = std::move(b3);                 // Move Assignment Operator

    cout << "\n--- Final States ---" << endl;
    b1.display();
    b2.display();
    b3.display();
    b4.display();
    b5.display();
    cout << endl;

    return 0;
}