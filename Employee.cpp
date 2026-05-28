/*
 * Employee.cpp
 *
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Function comment updated
 * - 2024-07-16: Add comments
 * - 2024-07-20: fixed change id search bug
 * - 2024-07-25: fixed character missing bug
 * - 2024-07-30: add no file eixst detection
 *
 * Description:
 * This file contains the declarations for functions that handle employee-related operations in
 * the Issue Tracking System (ITS) application. It includes functions for creating and managing
 * employee tasks such as bug and feature requests.
 */

#include "Employee.h"


using namespace std;

const string EMPLOYEE_FILE = "employees.dat"; // Path to the employee data file
const string REQUEST_FILE = "requests.dat";  // Path to the request data file
const string PRODUCT_FILE = "products.dat";  // Path to the product data file




//---------------------------------------------------------------------
// Function: addNewEmployee
// Space Complexity : O(1)
// Description: Adds a new employee to the system by prompting the user for details.
// Implementation: Searches for existing employee by phone number. If not found, creates
//                 a new profile by collecting name, email, and department.
//---------------------------------------------------------------------
void addNewEmployee(char phoneNumber[11]) {
    string name;
    string email;
    string department;
    char nameC[13];
    char emailC[24];
    char departmentC[31];
    

    // Loop to ensure valid employee name input
    while (true) {
        cout << "Enter Employee Name (1-13 letters): ";
        cin.ignore();
        getline(cin, name);
        if (name.length() > 0 && name.length() < 14) {
            break;  // Break the loop if the name length is valid
        } else {
            cout << "Please enter a valid Name with 1 to 13 letters.\n";
        }
    }

    // Convert std::string to char array
    strncpy(nameC, name.c_str(), sizeof(nameC));
    nameC[sizeof(nameC) - 1] = '\0';  // Ensure null termination

    // Loop to ensure valid employee email input
    while (true) {
        cout << "Enter Employee Email (1-24 characters): ";
        getline(cin, email);
        if (email.length() > 0 && email.length() < 25) {
            break;  // Break the loop if the email length is valid
        } else {
            cout << "Please enter a valid Email with 1 to 24 characters.\n";
        }
    }

    // Convert std::string to char array
    strncpy(emailC, email.c_str(), sizeof(emailC));
    emailC[sizeof(emailC) - 1] = '\0';  // Ensure null termination

    // Loop to ensure valid employee department input
    while (true) {
        cout << "Enter Employee Department (1-30 characters): ";
        getline(cin, department);
        if (department.length() > 0 && department.length() < 31) {
            break;  // Break the loop if the department length is valid
        } else {
            cout << "Please enter a valid Department with 1 to 30 characters.\n";
        }
    }

    // Convert std::string to char array
    strncpy(departmentC, department.c_str(), sizeof(departmentC));
    departmentC[sizeof(departmentC) - 1] = '\0';  // Ensure null termination

    // Create a new employee instance and populate it with the collected data
    Employee employee;
    strcpy(employee.phoneNumber, phoneNumber);
    strcpy(employee.name, nameC);
    strcpy(employee.email, emailC);
    strcpy(employee.department, departmentC);
    
    // Insert the new employee into the file
    insertEmployee(employee);

    // Print a success message
    cout << "Employee created successfully!\n";
}

