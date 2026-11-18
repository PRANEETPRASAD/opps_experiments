// Use STL containers (vector, map, unordered_map) and algorithms (sort, find_if, transform)
// to process a student marks dataset.[cite: 1]

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    int rollNo;
    string name;
    int marks;
};

int main() {
    // 1. std::vector to store student records
    vector<Student> students = {
        {103, "Rohan", 78},
        {101, "Aarav", 92},
        {104, "Sneha", 64},
        {102, "Isha", 85}
    };

    // 2. std::sort - Sort students by marks in descending order
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.marks > b.marks;
    });

    cout << "--- Sorted Students (Descending Marks) ---" << endl;
    for (const auto& s : students) {
        cout << s.rollNo << " | " << s.name << " : " << s.marks << endl;
    }

    // 3. std::find_if - Find first student scoring below 75
    auto it = find_if(students.begin(), students.end(), [](const Student& s) {
        return s.marks < 75;
    });

    cout << "\n--- First Student Scoring Below 75 ---" << endl;
    if (it != students.end()) {
        cout << "Found: " << it->name << " (Roll: " << it->rollNo << ", Marks: " << it->marks << ")" << endl;
    } else {
        cout << "None found." << endl;
    }

    // 4. std::transform - Add 5 grace marks (capped at 100) into a new vector
    vector<int> updatedMarks(students.size());
    transform(students.begin(), students.end(), updatedMarks.begin(), [](const Student& s) {
        return min(100, s.marks + 5);
    });

    // 5. std::map - Ordered mapping of Roll Number -> Updated Marks
    map<int, int> orderedMarksMap;
    // 6. std::unordered_map - Fast lookup of Student Name -> Grade
    unordered_map<string, char> gradeLookup;

    for (size_t i = 0; i < students.size(); i++) {
        orderedMarksMap[students[i].rollNo] = updatedMarks[i];

        char grade = (updatedMarks[i] >= 90) ? 'A' :
                     (updatedMarks[i] >= 80) ? 'B' :
                     (updatedMarks[i] >= 70) ? 'C' : 'D';
        gradeLookup[students[i].name] = grade;
    }

    cout << "\n--- std::map (Ordered by Roll No with Grace Marks) ---" << endl;
    for (const auto& entry : orderedMarksMap) {
        cout << "Roll No " << entry.first << " -> " << entry.second << endl;
    }

    cout << "\n--- std::unordered_map (Grade Lookup) ---" << endl;
    for (const auto& entry : gradeLookup) {
        cout << entry.first << " : Grade " << entry.second << endl;
    }

    return 0;
}