#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define WIN_WIDTH 60

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

struct Alphabet {
    char character;
    int x, y;

    Alphabet(char ch, int startX, int startY) : character(ch), x(startX), y(startY) {}

    void draw() const {
        SetConsoleCursorPosition(console, {static_cast<short>(x), static_cast<short>(y)});
        cout << character;
    }

    void erase() const {
        SetConsoleCursorPosition(console, {static_cast<short>(x), static_cast<short>(y)});
        cout << ' ';
    }

    void updatePosition() {
        erase();
        y++;
        draw();
    }
};

void setCursorVisibility(bool visible, DWORD size) {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = visible;
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder() {
    // Top border
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, SCREEN_HEIGHT - 1);
        cout << '#';
    }

    // Side borders
    for (int i = 0; i < SCREEN_HEIGHT - 1; i++) {
        gotoxy(0, i);
        cout << '#';
        gotoxy(SCREEN_WIDTH - 1, i);
        cout << '#';
    }

    // Inner vertical border
    for (int i = 0; i < SCREEN_HEIGHT - 1; i++) {
        gotoxy(WIN_WIDTH, i);
        cout << '#';
    }
}

void displayScore(int score) {
    gotoxy(WIN_WIDTH + 5, 2);
    cout << "Score: " << score;
}

void displayInstructions() {
    system("cls");
    cout << "Typing Tutor Instructions\n";
    cout << "-------------------------\n";
    cout << "1. Catch the falling characters by typing them.\n";
    cout << "2. Characters fall from the top and you need to type them before they reach the bottom.\n";
    cout << "3. Score points for each correct character.\n";
    cout << "4. Press 'ESC' to quit the game.\n";
    cout << "\nPress any key to return to the menu.";
    _getch();
}

void gameOver(int score) {
    system("cls");
    cout << "Game Over!\n";
    cout << "Your Score: " << score << "\n";
    cout << "Press any key to return to the menu.";
    _getch();
}

void startGame() {
    vector<Alphabet> fallingLetters;
    int score = 0;

    system("cls");
    drawBorder();
    displayScore(score);

    // Initialize falling letters
    for (int i = 0; i < 10; i++) {
        char ch = 'A' + rand() % 26;
        int x = 2 + rand() % (WIN_WIDTH - 2);
        fallingLetters.emplace_back(ch, x, 1);
    }

    gotoxy(WIN_WIDTH + 5, 4);
    cout << "Typing Tutor";

    gotoxy(WIN_WIDTH + 5, 6);
    cout << "Press any key to start";
    _getch();

    while (true) {
        if (_kbhit()) {
            char input = _getch();
            for (auto& letter : fallingLetters) {
                if (input == letter.character || input == letter.character + 32) {
                    letter.erase();
                    letter.character = 'A' + rand() % 26;
                    letter.x = 2 + rand() % (WIN_WIDTH - 2);
                    letter.y = 1;
                    letter.draw();
                    score++;
                    displayScore(score);
                }
            }
            if (input == 27) { // ESC key
                break;
            }
        }

        for (auto& letter : fallingLetters) {
            letter.updatePosition();
        }

        Sleep(300);

        // Check for game over condition
        for (const auto& letter : fallingLetters) {
            if (letter.y >= SCREEN_HEIGHT - 1) {
                gameOver(score);
                return;
            }
        }
    }
}

int main() {
    setCursorVisibility(false, 0);
    srand(static_cast<unsigned>(time(nullptr)));

    char option;
    do {
        system("cls");
        gotoxy(10, 5);
        cout << "------------------------------";
        gotoxy(10, 6);
        cout << "|       TYPING TUTOR         |";
        gotoxy(10, 7);
        cout << "------------------------------";
        gotoxy(10, 9);
        cout << "1. Start Game";
        gotoxy(10, 10);
        cout << "2. Instructions";
        gotoxy(10, 11);
        cout << "3. Quit";
        gotoxy(10, 13);
        cout << "Select option (1-3): ";

        option = _getche();

        switch (option) {
            case '1':
                startGame();
                break;
            case '2':
                displayInstructions();
                break;
            case '3':
                cout << "\nExiting the game. Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid option. Please choose between 1 and 3." << endl;
                _getch();
                break;
        }
    } while (option != '3');

    return 0;
}
