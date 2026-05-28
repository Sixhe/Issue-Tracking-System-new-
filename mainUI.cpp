/*
 * mainUI.cpp
 *
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Updated to include functions for displaying Engineer menu and related actions
 * - 2024-07-28: add requestUserContinue() function
 *
 * Description:
 * This file contains the implementations for functions that handle the user interface (UI) for the
 * Issue Tracking System (ITS) application. It includes functions for displaying menus and
 * getting user input.
 */

#include "mainUI.h"

using namespace std;

void displayMainMenuUI() {
    cout << "Issue Tracking System - Main Menu" << endl;
    cout << "   1) Customer" << endl;
    cout << "   2) Employee" << endl;
    cout << "   3) Engineer" << endl;
    cout << "   4) Exit" << endl;
    cout << "CHOOSE AN OPTION FROM [ 1 - 4 ] AND PRESS 'ENTER': ";
}

void displayCustomerMenuUI() {
    cout << "Issue Tracking System - Customer Menu" << endl;
    cout << "   1) Create customer request" << endl;
    cout << "   2) Display request by change id" << endl;
    cout << "   3) Go back to main menu" << endl;
    cout << "CHOOSE AN OPTION FROM [ 1 - 3 ] AND PRESS 'ENTER': ";
}

void displayEmployeeMenuUI() {
    cout << "Issue Tracking System - Employee Menu" << endl;
    cout << "   1) Create employee request" << endl;
    cout << "   2) Display request by change id" << endl;
    cout << "   3) Go back to main menu" << endl;
    cout << "CHOOSE AN OPTION FROM [ 1 - 3 ] AND PRESS 'ENTER': ";
}

void displayEngineerMenuUI() {
    cout << "Issue Tracking System - Engineer Menu" << endl;
    cout << "   1) Update Change Item" << endl;
    cout << "   2) Create Product Release" << endl;
    cout << "   3) Create Product" << endl;
    cout << "   4) Generate All Not Done Change Items Report-#1" << endl;
    cout << "   5) Generate Completed Change Items Report-#2" << endl;
    cout << "   6) Go back to main menu" << endl;
    cout << "CHOOSE AN OPTION FROM [ 1 - 6 ] AND PRESS 'ENTER': ";
}

void exitProgram() {
    cout << "System terminated." << endl;
    cout << "Thank you for using ITS Tracker." << endl;
    system("pause");
    exit(0);
}

int getSelection(int min, int max) {
    int selection;
    selection = enterCorrectIntValue();
    while (selection < min || selection > max) {
        cout << "Invalid selection. Please choose an option from " << min << " to " << max << ": ";
        selection = enterCorrectIntValue();
    }
    return selection;
}

void requestUserContinue() {
    cout << "Press ENTER to continue... ";
    cin.sync();
    cin.get();  
}


