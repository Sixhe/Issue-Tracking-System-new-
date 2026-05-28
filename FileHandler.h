/*
 * FileHandler.h
 * 
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Updated to include insertRequest function
 * - 2024-06-27: Function comment updated
 * - 2024-07-02: Add Customer() & insertEmployee() 
 * - 2024-07-06: Add displayProductName() & readFileByProduct & ByReuqest()
 * - 2024-07-08: Add readCustomerInfo() 
 * - 2024-07-12: Update and fix some bug in searchRelease() and searchProduct()
 * - 2024-07-14: create sortRequestByPriority() and revise comments
 * - 2024-07-24: add some functions
 * 
 * Description:
 * This file contains the declarations for functions that handle file operations for storing 
 * and retrieving employee, customer, and engineer information, as well as request/product 
 * information in the Issue Tracking System (ITS) application.
 */

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <iomanip>

 /* Since this is a simple class, 
  * we are not using any private attribute.
  * This is for data access convinent.
  */
// Class to represent a customer
struct Customer {
    char phoneNumber[11];           // Customer's phone number, up to 10 digits plus null terminator
    char name[13];                  // Customer's name, up to 12 characters plus null terminator
    char email[24];                 // Customer's email address, up to 23 characters plus null terminator
};

// Class to represent an employee
struct Employee {
    char phoneNumber[11];           // Employee's phone number, up to 10 digits plus null terminator
    char name[12];                  // Employee's name, up to 11 characters plus null terminator
    char email[24];                 // Employee's email address, up to 23 characters plus null terminator
    char department[31];            // Employee's department, up to 30 characters plus null terminator
};

struct Request {
    char phoneNumber[12];           // 10-11 digits + null terminator
    char releaseId[7];              // Exactly 6 digits + null terminator
    char changeId[7];               // Assume same format as Release ID
    char description[31];           // 1-30 characters + null terminator
    char priority[2];               // Number between 1 and 5, default priority is 1, highest priority is 5
    char date[11];                  // Date in format YYYY-MM-DD + null terminator
    char anticipatedReleaseId[7];   // Exactly 6 digits + null terminator
    char state[12];                 // One of the specified states + null terminator
    char productName[13];           // 12 characters + null terminator
};

struct Product {
    char productName[13];           // 12 characters + null terminator
    char productRelease[7];         // Exactly 6 digits + null terminator
};

//Function for insert new request into file
void insertRequest(const Request&);

//Function for insert a new customer and store it into 'customers.dat'
void insertCustomer(const Customer&);

//Function for insert a new employee and store it into 'employees.dat'
void insertEmployee(const Employee&);

//Function for insert new product object into "products.dat" file
void insertProduct(const Product&);

//Insert changed request into "requests.dat" file
void modifyRequest(const Request&);

//Insert changed release into "products.dat" file
void modifyProduct(const Product&);

// Function to search customer by a keyword in the 'customers.dat' file and return the index of the record where it is located
int searchCustomer(const std::string& keyword);

// Function to search employee by a keyword in the 'employees.dat' file and return the index of the record where it is located
int searchEmployee(const std::string& keyword);

// Function to search request by a keyword in the "requests.dat" file and return the index of the record where it is located
int searchRequest(const std::string& keyword);

// Function to search product by a keyword in the "products.dat" file and return the index of the record where it is located
int searchProduct(const std::string& keyword);

// Searches for a product release by product name
// User needs to enter the product name and a reference to store the release information
int searchRelease(const std::string& productName, std::string& productRelease);

// Displays the product name
// User needs to provide the product name and its length
void displayProductName(const char* productName, int length);

// Allows the user to select a product by a selection menu
// Returns the selected Product object
Product selectProduct();

// Retrieves product information from a file
// User needs to provide the file index, product index, array of Product objects, and number of products to read
int getProductFromFile(int, int, Product *, int );

// Sorts requests by their priority(1,2,3,4,5)
void sortRequestByPriority();

// Reads product information from a file using an fstream object
// Needs to provide the fstream object and a reference to store the Product data
bool readFileByProduct(std::fstream &, Product &);

// Reads product information from a file using an ifstream object
// Needs to provide the ifstream object and a reference to store the Product data
bool readFileByProduct(std::ifstream &, Product &);

// Reads request information from a file using an fstream object
// Needs to provide the fstream object and a reference to store the Request data
bool readFileByRequest(std::fstream &, Request &);

// Reads request information from a file using an ifstream object
// Needs to provide the ifstream object and a reference to store the Request data
bool readFileByRequest(std::ifstream &, Request &);

// Prompts the user to enter a correct integer value
// Returns the integer value entered by the user
int enterCorrectIntValue();

// Reads customer information from a specific index
// Provide the index of the customer information to read
Customer readCustomerInfo(int);

// Reads employee information from a specific index
// Provide the index of the employee information to read
Employee readEmployeeInfo(int);

// Reads request information based on a keyword
// Provide the keyword to search for in the request information
Request readRequestInfo(const std::string&);

// This is auxillary function
// User need to eneter Y or N
bool enterYesOrNo();

// This is auxillary function
// User need to eneter selection of actual release
// and it will return actual release which user selects
Product selectRelease(char* productName);

// Retrieves product information from a file
// User needs to provide the file index, product index, array of Product objects, product name and number of products to read
int getProductReleaseFromFile(int, int, Product*, int, char*);

// Reads the counter value from a file and returns it.
int readCounter();

// Writes the given counter value to a file.
void writeCounter(int counter);

// Generates and returns a sequential change ID based on an incremented counter.
std::string generateSequentialChangeID();

// Returns the current date in YYYY-MM-DD format.
std::string getCurrentDate();

// Check whether file exist
// If file exist, it will return false
bool checkFileExist(std::string fileName);
#endif // FILEHANDLER_H
