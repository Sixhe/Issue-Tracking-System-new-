/*
 * Employee.h
 * 
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Function comment updated
 * - 2024-07-16: Add comments
 * 
 * Description:
 * This file contains the declarations for functions that handle employee-related operations in 
 * the Issue Tracking System (ITS) application. It includes functions for creating and managing 
 * employee tasks such as bug and feature requests.
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "FileHandler.h"
using namespace std;

// Function to add a new employee based on phone number
// Parameters:
// - phoneNumber: A char array containing the employee's phone number (10-11 digits)
void addNewEmployee(char phoneNumber[11]);


// Function to add a request for an employee
// Prompts user for customer details and request information
void addEmployeeRequest();

// Function to display employee request by change ID
// Retrieves and displays request details based on the provided change ID
void displayEmployeeRequestByChangeId();




#endif // EMPLOYEE_H
