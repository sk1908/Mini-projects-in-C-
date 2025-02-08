#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

void showRules() {
    system("cls");
    cout << "\n\n";
    cout << "======================== GAME RULES ========================\n";
    cout << "1. Pick a number between 1 and 5.\n";
    cout << "2. Winning earns you 10 times your bet amount.\n";
    cout << "3. If you lose, you forfeit the bet amount.\n";
    cout << "============================================================\n";
    cout << "Press any key to continue...";
    getch();
}

void startGame() {
    system("cls");
    showRules();
    system("cls");

    string playerName;
    int balance, bet, guess, randomNumber;
    char choice;

    srand(static_cast<unsigned int>(time(0)));

    cout << "======================= CASINO GAME =======================\n\n";
    cout << "Enter your name: ";
    getline(cin, playerName);

    cout << "\n\nInitial deposit amount to start playing: $";
    cin >> balance;

    do {
        system("cls");
        cout << "======================= CASINO GAME =======================\n\n";
        cout << "Current Balance: $" << balance << "\n\n";

        do {
            cout << playerName << ", Enter bet amount: $";
            cin >> bet;
            if (bet > balance) {
                cout << "Insufficient balance. Please re-enter a valid bet amount.\n";
            }
        } while (bet > balance);

        do {
            cout << "Enter a number between 1 and 5: ";
            cin >> guess;
            if (guess < 1 || guess > 5) {
                cout << "Invalid number. Please pick a number between 1 and 5.\n";
            }
        } while (guess < 1 || guess > 5);

        randomNumber = rand() % 5 + 1;

        if (guess == randomNumber) {
            balance += bet * 10;
            cout << "\nCongratulations! You won $" << bet * 10 << "!\n";
        } else {
            balance -= bet;
            cout << "\nYou lost $" << bet << ". Better luck next time!\n";
        }

        cout << "The winning number was: " << randomNumber << "\n";
        cout << playerName << ", your remaining balance is: $" << balance << "\n";

        if (balance == 0) {
            cout << "You have run out of money. Game over.\n";
            break;
        }

        cout << "\nDo you want to play again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "============================================================\n";
    cout << "Thank you for playing! Your final balance is: $" << balance << "\n";
    cout << "============================================================\n";
    getch();
}

int main() {
    char menuChoice;

    do {
        system("cls");
        cout << "===================== CASINO NUMBER GUESS =====================\n";
        cout << "1. Start Game\n";
        cout << "2. View Rules\n";
        cout << "3. Exit\n";
        cout << "Select an option: ";
        menuChoice = getche();

        switch (menuChoice) {
            case '1':
                startGame();
                break;
            case '2':
                showRules();
                break;
            case '3':
                exit(0);
            default:
                cout << "\nInvalid option. Please try again.\n";
                break;
        }

    } while (true);

    return 0;
}
