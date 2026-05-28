/*
 * Customer.h
 * 
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Function comment updated
 * - 2024-07-16: Add comments
 * 
 * Description:
 * This file contains the declarations for functions that handle customer-related operations in 
 * the Issue Tracking System (ITS) application. It includes functions for creating and managing 
 * customer requests.
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <fstream>
#include <cstring> // for strcpy and strstr
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept> // for exception handling
#include "FileHandler.h"

using namespace std;

// Function to create a new customer file
void addNewCustomer(char phoneNumber[11]);

// Function to create a customer feature request
// Includes steps for entering phone number, selecting product name, and entering release ID and description
void addCustomerRequest();

// Function to display a customer request by change ID
// Prompts the user to enter a change ID, searches for the request, and displays the request details
void displayCustomerRequestByChangeId();



#endif // CUSTOMER_H
