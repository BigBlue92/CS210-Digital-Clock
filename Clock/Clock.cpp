/*CS-210-T6594 Programming Languages 20EW6
 * Project One: Chada tech clock
 * Clock.cpp
 * v1.1: Removed code from main and created timecalc to clean code
 * v1.2: Added elapsed seconds counter for the menu that can track how
 * long the user takes to make a choice, and also adds that to the time.
 * v1.3: Created the current time function, now is a fully functional clock
 * but does not update until the user makes a selection. This is acceptable
 * per the instructors comments in our general discussion on Brightspace.
 * Created on: Jul 13, 2020
 * Author: Ryan Mackenzie
 */

#include <iostream>
#include <chrono>
#include <windows.h>
#include <string>//used to convert integers to strings
#include <ctime>
using namespace std;

void currentTime(int& hours, int& minutes, int& seconds){
	const time_t now = time(nullptr) ; // get the current time point
	const tm calendar_time = *localtime(addressof(now));
	hours = calendar_time.tm_hour;
	minutes = calendar_time.tm_min;
	seconds = calendar_time.tm_sec;
}

//Creates the 12 hour clock, takes integers and converts them into strings.
//Combines the strings into a properly formatted clock and returns the string.
string clock12(int hours, int minutes, int seconds) {
	boolean amPm = false; //stores value for AM or PM
	string secondsFormatted;
	string minutesFormatted;
	string hoursFormatted;
	string printAmPm = "P M";

	//Calculates and formats seconds
	if (seconds < 10) {
		secondsFormatted = "0" + to_string(seconds);
	} else {
		secondsFormatted = to_string(seconds);
	}

	//Calculates and formats minutes
	if (minutes < 10) {
		minutesFormatted = "0" + to_string(minutes);
	} else {
		minutesFormatted = to_string(minutes);
	}

	//Calculates and formats hours, checks to see if AM needs to be true.
	if (hours < 12) {
		amPm = true;
		if (hours < 1) {
			hours = 12;
		}
	} else if (hours >= 13) {
			hours = hours % 12;
	}

	if (hours < 10) {
		hoursFormatted = "0" + to_string(hours);
	} else {
		hoursFormatted = to_string(hours);
	}

	if (amPm) {
		printAmPm = "A M";
	}
	//builds the final output time
	string time12 = hoursFormatted + ":" + minutesFormatted + ":"
			+ secondsFormatted + " " + printAmPm;
	return time12;
}

//Creates the 24 hour clock, takes integers and converts them into strings.
//Combines the strings into a properly formatted clock and returns the string.
string clock24(int hours, int minutes, int seconds) {
	string secondsFormatted;
	string minutesFormatted;
	string hoursFormatted;

	//formats seconds
	if (seconds < 10) {
		secondsFormatted = "0" + to_string(seconds);
	} else {
		secondsFormatted = to_string(seconds);
	}

	//formats minutes
	if (minutes < 10) {
		minutesFormatted = "0" +  to_string(minutes);
	} else {
		minutesFormatted = to_string(minutes);
	}

	//formats hours
	if (hours < 10) {
			hoursFormatted = "0" + to_string(hours);
	} else {
			hoursFormatted = to_string(hours);
	}
	//The final output string that's printed to the console built below.
	string time24 = hoursFormatted + ":" + minutesFormatted + ":" + secondsFormatted;
	return time24;
}

//This function makes sure the clock turns over properly at the right times.
//In: The GUI user input, and the current stored values for hours, minutes, and
//    and seconds which could be greater than 60 or 23.
//Out: Corrects and values that are too high and allocates those to add minutes
//     or hours where necessary. Resets values to where they should be with mod
//     statements.
void timeCalc(int userInput, int& seconds, int& minutes, int& hours) {
	if (userInput == 1) {
		hours += 1;
	} else if (userInput == 2) {
		minutes += 1;
	} else if (userInput == 3) {
		seconds += 1;
	}

	if (seconds > 59) {
		minutes += seconds / 60;
		seconds = seconds % 60;
	}
	if (minutes > 59) {
		hours += minutes / 60;
		minutes = minutes % 60;
	}
	if (hours > 23) {
		hours = hours % 24;
	}
}

int main() {
	int userInput;
	int seconds = 0;   // tracks seconds 0 - 59
	int minutes = 0;   //tracks minutes 0 - 59
	int hours = 0;     // tracks hours 0 - 23
	currentTime(hours, minutes, seconds);//gets and stores current time.

	//GUI formatted to look exactly like the spec document.
	while (userInput != 4) {
		cout << "*****************************    *****************************"
			 << endl;
		cout << "*       12-Hour Clock       *    *       24-Hour Clock       *"
			 << endl;
		cout << "*       " << clock12(hours, minutes, seconds); //formats the 12 hour clock
		cout << "        *    *          " << clock24(hours, minutes, seconds)
			 << "         *" << endl;//formats the 24 hour clock
		cout << "*****************************    *****************************"
			 << endl;
		cout << "                 ****************************" << endl;
		cout << "                 * 1 - Add One Hour         *" << endl;
		cout << "                 * 2 - Add One Minute       *" << endl;
		cout << "                 * 3 - Add One Second       *" << endl;
		cout << "                 * 4 - Exit Program         *" << endl;
		cout << "                 ****************************" << endl;

		//Counts seconds while user is in the menu and adds them to the time.
		auto start = chrono::system_clock::now();
		cin >> userInput;//Blocking statement waits for user input.
		auto end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end-start;
		seconds += elapsed_seconds.count();

		//Keeps track of time for both clocks unless the user quits
		if (userInput != 4) {
			timeCalc(userInput, seconds, minutes, hours);
		}
	}
	return 0;
}


