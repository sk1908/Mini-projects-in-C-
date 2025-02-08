#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\nPress any key to continue...";
    getch();
}

double calculateGPA(const vector<double>& credits, const vector<double>& points) {
    double sum = 0;
    double totalCredits = 0;
    
    for (size_t i = 0; i < credits.size(); ++i) {
        sum += credits[i] * points[i];
        totalCredits += credits[i];
    }

    return totalCredits > 0 ? sum / totalCredits : 0;
}

void calculateGPA() {
    clearScreen();
    cout << "---------------------------------" << endl;
    cout << "          GPA Calculator          " << endl;
    cout << "---------------------------------" << endl;

    int numSubjects;
    cout << "Enter number of subjects: ";
    cin >> numSubjects;

    if (numSubjects <= 0) {
        cout << "Invalid number of subjects!" << endl;
        pause();
        return;
    }

    vector<double> credits(numSubjects);
    vector<double> points(numSubjects);

    for (int i = 0; i < numSubjects; ++i) {
        cout << "Enter credits for subject " << i + 1 << ": ";
        cin >> credits[i];
        cout << "Enter points for subject " << i + 1 << ": ";
        cin >> points[i];
        cout << "----------------------------------------------" << endl;
    }

    double gpa = calculateGPA(credits, points);
    cout << endl;
    cout << "Your GPA: " << gpa << endl;
    pause();
}

double calculateCGPA(const vector<double>& gpas) {
    double sum = 0;
    for (double gpa : gpas) {
        sum += gpa;
    }
    return gpas.size() > 0 ? sum / gpas.size() : 0;
}

void calculateCGPA() {
    clearScreen();
    cout << "---------------------------------" << endl;
    cout << "          CGPA Calculator         " << endl;
    cout << "---------------------------------" << endl;

    int numSemesters;
    cout << "Enter number of semesters: ";
    cin >> numSemesters;

    if (numSemesters <= 0) {
        cout << "Invalid number of semesters!" << endl;
        pause();
        return;
    }

    vector<double> gpas(numSemesters);

    for (int i = 0; i < numSemesters; ++i) {
        cout << "Enter GPA for semester " << i + 1 << ": ";
        cin >> gpas[i];
    }

    double cgpa = calculateCGPA(gpas);
    cout << endl;
    cout << "Your CGPA: " << cgpa << endl;
    pause();
}

void showInstructions() {
    clearScreen();
    cout << "How to calculate GPA and CGPA:" << endl;
    cout << "-------------------------------" << endl << endl;
    cout << "GPA = Sum of (Credit * Points) / Total Credits" << endl << endl;
    cout << "CGPA = Sum of GPAs for all semesters / Number of Semesters" << endl << endl;
    cout << "Grade - Point Table:" << endl;
    cout << "---------------------" << endl;
    cout << "Grade \t\t 4.0 Scale" << endl;
    cout << "---------------------" << endl;
    cout << "A+ \t\t 4.0" << endl;
    cout << "A \t\t 4.0" << endl;
    cout << "A- \t\t 3.7" << endl;
    cout << "B+ \t\t 3.3" << endl;
    cout << "B \t\t 3.0" << endl;
    cout << "B- \t\t 2.7" << endl;
    cout << "C+ \t\t 2.3" << endl;
    cout << "C \t\t 2.0" << endl;
    cout << "C- \t\t 1.7" << endl;
    cout << "D+ \t\t 1.3" << endl;
    cout << "D \t\t 1.0" << endl;
    cout << "D- \t\t 0.7" << endl;
    cout << "F \t\t 0.0" << endl;
    pause();
}

int main() {
    char option;

    do {
        clearScreen();
        cout << "------------------------------------" << endl;
        cout << "|        GPA & CGPA Calculator     |" << endl;
        cout << "------------------------------------" << endl << endl;
        cout << "1. Calculate GPA" << endl;
        cout << "2. Calculate CGPA" << endl;
        cout << "3. How to calculate GPA?" << endl;
        cout << "4. Quit" << endl << endl;
        cout << "Select option: ";
        option = getche();

        switch (option) {
            case '1':
                calculateGPA();
                break;
            case '2':
                calculateCGPA();
                break;
            case '3':
                showInstructions();
                break;
            case '4':
                exit(0);
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                pause();
                break;
        }

    } while (true);

    return 0;
}
