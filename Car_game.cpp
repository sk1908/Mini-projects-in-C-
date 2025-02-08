#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

#define GAME_WIDTH 80
#define GAME_HEIGHT 24
#define ROAD_WIDTH 60

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPos;

int obstacleY[3];
int obstacleX[3];
int obstacleStatus[3];
char vehicle[4][4] = { ' ', '@', '@', ' ',
					   '@', '@', '@', '@',
					   ' ', '@', '@', ' ',
					   '@', '@', '@', '@' };

int vehiclePosition = ROAD_WIDTH / 2;
int playerScore = 0;
bool isPaused = false;

void setCursorPos(int x, int y) {
	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleCursorPosition(console, cursorPos);
}

void setCursorVisibility(bool visible, DWORD size) {
	if (size == 0) size = 20;

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = visible;
	cursorInfo.dwSize = size;
	SetConsoleCursorInfo(console, &cursorInfo);
}

void drawBoundary() {
	for (int i = 0; i < GAME_HEIGHT; i++) {
		for (int j = 0; j < 15; j++) {
			setCursorPos(0 + j, i); cout << "|";
			setCursorPos(ROAD_WIDTH - j, i); cout << "|";
		}
	}
	for (int i = 0; i < GAME_HEIGHT; i++) {
		setCursorPos(GAME_WIDTH, i); cout << "|";
	}
}

void spawnObstacle(int index) {
	obstacleX[index] = 15 + rand() % (ROAD_WIDTH - 20);
	obstacleStatus[index] = 1;
	obstacleY[index] = 1;
}

void drawObstacle(int index) {
	if (obstacleStatus[index] == 1) {
		setCursorPos(obstacleX[index], obstacleY[index]); cout << "####";
		setCursorPos(obstacleX[index], obstacleY[index] + 1); cout << " ## ";
		setCursorPos(obstacleX[index], obstacleY[index] + 2); cout << "####";
		setCursorPos(obstacleX[index], obstacleY[index] + 3); cout << " ## ";
	}
}

void clearObstacle(int index) {
	if (obstacleStatus[index] == 1) {
		setCursorPos(obstacleX[index], obstacleY[index]); cout << "    ";
		setCursorPos(obstacleX[index], obstacleY[index] + 1); cout << "    ";
		setCursorPos(obstacleX[index], obstacleY[index] + 2); cout << "    ";
		setCursorPos(obstacleX[index], obstacleY[index] + 3); cout << "    ";
	}
}

void resetObstacle(int index) {
	clearObstacle(index);
	spawnObstacle(index);
}

void drawVehicle() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			setCursorPos(j + vehiclePosition, i + 20); cout << vehicle[i][j];
		}
	}
}

void clearVehicle() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			setCursorPos(j + vehiclePosition, i + 20); cout << " ";
		}
	}
}

int checkCollision() {
	for (int i = 0; i < 3; i++) {
		if (obstacleY[i] + 4 >= 20) {
			if (obstacleX[i] + 4 - vehiclePosition >= 0 && obstacleX[i] + 4 - vehiclePosition < 8) {
				return 1;
			}
		}
	}
	return 0;
}

void displayGameOver() {
	system("cls");
	cout << endl;
	cout << "\t\t-------------------------" << endl;
	cout << "\t\t----- Game Over !! ------" << endl;
	cout << "\t\t-------------------------" << endl << endl;
	cout << "\t\tPress any key to return to the menu.";
	getch();
}

void updateScoreDisplay() {
	setCursorPos(ROAD_WIDTH + 5, 5); cout << "Score: " << playerScore << endl;
}

void displayInstructions() {
	system("cls");
	cout << "Instructions" << endl;
	cout << "----------------" << endl;
	cout << " Avoid the obstacles by moving left or right." << endl;
	cout << " Use 'A' to move left, 'D' to move right, and 'P' to pause the game." << endl;
	cout << " Press 'Esc' to exit the game." << endl;
	cout << "Press any key to return to the menu.";
	getch();
}

void playGame() {
	vehiclePosition = -1 + ROAD_WIDTH / 2;
	playerScore = 0;
	obstacleStatus[0] = 1;
	obstacleStatus[1] = 0;
	obstacleStatus[2] = 0;

	system("cls");
	drawBoundary();
	updateScoreDisplay();
	spawnObstacle(0);
	spawnObstacle(1);

	setCursorPos(ROAD_WIDTH + 5, 2); cout << "Car Racing Game";
	setCursorPos(ROAD_WIDTH + 4, 4); cout << "----------------";
	setCursorPos(ROAD_WIDTH + 4, 6); cout << "----------------";
	setCursorPos(ROAD_WIDTH + 5, 10); cout << "Controls";
	setCursorPos(ROAD_WIDTH + 4, 12); cout << "A - Left";
	setCursorPos(ROAD_WIDTH + 4, 14); cout << "D - Right";
	setCursorPos(ROAD_WIDTH + 4, 16); cout << "P - Pause";
	setCursorPos(ROAD_WIDTH + 4, 18); cout << "Esc - Exit";

	setCursorPos(15, 5); cout << "Press any key to start";
	getch();
	setCursorPos(15, 5); cout << "                     ";

	while (1) {
		if (kbhit()) {
			char ch = getch();
			if (ch == 'a' || ch == 'A') {
				if (vehiclePosition > 15) vehiclePosition -= 4;
			}
			if (ch == 'd' || ch == 'D') {
				if (vehiclePosition < 50) vehiclePosition += 4;
			}
			if (ch == 'p' || ch == 'P') {
				isPaused = !isPaused;
				while (isPaused) {
					if (kbhit()) {
						char pauseKey = getch();
						if (pauseKey == 'p' || pauseKey == 'P') {
							isPaused = false;
						}
					}
				}
			}
			if (ch == 27) {
				break;
			}
		}

		if (!isPaused) {
			drawVehicle();
			for (int i = 0; i < 2; i++) {
				drawObstacle(i);
			}
			if (checkCollision() == 1) {
				displayGameOver();
				return;
			}
			Sleep(50);
			clearVehicle();
			for (int i = 0; i < 2; i++) {
				clearObstacle(i);
			}

			for (int i = 0; i < 2; i++) {
				if (obstacleStatus[i] == 1) {
					obstacleY[i] += 1;
				}
			}

			if (obstacleY[0] == 10 && obstacleStatus[1] == 0) {
				obstacleStatus[1] = 1;
			}

			if (obstacleY[0] > GAME_HEIGHT - 4) {
				resetObstacle(0);
				playerScore++;
				updateScoreDisplay();
			}
			if (obstacleY[1] > GAME_HEIGHT - 4) {
				resetObstacle(1);
				playerScore++;
				updateScoreDisplay();
			}
		}
	}
}

int main() {
	setCursorVisibility(0, 0);
	srand((unsigned)time(NULL));

	do {
		system("cls");
		setCursorPos(10, 5); cout << " ----------------------------- ";
		setCursorPos(10, 6); cout << " |        Car Racing Game    | ";
		setCursorPos(10, 7); cout << " -----------------------------";
		setCursorPos(10, 9); cout << "1. Start Game";
		setCursorPos(10, 10); cout << "2. Instructions";
		setCursorPos(10, 11); cout << "3. Exit";
		setCursorPos(10, 13); cout << "Select an option: ";
		char option = getche();

		if (option == '1') playGame();
		else if (option == '2') displayInstructions();
		else if (option == '3') exit(0);

	} while (1);

	return 0;
}
