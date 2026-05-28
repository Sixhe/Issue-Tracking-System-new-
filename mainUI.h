/*
 * mainUI.h
 * 
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Updated to include functions for displaying Engineer menu and related actions
 * - 2024-06-27: Function comment updated
 * - 2024-07-02: Comment misrepresent fixed
 * - 2024-07-28: add requestUserContinue() function
 * 
 * Description:
 * This file contains the declarations for functions that handle the user interface (UI) for the 
 * Issue Tracking System (ITS) application. It includes functions for displaying menus and 
 * getting user input.
 */

#ifndef MAINUI_H
#define MAINUI_H

#include <iostream>
#include "FileHandler.h"

//---------------------------------------------------------------------
// Function: displayMainMenuUI
// Description: Displays the main menu text.
// Implementation: This function is called to display the main menu options to the user.
//---------------------------------------------------------------------
void displayMainMenuUI();

//---------------------------------------------------------------------
// Function: displayCustomerMenuUI
// Description: Displays the customer menu text.
// Implementation: This function is called to display the customer menu options to the user.
//---------------------------------------------------------------------
void displayCustomerMenuUI();

//---------------------------------------------------------------------
// Function: displayEmployeeMenuUI
// Description: Displays the employee menu text.
// Implementation: This function is called to display the employee menu options to the user.
//---------------------------------------------------------------------
void displayEmployeeMenuUI();

//---------------------------------------------------------------------
// Function: displayEngineerMenuUI
// Description: Displays the engineer menu text.
// Implementation: This function is called to display the engineer menu options to the user.
//---------------------------------------------------------------------
void displayEngineerMenuUI();

//---------------------------------------------------------------------
// Function: exitProgram
// Description: Exits the program.
// Implementation: Clears the screen and displays a thank you message before exiting the program.
//---------------------------------------------------------------------
void exitProgram();

//---------------------------------------------------------------------
// Function: getSelection
// Description: Gets the user's selection within a specified range.
// Implementation: This function prompts the user to make a selection within the given range [min, max] and returns the selected value.
//---------------------------------------------------------------------
int getSelection(int min, int max);

//---------------------------------------------------------------------
// Function: requestUserContinue
// Description: Requests user input to continue, return to the previous menu, or exit the program.
// Implementation: Prompts the user to press [B] to return to the previous menu, or [Q] to exit the program.
//---------------------------------------------------------------------
void requestUserContinue();

#endif // MAINUI_H
