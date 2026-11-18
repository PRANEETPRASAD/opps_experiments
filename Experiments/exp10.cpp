// Implement a CSV file reader/writer using file I/O (fstream). Store and retrieve
// student records. Use file pointers (seekg, seekp, tellg, tellp).[cite: 1]

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

// Format record to fixed-width CSV line (32 bytes + newline) for reliable random access with seekp/seekg
string formatRecord(const Student& s) {
    ostringstream oss;
    oss << setw(4) << setfill('0') << s.rollNo << ","
        << left << setw(18) << setfill(' ') << s.name.substr(0, 18) << ","
        << right << setw(6) << fixed << setprecision(2) << s.marks;
    return oss.str();
}

int main() {
    const string filename = "students.csv";

    // 1. Write student records to CSV using fstream (demonstrating tellp & seekp)
    fstream outFile(filename, ios::out | ios::trunc);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    string header = "Roll,Name              ,Marks ";
    outFile << header << "\n";
    streampos headerEndPos = outFile.tellp();
    cout << "Header written. Current put pointer (tellp): " << headerEndPos << endl;

    Student records[3] = {
        {101, "Aarav Sharma", 88.50f},
        {102, "Isha Verma", 92.00f},
        {103, "Rohan Kulkarni", 76.25f}
    };

    streampos secondRecordPos;
    for (int i = 0; i < 3; i++) {
        if (i == 1) {
            secondRecordPos = outFile.tellp(); // Save byte offset of 2nd record
        }
        outFile << formatRecord(records[i]) << "\n";
    }
    cout << "All 3 records written. End put pointer (tellp): " << outFile.tellp() << endl;
    outFile.close();

    // 2. Update 2nd record in-place using seekp and tellp
    fstream updateFile(filename, ios::in | ios::out);
    if (!updateFile) {
        cerr << "Error opening file for updating!" << endl;
        return 1;
    }

    updateFile.seekp(secondRecordPos, ios::beg);
    cout << "\nMoved put pointer using seekp to byte: " << updateFile.tellp() << endl;
    Student updatedRecord = {102, "Isha Verma", 96.50f};
    updateFile << formatRecord(updatedRecord);
    updateFile.close();

    // 3. Read records from CSV using fstream (demonstrating seekg & tellg)
    fstream inFile(filename, ios::in);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }

    cout << "\n--- Reading All Records from CSV ---" << endl;
    string line;
    while (getline(inFile, line)) {
        cout << line << "  [tellg: " << inFile.tellg() << "]" << endl;
    }

    // Clear EOF flag before seeking again
    inFile.clear();

    // Jump directly to 2nd record using seekg
    inFile.seekg(secondRecordPos, ios::beg);
    cout << "\n--- Random Access Read via seekg (byte " << inFile.tellg() << ") ---" << endl;
    getline(inFile, line);

    stringstream ss(line);
    string rollStr, nameStr, marksStr;
    getline(ss, rollStr, ',');
    getline(ss, nameStr, ',');
    getline(ss, marksStr, ',');

    cout << "Retrieved Roll No : " << stoi(rollStr) << endl;
    cout << "Retrieved Name    : " << nameStr << endl;
    cout << "Retrieved Marks   : " << stof(marksStr) << endl;

    inFile.close();
    return 0;
}