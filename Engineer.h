/*
 * Engineer.h
 *
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Function comment updated
 * - 2024-07-10: Update some functions
 * - 2024-07-11: Create and delete some functions
 * - 2024-07-15: Fixed some bugs
 * - 2024-07-16: Comment updated
 * - 2024-07-24: function name update
 *
 * Description:
 * This file contains the declarations for functions that handle engineer-related operations in
 * the Issue Tracking System (ITS) application. It includes functions for creating and managing
 * product releases, change items, and generating reports.
 */

#ifndef ENGINEER_H
#define ENGINEER_H

// Include Header File
#include <string>
#include <cstring>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include "FileHandler.h"

using namespace std;

// Create unique release for different product
// User need to enter release id and select product
void createProductRelease();

// Create new product
// User need to enter product name
void createProduct();

// This function will geneate 
// all not done change item list
void generateReport1();

// This function will generate
// informaton about finished change item
void generateReport2();

// Function for user enter change of request
// It will return all request information
void enterChange(Request& R);

// This function will update selected change item
void updateChangeItem();

// This is auxillary function
// User need to eneter selection of all change item
// and it will return change item which user selects
Request selectFromAllChangeItem(char* productName);

// Retrieves product information from a file
// User needs to provide the file index, change item index, array of Request objects, product name and number of change items to read
int getAllChangeItemFromFile(int, int, Request*, int, char*);

// This is auxillary function
// User need to eneter selection of all not done change item
// and it will return change item which user selects
void displayAllNotDoneChangeItem(char* productName);

// Retrieves product information from a file
// User needs to provide the file index, change item index, array of Request objects, product name and number of change items to read
int getAllNotDoneChangeItemFromFile(int, int, Request*, int, char*);


#endif // ENGINEER_H
