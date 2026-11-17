#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Student {
private:
    int id;
    string name;
    double gpa;

public:
    Student(int studentId, string studentName, double studentGpa) {
        id = studentId;
        name = studentName;
        gpa = studentGpa;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getGpa() const { return gpa; }

    void display() const {
        cout << left << setw(10) << id 
             << setw(25) << name 
             << setw(10) << fixed << setprecision(2) << gpa << endl;
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;
    const string filename = "students.txt";

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& student : students) {
                file << student.getId() << "," << student.getName() << "," << student.getGpa() << endl;
            }
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            int id;
            string name;
            double gpa;
            char comma;

            students.clear();
            while (file >> id >> comma) {
                getline(file, name, ',');
                file >> gpa;
                students.push_back(Student(id, name, gpa));
            }
            file.close();
        }
    }

public:
    StudentManagementSystem() {
        loadFromFile();
    }

    void addStudent() {
        int id;
        string name;
        double gpa;

        cout << "\n--- Add New Student ---\n";
        cout << "Enter Student ID: ";
        cin >> id;
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter GPA: ";
        cin >> gpa;

        students.push_back(Student(id, name, gpa));
        saveToFile();
        cout << "Student added and saved successfully!\n";
    }

    void displayAllStudents() {
        if (students.empty()) {
            cout << "\nNo student records found.\n";
            return;
        }

        cout << "\n--- Registered Students List ---\n";
        cout << left << setw(10) << "ID" 
             << setw(25) << "Name" 
             << setw(10) << "GPA" << endl;
        cout << "-------------------------------------------\n";
        
        for (const auto& student : students) {
            student.display();
        }
    }

    void searchStudent() {
        if (students.empty()) {
            cout << "\nNo records available to search.\n";
            return;
        }

        int searchId;
        cout << "\nEnter Student ID to search: ";
        cin >> searchId;

        bool found = false;
        for (const auto& student : students) {
            if (student.getId() == searchId) {
                cout << "\nStudent Found:\n";
                cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(10) << "GPA" << endl;
                cout << "-------------------------------------------\n";
                student.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Error: Student with this ID not found.\n";
        }
    }
};

int main() {
    StudentManagementSystem sms;
    int choice;

    do {
        cout << "\n===============================\n";
        cout << "   Student Management System   \n";
        cout << "===============================\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                sms.addStudent();
                break;
            case 2:
                sms.displayAllStudents();
                break;
            case 3:
                sms.searchStudent();
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
