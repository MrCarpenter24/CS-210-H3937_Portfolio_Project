/* PhillipsClockApp.cpp
 * VERSION 3.0
 *
 * This program consists of Project One Material,
 * a clock capable of taking input and providing accurate
 * output such as displaying the present time.
 *
 *  Created on: Jan 29, 2021
 *   Last Edit: February 17, 2021
 *      Author: Johnathan Phillips
 * -------------------------------------------------------
 * To properly display the time in both 12hr and 24hr
 * formats, on 1/24/2021, code was used from this link:
 *
 * https://www.codespeedy.com/digital-clock-in-cpp/
 * 		borrowed code by Ranjeet V
 * -------------------------------------------------------
 *
 */
#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
using namespace std;

//Global variables
int seconds, minutes, hours;
string str; //Stores "AM" or "PM"
time_t prev_seconds;  //Stores time that has passed since clock was last displayed
time_t added_seconds = 0; //Stores total added seconds
time_t total_seconds = time(0); //Stores current seconds

void displayMenu(){ //Displays formatted text menu
	cout << "*************************" << endl;
	cout << "*" << setw(23) << left << "1 - Add One Hour" << "*" << endl;
	cout << "*" << setw(23) << left << "2 - Add One Minute" << "*" << endl;
	cout << "*" << setw(23) << left << "3 - Add One Second" << "*" << endl;
	cout << "*                       *" << endl;
	cout << "*" << setw(23) << left << "4 - Remove One Hour" << "*" << endl;
	cout << "*" << setw(23) << left << "5 - Remove One Minute" << "*" << endl;
	cout << "*" << setw(23) << left << "6 - Remove One Second" << "*" << endl;
	cout << "*                       *" << endl;
	cout << "*" << setw(23) << left << "7 - Exit Program" << "*" << endl;
	cout << "*************************" << endl;

	cout << "Enter selection: ";
}
void displayClock(){ //Pulls time from system**
	//********The following code is borrowed, mostly verbatim, for the clock, from this site:
	//  https://www.codespeedy.com/digital-clock-in-cpp/

	//getting values of seconds, minutes, and hours
	struct tm* ct = localtime(&total_seconds);

	prev_seconds = time(0)-total_seconds;

	total_seconds = total_seconds + prev_seconds + added_seconds;

	seconds = ct -> tm_sec;
	minutes = ct -> tm_min;
	hours = ct -> tm_hour;

	//Added to original code to store 24hr data
	int hours24 = hours;

	//converting it into 12 hour format
	if(hours >= 12)
	str = "PM";
	else
	str = "AM";
	hours = hours>12?hours-12:hours;

	//Print clock version
	cout << endl << "VERSION 3.0 -------------------- modified Feb 17, 2021" << endl;

	//Printing formatted result
	cout << "*************************" << "    " << "*************************" << endl;
	cout << "*     12-Hour Clock     *" << "    " << "*     24-Hour Clock     *" << endl;
	//Standard 12hr
	cout << "*      " << (hours<10?"0":"") << hours << ":" << (minutes<10?"0":"") << minutes << ":" << (seconds<10?"0":"") << seconds << " " << str;
	cout << "      *" << "    " << "*       ";
	//Military 24hr
	cout << (hours24<10?"0":"") << hours24 << ":" << (minutes<10?"0":"") << minutes << ":" << (seconds<10?"0":"") << seconds;
	cout << "        *" << endl;
	cout << "*************************" << "    " << "*************************" << endl;

	//Explain to user how to access the menu
	cout << "Press escape for menu." << endl;

}

void addHour(){  //Function for adding an hour to the clock
	added_seconds  += 3600;
}

void addMinute(){ //Function for adding a minute to the clock
	added_seconds += 60;
}

void addSecond(){  //Function for adding a minute to the clock
	added_seconds += 1;
}

void subHour(){  //Function for adding an hour to the clock
	added_seconds  -= 3600;
}

void subMinute(){ //Function for adding a minute to the clock
	added_seconds -= 60;
}

void subSecond(){  //Function for adding a minute to the clock
	added_seconds -= 1;
}

//--------------------MAIN EXECUTION--------------------//

int main(){
	char menuValue = 0; //Used in menu driven while loop
	bool pullMenu = false;  //Used to control clock refresh

	while(menuValue != '7'){
		while(pullMenu == false){
			system("CLS"); //Clears previous clock (Only works when ran in CMD)
			displayClock();
			Sleep(1000);   //Saves resources, only refreshes clock once per second.
			//Checks to see if escape key has been pressed
			if (GetAsyncKeyState(VK_ESCAPE)){
				pullMenu = true;
			}
		}

		cout << endl;

		displayMenu();
		cin >> menuValue;

		switch(menuValue){
			case '1':
				addHour();
				break;
			case '2':
				addMinute();
				break;
			case '3':
				addSecond();
				break;
			case '4':
				subHour();
				break;
			case '5':
				subMinute();
				break;
			case '6':
				subSecond();
				break;
			case '7':
				system("CLS");
				cout << endl << "Until next time! :)" << endl;
				Sleep(2000);
				break;
			default:
				cout << "Input error. Try using 1 through 7 as input." << endl;
				Sleep(3000);
				break;
				}
		pullMenu = false;
	}

	return 0;
}
