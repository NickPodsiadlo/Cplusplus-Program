/*
 * Nicholas Podsiadlo
 * Project 1: Chada Tech Clock
 * SNHU CS 210
 * 5/16/2021
 * Desc: Displays a clock in both 12 hour and 24 hour format
 * The user is able to set the time and make adjustments using the menu as needed
 */

#include <iostream>
#include <iomanip>
#include <thread>
#include <windows.h>

using namespace std;

//function declarations
void setCurrentTime(int& hours, int& minutes, int& seconds);
void display12Hour(int hours = 0, int minutes = 0, int seconds = 0);
void display24Hour(int hours = 0, int minutes = 0, int seconds = 0);
int displayMenu();
void determineIncrement(int& hours, int& minutes, int& seconds);
bool processMenuCommand(int menuChoice, int& hours, int& minutes, int& seconds);

// beginning of main function
int main() {
    // define variables that will be used in main
    int hours;
    int minutes;
    int seconds;
    int menuChoice;
    bool quitProgram = false;

    //display instructions to the user
    cout << "Press the Left-Shift key at any time to pause the clock and make a menu selection." << endl;
    cout << "Please set the time for your new clock."<< endl;
    setCurrentTime(hours, minutes, seconds);

    // main loop that updates the clock and checks if the menu needs to be opened
    while (!quitProgram) {
        //clear the previous output (if any)
        cout << string( 100, '\n' );

        //display the 2 formatted times
        display12Hour(hours, minutes, seconds);
        cout << endl << endl;
        display24Hour(hours, minutes, seconds);

        // add 1 second and wait for 1 second
        seconds += 1;
        std::this_thread::sleep_for(1s);

        // check if 60 seconds, 60 minutes, or 24 hours has been reached
        determineIncrement(hours, minutes, seconds);

        // check if the user has pressed the Left-Shift key in order to determine if menu should be shown
        if(GetAsyncKeyState(VK_LSHIFT)) {
            cout << string(100, '\n'); //clear previous output before displaying menu
            menuChoice = displayMenu();
        }

        quitProgram = processMenuCommand(menuChoice, hours, minutes, seconds);
        menuChoice = 0;  // reset menuChoice after the command has been processed
    }
    // end of main, return 0
    return 0;
}

// function definitions

// function that allows the user to set the time by inputting hours, minutes, and seconds
// checks to make sure the values entered form a valid time
void setCurrentTime(int& hours, int& minutes, int& seconds) {
    bool valid = false; //declare bool to check for valid input

    while (!valid) {
        cout << "Enter current hour (0-23):" << endl;
        cin >> hours;
        cout << "Enter current minute (0-59):" << endl;
        cin >> minutes;
        cout << "Enter current second (0-59):" << endl;
        cin >> seconds;

        // check that the input is within range
        if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59) {
            valid = true;
        }
        else {
            cout << "Your input was not within the valid ranges, try again." << endl;
        }
    }
}

// displays the clock using 12 hour format
void display12Hour(int hours, int minutes, int seconds) {
    string am_pm = "AM"; // define a variable to hold the string for AM or PM

    // check if hours needs to be converted to 12 hour format
    if (hours >= 12) {
        am_pm = "PM";
        // subtract by 12 if hours is not 12
        if (hours != 12) {
            hours -= 12;
        }
    }

    // check if it is midnight (12 AM)
    if (hours == 0) {
        hours = 12;
    }

    // output the formatted clock title
    cout << "*************************" << endl;
    cout << "*" << setw(18) << right << "12-Hour Clock";
    cout << setw(6) << right << "*" << endl;
    // output the formatted time string
    cout << "*" << setw(6) << " ";
    cout << setw(2) << setfill('0');
    cout << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds << " " << am_pm;
    cout << setfill(' ') << setw(7) << right << "*" << endl;
    cout << "*************************" << endl;
}

// displays the clock using 24 hours format
void display24Hour(int hours, int minutes, int seconds) {
    // output the formatted clock title
    cout << "*************************" << endl;
    cout << "*" << setw(18) << right << "24-Hour Clock";
    cout << setw(6) << right << "*" << endl;
    // output the formatted time string
    cout << "*" << setw(7) << " ";
    cout << setw(2) << setfill('0');
    cout << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds << " ";
    cout << setfill(' ') << setw(8) << right << "*" << endl;
    cout << "*************************" << endl;
}

// displays the menu, checks for valid menu entries
int displayMenu() {
    int menuChoice; //define a variable to hold the menu choice
    bool valid = false;  //bool variable to determine if input is valid

    while (!valid) {
        // output the formatted menu
        cout << "*************************" << endl;
        cout << setw(24) << left << "* 1 - Add One Hour" << "*" << endl;
        cout << setw(24) << left << "* 2 - Add One Minute" << "*" << endl;
        cout << setw(24) << left << "* 3 - Add One Second" << "*" << endl;
        cout << setw(24) << left << "* 4 - Set Current Time" << "*" << endl;
        cout << setw(24) << left << "* 5 - Exit Program" << "*" << endl;
        cout << "*************************" << endl;

        // get the menuChoice from the user and return its value
        cin >> menuChoice;
        // check if the menuChoice is valid
        if (menuChoice >= 1 && menuChoice <= 5) {
            valid = true;
        }
        else {
            cout << "That was not a valid entry, please try again." << endl;
        }
    }
    return menuChoice;
}

// function that is called to determine if hours, minutes, or seconds needs to be incremented
void determineIncrement(int& hours, int& minutes, int& seconds) {
    // determine if seconds needs to be incremented
    if (seconds == 60) {
        seconds = 0;
        minutes += 1;
    }
    // determine if minutes needs to be incremented
    if (minutes == 60) {
        minutes = 0;
        hours += 1;
    }
    // reset hours to 0 when reaching 24
    if (hours == 24)
        hours = 0;
}

// process the users entry on the menu screen using a switch statement
bool processMenuCommand(int menuChoice, int& hours, int& minutes, int& seconds) {
    bool quitProgram = false;
    switch (menuChoice) {
        case 1:
            hours += 1;
            break;
        case 2:
            minutes += 1;
            break;
        case 3:
            seconds += 1;
            break;
        case 4:
            setCurrentTime(hours, minutes, seconds);
            break;
        case 5:
            quitProgram = true;
            cout << "Goodbye!" << endl;
            std::this_thread::sleep_for(3s);;
            break;
    }
    // return quitProgram bool value
    return quitProgram;
}