//---------------------------------------------------------------------
// Function: addEmployeeRequest
// Space Complexity : O(1)
// Description: Adds a new request for an employee, including details like release ID, product name, and description.
// Implementation: Prompts for phone number, searches for employee, creates new profile if needed, and collects request details.
//---------------------------------------------------------------------
void addEmployeeRequest() {
    string phoneNumber;
    string description;
    string productName;
    string priority = "1"; // Default priority 1 is the lowest priority, 5 is the highest
    string state = "New"; // Default state is New
    string anticipatedReleaseId="None";// Default is none
    char phoneNumberC[12];
    char descriptionC[31];
    char productNameC[13];
    

    try {
        // Step 1: Prompt user to enter phone number
        bool check = false; // Value for check whether enter is wrong
        int i = 0; // Value for while loop
        cout << "Enter Employee Phone Number (10-11 digits): ";
        cin.ignore();
        getline(cin, phoneNumber);
        // check length of input value
        if (phoneNumber.length() < 10 && phoneNumber.length() > 11) {
            check = true;
        }
        else {
            phoneNumber.copy(phoneNumberC, phoneNumber.length(), 0);
            // loop for check whether input value is digit
            while (i != phoneNumber.length()) {
                if (!isdigit(phoneNumberC[i])) {
                    check = true;
                }
                i++;
            }
        }
        // When input value length equal to 6, but value is not digit
        // ask user enter again
        while (phoneNumber.length() < 10 || phoneNumber.length() > 11 || check) {
            check = false;
            cout << "Please enter a valid Phone Number with 10 to 11 digits.\nEnter Employee Phone Number (10-11 digits): ";
            getline(cin, phoneNumber);
            phoneNumber.copy(phoneNumberC, phoneNumber.length(), 0);
            int j = 0;
            // loop for check whether input value is digit
            while (j != phoneNumber.length()) {
                if (!isdigit(phoneNumberC[j])) {
                    check = true;
                }
                j++;
            }
        }
        phoneNumber.copy(phoneNumberC, phoneNumber.length(), 0);

        phoneNumberC[sizeof(phoneNumberC) - 1] = '\0';  // Ensure null termination

        int index = 0;

        // Step 2: Search for the employee by phone number
        // Check if file exist.
        if (!checkFileExist(EMPLOYEE_FILE)) {
            index = -1;
        }
        else {
            index = searchEmployee(phoneNumberC);
        }

        if (index == -1) {
            cout << "Cannot find employee. Create new profile (Y/N)? ";
            if (enterYesOrNo()) {
                addNewEmployee(phoneNumberC);
            }
            else { return; }
        }

        if (!checkFileExist(PRODUCT_FILE)) {
            cout << "No product exist. Please create product first!" << endl;
            return;
        }

        // Step 3: Select product name
        Product product;
        product = selectProduct();
        if (product.productName[0] == '\0') { return; } // When product name is empty, end function
        productName = product.productName;

        // Convert std::string to char array
        strncpy(productNameC, productName.c_str(), sizeof(productNameC));
        productNameC[sizeof(productNameC) - 1] = '\0';  // Ensure null termination

        // Step 4: Enter release ID
        product = selectRelease(product.productName);
        if (product.productRelease[0] == '\0') { return; }

        // Step 5: Enter description with validation loop
        while (true) {
            cout << "Enter Description (1-30 characters): ";
            cin.ignore();
            getline(cin, description);
            if (description.length() >= 1 && description.length() <= 30) {
                break;
            } else {
                cout << "Please enter a valid Description with 1 to 30 characters.\n";
            }
        }

        // Convert std::string to char array
        strncpy(descriptionC, description.c_str(), sizeof(descriptionC));
        descriptionC[sizeof(descriptionC) - 1] = '\0';  // Ensure null termination

        // Create a new request
        Request request;
        strcpy(request.phoneNumber, phoneNumberC);
        strcpy(request.releaseId, product.productRelease);
        strcpy(request.description, descriptionC);
        strcpy(request.productName, productNameC);
        strcpy(request.priority, priority.c_str());
        strcpy(request.state, state.c_str());
        strcpy(request.changeId, generateSequentialChangeID().c_str());
        strcpy(request.date, getCurrentDate().c_str());
        strcpy(request.anticipatedReleaseId, anticipatedReleaseId.c_str());



        // Insert the new request into the file
        insertRequest(request);

        // Print a success message
        cout << "Change ID: " << request.changeId << endl;
        cout << "Request created successfully!\n";
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << "\n";
        cout << "Returning to main menu.\n";
    } catch (...) {
        cout << "An unexpected error occurred. Returning to main menu.\n";
    }
}

//---------------------------------------------------------------------
// Function: displayEmployeeRequestByChangeId
// Space Complexity : O(1)
// Description: Displays the details of an employee request based on the change ID.
// Implementation: Prompts for change ID, searches for the request, and displays relevant details.
//---------------------------------------------------------------------
void displayEmployeeRequestByChangeId() {
    // Check if file exist.If file not exist, end function
    if (!checkFileExist(REQUEST_FILE)) {
        cout << "No request exist. Please create request first!" << endl;
        return;
    }

    string input;
    char id[7];
    int i = 0;
    bool check = false;
    cout << "Enter Change ID (6 digits): ";
    cin.clear();
    cin.ignore();
    getline(cin, input);
    if (input.length() != 6) {
        check = true;
    }
    else {
        input.copy(id, 6, 0);
        // loop for check whether input value is digit
        while (i != 6) {
            if (!isdigit(id[i])) {
                check = true;
            }
            i++;
        }
    }
    // When input value length equal to 6, but value is not digit
    // ask user enter again
    while (input.length() != 6 || check) {
        check = false;
        cout << "Please enter a valid Change ID with exactly 6 digits.\nEnter Change ID (6 digits): ";
        cin.clear();
        getline(cin, input);
        input.copy(id, 6, 0);
        int j = 0;
        // loop for check whether input value is digit
        while (j != 6) {
            if (!isdigit(id[j])) {
                check = true;
            }
            j++;
        }
    }
    input.copy(id, 6, 0);
    id[6] = '\0';
    if (searchRequest(id) == -1) {
        cout << "No such request.\n";
    } else {
        Request R = readRequestInfo(id);

        if (checkFileExist(EMPLOYEE_FILE)) {
            if (searchEmployee(R.phoneNumber) == -1) {
                cout << "No such employee request!" << endl;
                return;
            }
        }

        Employee E = readEmployeeInfo(searchEmployee(R.phoneNumber));

        cout << "Request - " << R.changeId << endl;
        cout << "State: " << R.state << endl;
        cout << "Priority: " << R.priority << endl;
        cout << "Change ID: " << R.changeId << endl;
        cout << "Release ID: " << R.releaseId << endl;
        cout << "Date: " << R.date << endl;
        cout << "Employee name: " << E.name << endl;
        cout << "Employee phone number: " << E.phoneNumber << endl;
        cout << "Employee email: " << E.email << endl;
        cout << "Employee department: " << E.department << endl;
        cout << "Description: " << R.description << endl;
    }
}
