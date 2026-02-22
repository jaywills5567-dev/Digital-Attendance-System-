#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ================= STUDENT CLASS =================
class Student {
private:
    string indexNumber;
    string name;

public:
    Student(string index = "", string n = "") {
        indexNumber = index;
        name = n;
    }

    string getIndex() const { return indexNumber; }
    string getName() const { return name; }

    void display() const {
        cout << left << setw(15) << indexNumber
             << setw(25) << name << endl;
    }

    string toFileFormat() const {
        return indexNumber + "|" + name;
    }
};

// ================= GLOBAL VARIABLES =================
vector<Student> students;

// ================= STUDENT FUNCTIONS =================
void loadStudents() {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        size_t pos = line.find("|");
        if (pos != string::npos) {
            string index = line.substr(0, pos);
            string name = line.substr(pos + 1);
            students.push_back(Student(index, name));
        }
    }
    file.close();
}

void saveStudents() {
    ofstream file("students.txt");
    for (const auto &s : students)
        file << s.toFileFormat() << endl;
    file.close();
}

bool studentExists(string index) {
    for (const auto &s : students)
        if (s.getIndex() == index)
            return true;
    return false;
}

void registerStudent() {
    string index, name;

    cout << "Enter Index Number: ";
    cin >> index;
    cin.ignore();

    if (studentExists(index)) {
        cout << "Student already exists!\n";
        return;
    }

    cout << "Enter Full Name: ";
    getline(cin, name);

    students.push_back(Student(index, name));
    saveStudents();

    cout << "Student Registered Successfully!\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students registered.\n";
        return;
    }

    cout << left << setw(15) << "Index"
         << setw(25) << "Name" << endl;
    cout << "--------------------------------------\n";

    for (const auto &s : students)
        s.display();
}

void searchStudent() {
    string index;
    cout << "Enter Index Number: ";
    cin >> index;

    for (const auto &s : students) {
        if (s.getIndex() == index) {
            cout << "Student Found:\n";
            s.display();
            return;
        }
    }

    cout << "Student not found.\n";
}

// ================= SESSION FUNCTIONS =================
void createSession() {
    string courseCode, date, startTime;
    int duration;

    cout << "Course Code: ";
    cin >> courseCode;
    cout << "Date (YYYY_MM_DD): ";
    cin >> date;
    cout << "Start Time: ";
    cin >> startTime;
    cout << "Duration (minutes): ";
    cin >> duration;

    string filename = "sessions/session_" + courseCode + "_" + date + ".txt";
    ofstream file(filename);

    file << "Course:" << courseCode << endl;
    file << "Date:" << date << endl;
    file << "StartTime:" << startTime << endl;
    file << "Duration:" << duration << endl;
    file << "---------------------------------\n";

    file.close();
    cout << "Session Created Successfully!\n";
}

void markAttendance() {
    if (students.empty()) {
        cout << "No students registered.\n";
        return;
    }

    string courseCode, date;
    cout << "Course Code: ";
    cin >> courseCode;
    cout << "Date (YYYY_MM_DD): ";
    cin >> date;

    string filename = "sessions/session_" + courseCode + "_" + date + ".txt";
    ofstream file(filename, ios::app);

    int present = 0, absent = 0, late = 0;

    for (const auto &s : students) {
        int choice;
        cout << s.getIndex() << " - " << s.getName() << endl;
        cout << "1.Present 2.Absent 3.Late: ";
        cin >> choice;

        string status;
        switch (choice) {
            case 1: status = "Present"; present++; break;
            case 2: status = "Absent"; absent++; break;
            case 3: status = "Late"; late++; break;
            default: status = "Absent"; absent++;
        }

        file << s.getIndex() << "|" << s.getName()
             << "|" << status << endl;
    }

    file << "---------------------------------\n";
    file << "Summary|Present:" << present
         << "|Absent:" << absent
         << "|Late:" << late << endl;

    file.close();
    cout << "Attendance Recorded Successfully!\n";
}

void viewSessionReport() {
    string courseCode, date;
    cout << "Course Code: ";
    cin >> courseCode;
    cout << "Date (YYYY_MM_DD): ";
    cin >> date;

    string filename = "sessions/session_" + courseCode + "_" + date + ".txt";
    ifstream file(filename);

    if (!file) {
        cout << "Session file not found.\n";
        return;
    }

    string line;
    while (getline(file, line))
        cout << line << endl;

    file.close();
}

// ================= MAIN MENU =================
int main() {
    loadStudents();

    int choice;
    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Session\n";
        cout << "5. Mark Attendance\n";
        cout << "6. View Session Report\n";
        cout << "7. Exit\n";
        cout << "Choose Option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: createSession(); break;
            case 5: markAttendance(); break;
            case 6: viewSessionReport(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid Option.\n";
        }

    } while (choice != 7);

    return 0;
}
