/* 
 * main.cpp
 * 
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Added functions to delete a product and delete a product release
 * - 2024-07-02: Fixed function capital error and fixed function call error
 * - 2024-07-03: Add comment to each function
 * - 2024-07-16: Fix the bug that clear screen function failed
 * - 2024-07-22: add title
 * - 2024-07-25: change clear screen code
 * - 2024-07-28: add press to continue when function end
 * 
 * Description:
 * This file serves as the main entry point for the Issue Tracking System (ITS) application.
 * It handles the main menu navigation and calls the appropriate functions based on user input.
 * The application allows users to manage customer requests, employee tasks, and engineer tasks.
 */

#include <iostream>
#include <cstdlib> // for system("clear") to clear the screen

#include "Customer.h"
#include "Employee.h"
#include "Engineer.h"
#include "mainUI.h"
#include "FileHandler.h"

using namespace std;

//---------------------------------------------------------------------
// Function to clear the console screen.
// This function uses system("clear") to clear the screen.
//---------------------------------------------------------------------
void clearScreen();

//---------------------------------------------------------------------
// Function to handle the customer menu operations.
// This function displays the customer menu and handles user input for:
// 1) Creating a new customer request
// 2) Adding an existing customer request
// 3) Going back to the main menu
// The function repeatedly displays the menu until the user chooses to go back to the main menu.
//---------------------------------------------------------------------
void handleCustomerMenu();

//---------------------------------------------------------------------
// Function to handle the employee menu operations.
// This function displays the employee menu and handles user input for:
// 1) Adding a bug request
// 2) Adding a feature request
// 3) Going back to the main menu
// The function repeatedly displays the menu until the user chooses to go back to the main menu.
//---------------------------------------------------------------------
void handleEmployeeMenu();

//---------------------------------------------------------------------
// Function to handle the engineer menu operations.
// This function displays the engineer menu and handles user input for:
// 1) Updating a change item
// 2) Creating a product release
// 3) Creating a product
// 4) Generating report 1 (All Not Done Change Items Report)
// 5) Generating report 2 (Completed Change Items Report)
// 6) Going back to the main menu
// The function repeatedly displays the menu until the user chooses to go back to the main menu.
//---------------------------------------------------------------------
void handleEngineerMenu();

//---------------------------------------------------------------------
// Function to display the main menu and handle user navigation.
// This function displays the main menu and handles user input for navigating to:
// 1) The customer menu
// 2) The employee menu
// 3) The engineer menu
// 4) Exiting the program
// The function repeatedly displays the main menu until the user chooses to exit the program.
//---------------------------------------------------------------------
void displayMainMenu();

//---------------------------------------------------------------------
// Function to go back to the main menu.
// This function is called to return to the main menu from any sub-menu.
//---------------------------------------------------------------------
void goBackMainMenu();

//---------------------------------------------------------------------
// This is the most important main function
//---------------------------------------------------------------------
int main() {
    system("title Issue Tracking System");
    displayMainMenu();
    return 0;
}

//---------------------------------------------------------------------
// Function: displayMainMenu
// Description: Displays the main menu and handles user navigation.
// Implementation: This function displays the main menu and handles user input for navigating to:
//                 1) Customer" 
//                 2) Employee" 
//                 3) Engineer" 
//                 4) Exit" 
//The function repeatedly displays the main menu until the user chooses to exit the program.
//---------------------------------------------------------------------
void displayMainMenu() {
    int selection;
    do {
        clearScreen();
        displayMainMenuUI();
        selection = getSelection(1, 4);
        switch (selection) {
            case 1:
                handleCustomerMenu();
                break;
            case 2:
                handleEmployeeMenu();
                break;
            case 3:
                handleEngineerMenu();
                break;
            case 4:
                exitProgram();
                break;
            default:
                clearScreen();
                cout << "Invalid selection. Please choose an option from 1 to 4." << endl;
        }
    } while (selection != 4);
}

//---------------------------------------------------------------------
//Uses the system command to clear the screen. On Unix-based systems, it uses "clear".
//---------------------------------------------------------------------
void clearScreen() {
    // On Windows
    system("CLS");
}

//---------------------------------------------------------------------
// Function: handleCustomerMenu
// Description: Handles the customer menu operations.
// Implementation: This function displays the customer menu and handles user input for:
//                 1) Create customer request
//                 2) Display request by change id
//                 3) Go back to main menu
//The function repeatedly displays the menu until the user chooses to go back to the main menu.
//---------------------------------------------------------------------
void handleCustomerMenu() {
    int selection;
    do {
        clearScreen();
        displayCustomerMenuUI();
        selection = getSelection(1, 3);
        if (selection == 1) {
            clearScreen();
            addCustomerRequest();
            requestUserContinue();
        } else if (selection == 2) {
            clearScreen();
            displayCustomerRequestByChangeId();
            requestUserContinue();
        } else if (selection == 3) {
            goBackMainMenu();
            break;
        } else {
            clearScreen();
            cout << "Invalid selection. Returning to customer menu." << endl;
        }
    } while (selection != 3);
}

//---------------------------------------------------------------------
// Function: handleEmployeeMenu
// Description: Handles the employee menu operations.
// Implementation: This function displays the employee menu and handles user input for:
//                 1) Create employee request
//                 2) Display request by change id
//                 3) Go back to main menu
//The function repeatedly displays the menu until the user chooses to go back to the main menu.
//---------------------------------------------------------------------
void handleEmployeeMenu() {
    int selection;
    do {
        clearScreen();
        displayEmployeeMenuUI();
        selection = getSelection(1, 3);
        if (selection == 1) {
            clearScreen();
            addEmployeeRequest();
            requestUserContinue();
        } else if (selection == 2) {
            clearScreen();
            displayEmployeeRequestByChangeId();
            requestUserContinue();
        } else if (selection == 3) {
            goBackMainMenu();
            break;
        } else {
            clearScreen();
            cout << "Invalid selection. Returning to employee menu." << endl;
        }
    } while (selection != 3);
}

//---------------------------------------------------------------------
// Function: handleEngineerMenu
// Description: Handles the engineer menu operations.
// Space Complexity: O(1)
// Implementation: This function displays the engineer menu and handles user input for:
//                 1) Update Change Item
//                 2) Create Product Release
//                 3) Create Product
//                 4) Generate All Not Done Change Items Report-#1
//                 5) Generate Completed Change Items Report-#2"
//                 6) Go back to main menu
//The function repeatedly displays the menu until the user chooses to go back to the main menu.
//---------------------------------------------------------------------
void handleEngineerMenu() {
    int selection;
    do {
        clearScreen();
        displayEngineerMenuUI();
        selection = getSelection(1, 6);
        if (selection == 1) {
            clearScreen();
            updateChangeItem();
            requestUserContinue();
        } else if (selection == 2) {
            clearScreen();
            createProductRelease();
            requestUserContinue();
        } else if (selection == 3) {
            clearScreen();
            createProduct();
            requestUserContinue();
        } else if (selection == 4) {
            clearScreen();
            generateReport1();
            requestUserContinue();
        } else if (selection == 5) {
            clearScreen();
            generateReport2();
            requestUserContinue();
        } else if (selection == 6) {
            goBackMainMenu();
            break;
        } else {
            clearScreen();
            cout << "Invalid selection. Returning to engineer menu." << endl;
        }
    } while (selection != 6);
}



//---------------------------------------------------------------------
// Function: goBackMainMenu
// Description: Goes back to the main menu.
// Implementation: Called to return to the main menu from any sub-menu.
//---------------------------------------------------------------------
void goBackMainMenu() {
    displayMainMenu();
}