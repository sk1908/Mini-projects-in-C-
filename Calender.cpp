#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>

using namespace std;

void generateCalendar(int selectedYear) {
	int monthOffsets[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	string monthNames[] = { "January", "February", "March", "April", "May", "June",
	                      "July", "August", "September", "October", "November", "December" };

	cout << "  --------------------------------" << endl;
	cout << "          Yearly Calendar - " << selectedYear << endl;
	cout << "  --------------------------------" << endl << endl;

	int totalDays;
	int startDay;

	// Determine the first day of the year
	int y = selectedYear - 1;
	startDay = (y + y / 4 - y / 100 + y / 400 + monthOffsets[0] + 1) % 7;

	for (int month = 0; month < 12; month++) {
		if (month == 1) { // February, adjust for leap year
			if (selectedYear % 400 == 0 || (selectedYear % 4 == 0 && selectedYear % 100 != 0))
				totalDays = 29;
			else
				totalDays = daysInMonth[month];
		} else {
			totalDays = daysInMonth[month];
		}

		cout << endl << "  ------------ " << monthNames[month] << " -------------" << endl;
		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;

		int weekDay;
		for (weekDay = 0; weekDay < startDay; weekDay++)
			cout << "     "; // Add leading spaces

		for (int day = 1; day <= totalDays; day++) {
			weekDay++;
			cout << setw(5) << day;
			if (weekDay > 6) {
				weekDay = 0;
				cout << endl;
			}
		}

		if (weekDay) 
			cout << endl;

		startDay = weekDay; // Update startDay for the next month
	}

	return;
}

int main() {
	system("cls");

	time_t currentTime = time(0);
	tm *currentDate = localtime(&currentTime);

	int displayYear = 1900 + currentDate->tm_year;
	char userInput;

	do {
		system("cls");
		generateCalendar(displayYear);

		cout << endl << endl;
		cout << "Options: " << endl;
		cout << "- Press 'n' for next year" << endl;
		cout << "- Press 'p' for previous year" << endl;
		cout << "- Press 'q' to quit" << endl;
		userInput = getche();

		switch (userInput) {
			case 'n':
				displayYear++;
				break;
			case 'p':
				displayYear--;
				break;
		}

	} while (userInput != 'q' && userInput != 'Q');

	return 0;
}
