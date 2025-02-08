#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <limits> // Include for numeric_limits

using namespace std;

// Function Declarations
void play();
void instructions();
void displayHeader(const string& header);
int getValidInteger(const string& prompt, int minValue, int maxValue);
double getValidDouble(const string& prompt);

// Main Function
int main() {
    // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    char option;

    do {
        system("cls");
        displayHeader("MATHS GAME");
        cout << "1. Play" << endl;
        cout << "2. Instructions" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose Option (1-3): ";
        option = getche();

        switch (option) {
            case '1':
                play();
                break;
            case '2':
                instructions();
                break;
            case '3':
                cout << "\nExiting the game. Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid option. Please choose between 1 and 3." << endl;
                _getch(); // Pause for user to read message
                break;
        }
    } while (option != '3');

    return 0;
}

// Function to display header
void displayHeader(const string& header) {
    cout << "-----------------------------------" << endl;
    cout << "           " << header << "            " << endl;
    cout << "-----------------------------------" << endl << endl;
}

// Function to get valid integer input
int getValidInteger(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minValue || value > maxValue) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between " << minValue << " and " << maxValue << "." << endl;
        } else {
            break;
        }
    }
    return value;
}

// Function to get valid double input
double getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a numeric value." << endl;
        } else {
            break;
        }
    }
    return value;
}

// Function to handle gameplay
void play() {
    system("cls");
    displayHeader("MATHS GAME");

    int limit = 10;
    cout << "Select Difficulty Level:" << endl;
    cout << "1. Level 1 (Range 0-10)" << endl;
    cout << "2. Level 2 (Range 0-20)" << endl;
    cout << "3. Level 3 (Range 0-100)" << endl;
    cout << "4. Back to Menu" << endl;

    char option = getche();

    switch (option) {
        case '1': limit = 10; break;
        case '2': limit = 20; break;
        case '3': limit = 100; break;
        case '4': return;
        default:
            cout << "\nInvalid selection. Returning to menu." << endl;
            _getch(); // Pause for user to read message
            return;
    }
	cout << "\n";
    float q1, q2, ans, correctAns;
    int correctNo = 0, totalNo = 5;
    char operation;

    for (int i = 0; i < totalNo; ++i) {
        q1 = rand() % limit;
        q2 = rand() % limit;

        int tmpOp = rand() % 3;
        switch (tmpOp) {
            case 0: operation = '+'; break;
            case 1: operation = '-'; break;
            case 2: operation = '*'; break;
        }

        cout << "Question:(" << (i + 1) << "): ";
        cout << q1 << " " << operation << " " << q2 << " = ";
        ans = getValidDouble("");

        switch (operation) {
            case '+': correctAns = q1 + q2; break;
            case '-': correctAns = q1 - q2; break;
            case '*': correctAns = q1 * q2; break;
        }

        if (correctAns == ans) {
            correctNo++;
            cout << "Correct!" << endl << endl;
        } else {
            cout << "Wrong! The correct answer was " << correctAns << endl << endl;
        }
    }

    cout << "Total Questions: " << totalNo << endl;
    cout << "Correct Answers: " << correctNo << endl;
    cout << "Score: " << static_cast<float>(correctNo) / totalNo * 100 << "%" << endl;

    cout << "\nPress any key to continue..." << endl;
    _getch(); // Wait for user to press a key
}

// Function to display instructions
void instructions() {
    system("cls");
    displayHeader("Instructions");

    cout << "1. This game contains basic arithmetic problems." << endl;
    cout << "2. Each correct answer earns you 1 point." << endl;
    cout << "3. There are 5 questions in each game." << endl;
    cout << "4. To win, you need to get at least 3 correct answers." << endl;

    cout << "\nPress any key to continue..." << endl;
    _getch(); // Wait for user to press a key
}
