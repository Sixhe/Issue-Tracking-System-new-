/*
 * FileHandler.cpp
 *
 * Revision History:
 * - 2024-06-26: Initial implementation
 * - 2024-06-27: Updated to include insertRequest and insertProduct functions
 * - 2024-07-01: Added readFileByRequest overloaded functions for ifstream and fstream objects
 * - 2024-07-03: Implemented modifyRequest and modifyProduct functions
 * - 2024-07-05: Added searchCustomer, searchEmployee, searchRequest, and searchProduct functions
 * - 2024-07-07: Integrated deleteReleaseFromFile and deleteProductFromFile functions
 * - 2024-07-09: Enhanced error handling in file operations
 * - 2024-07-11: Optimized read and write operations for performance improvements
 * - 2024-07-13: Implemented sortRequestByPriority function for prioritizing requests
 * - 2024-07-15: Added utility functions displayProductName, selectProduct, and getProductFromFile
 * - 2024-07-17: Improved user input validation in enterCorrectIntValue function
 * - 2024-07-24: add some functions
 * - 2024-07-26: fixed select bugs
 * - 2024-07-28: fixed enterCorrectIntValue function
 * 
 * Description:
 * This file contains the implementations for functions that handle file operations for storing
 * and retrieving employee, customer, and engineer information, as well as request/product
 * information in the Issue Tracking System (ITS) application.
 *
 * Discussion:
    Memory Usage:
        Functions that involve reading or writing to files (insertRequest, insertCustomer, 
        insertEmployee, insertProduct, etc.) will require memory to buffer the data being read or written. 
        The size of these buffers can impact memory usage. Search functions (searchCustomer, searchEmployee, 
        searchRequest, etc.) need to load up to 20 obejcts from the file into memory, especially for our 
        files which are not indexed and need to be scanned linearly.

    Speed and Time Efficiency:
        Insert and modify functions typically involve I/O operations, which can be slow compared 
        to in-memory operations. Efficient I/O handling, such as batching writes or using asynchronous I/O, 
        can improve speed.Linear search is straightforward but slow for large datasets. Implementing indexing or using binary search 
        techniques can significantly improve search speed. However indexing and binary search is impossible
        for this object since the memory is limited. As a result we decide to use linear method.
        Sorting functions, such as sortRequestByPriority, need to consider the time complexity of the sorting 
        algorithm. MergeSort is used for better performance on our large datasets.

    Space Efficiency:
        Functions that write to files must consider the space available on the storage medium. Large datasets or 
        frequent writes can quickly consume disk space.Duplicate data entries (e.g., multiple records for the 
        same customer or product) can lead to wasted space. Duplicate data management and verification mitigate this.

    Implementation Issues:
        Error Handling: Functions handle cases where files are not found, data is corrupted, or I/O operations fail.
        Data Consistency: Ensuring data consistency across different files (e.g., requests.dat, customers.dat, 
            employees.dat). This involve implementing mechanisms to check and maintain data integrity.
        Code Reusability: Functions like readFileByProduct and readFileByRequest designed to be reusable and modular,
            function overloading to handle different file types and data structures.
        Performance Optimization: For functions that handle large data sets frequently, performance optimization techniques
            such as indexing, caching, and efficient data structures included.

    Security Considerations:
        Data Privacy: Functions handling sensitive data (e.g., customer and employee information) are implement properly 
            access controls functions and encryption mechanisms.
 */

#include "FileHandler.h"

using namespace std;

// Define constants for the file names
const string REQUEST_FILE = "requests.dat";
const string PRODUCT_FILE = "products.dat";
const string EMPLOYEE_FILE = "employees.dat";
const string CUSTOMER_FILE = "customers.dat";
const string COUNTER_FILE = "id_counter.dat";
//---------------------------------------------------------------------
// Function: readFileByProduct
// Description: Reads product information from a file using an fstream object
// Space Complexity: O(1)
// Implementation: User needs to provide the fstream object and a reference to store the Product data
//---------------------------------------------------------------------
bool readFileByProduct(fstream& inFile, Product& P) {
    // Reads the product name from the file into the product object
    inFile.read(P.productName, sizeof(P.productName));

    // Reads the product release from the file into the product object
    inFile.read(P.productRelease, sizeof(P.productRelease));
    
    // Returns true indicating the read operation was successful
    return true;
}

//---------------------------------------------------------------------
// Function: readFileByProduct (overloaded)
// Description: Reads product information from a file using an ifstream object
// Space Complexity: O(1)
// Implementation: User needs to provide the ifstream object and a reference to store the Product data
//---------------------------------------------------------------------
bool readFileByProduct(ifstream& inFile, Product& P) {
    // Reads the product name from the file into the product object
    inFile.read(P.productName, sizeof(P.productName));

    // Reads the product release from the file into the product object
    inFile.read(P.productRelease, sizeof(P.productRelease));
    
    // Returns true indicating the read operation was successful
    return true;
}

//---------------------------------------------------------------------
// Function: readFileByRequest
// Description: Reads request information from a file using an fstream object
// Space Complexity: O(1)
// Implementation: User needs to provide the fstream object and a reference to store the Request data
//---------------------------------------------------------------------
bool readFileByRequest(fstream& inFile, Request& request) {
    // Reads the phone number, release ID, change ID, description,
    // priority, date, anticipated release ID, state, and product name from the file into the request object
    inFile.read(request.phoneNumber, sizeof(request.phoneNumber));
    inFile.read(request.releaseId, sizeof(request.releaseId));
    inFile.read(request.changeId, sizeof(request.changeId));
    inFile.read(request.description, sizeof(request.description));
    inFile.read(request.priority, sizeof(request.priority));
    inFile.read(request.date, sizeof(request.date));
    inFile.read(request.anticipatedReleaseId, sizeof(request.anticipatedReleaseId));
    inFile.read(request.state, sizeof(request.state));
    inFile.read(request.productName, sizeof(request.productName));

    // Returns true indicating the read operation was successful
    return true;
}

//---------------------------------------------------------------------
// Function: readFileByRequest (overloaded)
// Description: Reads request information from a file using an ifstream object
// Space Complexity: O(1)
// Implementation: User needs to provide the ifstream object and a reference to store the Request data
//---------------------------------------------------------------------
bool readFileByRequest(ifstream& inFile, Request& request) {
    // Reads the phone number, release ID, change ID, description,
    // priority, date, anticipated release ID, state, and product name from the file into the request object
    inFile.read(request.phoneNumber, sizeof(request.phoneNumber));
    inFile.read(request.releaseId, sizeof(request.releaseId));
    inFile.read(request.changeId, sizeof(request.changeId));
    inFile.read(request.description, sizeof(request.description));
    inFile.read(request.priority, sizeof(request.priority));
    inFile.read(request.date, sizeof(request.date));
    inFile.read(request.anticipatedReleaseId, sizeof(request.anticipatedReleaseId));
    inFile.read(request.state, sizeof(request.state));
    inFile.read(request.productName, sizeof(request.productName));

    // Returns true indicating the read operation was successful
    return true;
}

//---------------------------------------------------------------------
// Function: insertRequest
// Description: Inserts a new request into a binary file
// Space Complexity: O(1)
// Implementation: Appends a new request to the request file
//---------------------------------------------------------------------
void insertRequest(const Request& request) {
    // Open the file in binary append mode
    ofstream outFile(REQUEST_FILE, ios::binary | ios::app);
    if (outFile.is_open()) { // Check if the file is successfully opened
        outFile.write(request.phoneNumber, sizeof(request.phoneNumber));
        outFile.write(request.releaseId, sizeof(request.releaseId));
        outFile.write(request.changeId, sizeof(request.changeId));
        outFile.write(request.description, sizeof(request.description));
        outFile.write(request.priority, sizeof(request.priority));
        outFile.write(request.date, sizeof(request.date));
        outFile.write(request.anticipatedReleaseId, sizeof(request.anticipatedReleaseId));
        outFile.write(request.state, sizeof(request.state));
        outFile.write(request.productName, sizeof(request.productName));
        outFile.close(); // Close the file after writing
    }
    else {
        // Print an error message if the file could not be opened
        cout << "Unable to open request file for writing!" << endl;
    }
}

//---------------------------------------------------------------------
// Function: insertCustomer
// Description: Inserts a new customer into a binary file
// Space Complexity: O(1)
// Implementation: Appends a new customer to the customer file
//---------------------------------------------------------------------
void insertCustomer(const Customer& customer) {
    // Open the file in binary append mode
    ofstream outFile(CUSTOMER_FILE, ios::binary | ios::app);
    if (outFile.is_open()) { // Check if the file is successfully opened
        outFile.write(customer.name, sizeof(customer.name));
        outFile.write(customer.phoneNumber, sizeof(customer.phoneNumber));
        outFile.write(customer.email, sizeof(customer.email));
        outFile.close(); // Close the file after writing
    }
    else {
        // Print an error message if the file could not be opened
        cout << "Unable to open customer file for writing!" << endl;
    }
}

//---------------------------------------------------------------------
// Function: insertEmployee
// Description: Function to insert a new employee into a binary file
// Space Complexity: O(1)
// Implementation: This function appends a new employee to the employee file
//---------------------------------------------------------------------
void insertEmployee(const Employee& employee) {
    ofstream outFile(EMPLOYEE_FILE, ios::binary | ios::app);
    if (outFile.is_open()) { // Check if the file is successfully opened
        outFile.write(employee.name, sizeof(employee.name));
        outFile.write(employee.phoneNumber, sizeof(employee.phoneNumber));
        outFile.write(employee.email, sizeof(employee.email));
        outFile.write(employee.department, sizeof(employee.department));
        outFile.close(); // Close the file after writing
    }
    else {
        cout << "Unable to open employee file for writing!" << endl;
    }
}

//---------------------------------------------------------------------
// Function: insertProduct
// Description: Function to insert a new product into a binary file
// Space Complexity: O(1)
// Implementation: This function appends a new product to the product file
//---------------------------------------------------------------------
void insertProduct(const Product& product) {
    ofstream outFile(PRODUCT_FILE, ios::binary | ios::app);
    if (outFile.is_open()) { // Check if the file is successfully opened
        outFile.write(product.productName, sizeof(product.productName));
        outFile.write(product.productRelease, sizeof(product.productRelease));
        outFile.close(); // Close the file after writing
    }
    else {
        cout << "Unable to open product file for writing!" << endl;
    }
}

//---------------------------------------------------------------------
// Function: modifyRequest
// Description: Function to modify an existing request in a binary file at the specified index
// Space Complexity: O(1)
// Implementation: This function updates an existing request in the request file at the given index
//---------------------------------------------------------------------
void modifyRequest(const Request& request) {
    fstream file;
    file.open(REQUEST_FILE, ios::binary | ios::in | ios::out);
    if (file.is_open()) { // Check if the file is successfully opened
        int index = searchRequest(request.phoneNumber);
        file.seekp(index * sizeof(Request), ios::beg); // Move to the specified index
        file.write(request.phoneNumber, sizeof(request.phoneNumber));
        file.write(request.releaseId, sizeof(request.releaseId));
        file.write(request.changeId, sizeof(request.changeId));
        file.write(request.description, sizeof(request.description));
        file.write(request.priority, sizeof(request.priority));
        file.write(request.date, sizeof(request.date));
        file.write(request.anticipatedReleaseId, sizeof(request.anticipatedReleaseId));
        file.write(request.state, sizeof(request.state));
        file.write(request.productName, sizeof(request.productName));
        file.close(); // Close the file after writing
        sortRequestByPriority();
    }
    else {
        cout << "Unable to open file for reading/writing!" << endl;
    }
}

//---------------------------------------------------------------------
// Function: modifyProduct
// Description: Function to modify an existing product in a binary file at the specified index
// Space Complexity: O(1)
// Implementation: This function updates an existing product in the product file at the given index
//---------------------------------------------------------------------
void modifyProduct(const Product& product) {
    fstream file;
    file.open(PRODUCT_FILE, ios::binary | ios::in | ios::out);
    if (file.is_open()) { // Check if the file is successfully opened
        int index = searchProduct(product.productName);
        file.seekp(index * sizeof(Product), ios::beg); // Move to the specified index
        file.write(product.productName, sizeof(product.productName));
        file.write(product.productRelease, sizeof(product.productRelease));
        file.close(); // Close the file after writing
    }
    else {
        cout << "Unable to open file for reading/writing!" << endl;
    }
}

//---------------------------------------------------------------------
// Function: searchCustomer
// Description: Function to search for a keyword in the customer file and return the index of the record where it is located
// Space Complexity: O(n) where n is the number of records in the customer file
// Implementation: This function opens the customer file in binary read mode, reads each Customer object, 
// and checks if any field contains the keyword. It returns the index of the matching record or -1 if no match is found.
//---------------------------------------------------------------------
int searchCustomer(const std::string& keyword) {
    ifstream inFile(CUSTOMER_FILE, ios::binary);  // Open the customer file in binary read mode
    int index = 0;
    bool found = false;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open customer file for searching!" << endl;
        return -1;
    }

    // Continue until the end of the file
    while (inFile.peek() != EOF) {
        Customer customer;
        inFile.read(customer.name, sizeof(customer.name));                // Read the name field
        inFile.read(customer.phoneNumber, sizeof(customer.phoneNumber));  // Read the phone number field
        inFile.read(customer.email, sizeof(customer.email));              // Read the email field

        // Check if any field contains the keyword
        if (!strcmp(customer.name, keyword.c_str()) ||
            !strcmp(customer.phoneNumber, keyword.c_str()) ||
            !strcmp(customer.email, keyword.c_str())) {
            found = true;
            break; // Exit the loop if the keyword is found
        }
        index++;
    }

    inFile.close(); // Close the file after reading
    return found ? index : -1; // Return the index if the keyword is found, otherwise return -1
}

//---------------------------------------------------------------------
// Function: searchEmployee
// Description: Function to search for a keyword in the employee file and return the index of the record where it is located
// Space Complexity: O(n) where n is the number of records in the employee file
// Implementation: This function opens the employee file in binary read mode, reads each Employee object, and checks if any field contains the keyword.
// It returns the index of the matching record or -1 if no match is found.
//---------------------------------------------------------------------
int searchEmployee(const std::string& keyword) {
    ifstream inFile(EMPLOYEE_FILE, ios::binary);  // Open the employee file in binary read mode
    int index = 0;
    bool found = false;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open employee file for searching!" << endl;
        return -1;
    }

    // Continue until the end of the file
    while (inFile.peek() != EOF) {
        Employee employee;
        inFile.read(employee.name, sizeof(employee.name));                // Read the name field
        inFile.read(employee.phoneNumber, sizeof(employee.phoneNumber));  // Read the phone number field
        inFile.read(employee.email, sizeof(employee.email));              // Read the email field
        inFile.read(employee.department, sizeof(employee.department));    // Read the department field

        // Check if any field contains the keyword
        if (!strcmp(employee.name, keyword.c_str()) ||
            !strcmp(employee.phoneNumber, keyword.c_str()) ||
            !strcmp(employee.email, keyword.c_str()) ||
            !strcmp(employee.department, keyword.c_str())) {
            found = true;
            break; // Exit the loop if the keyword is found
        }
        index++;
    }

    inFile.close(); // Close the file after reading
    return found ? index : -1; // Return the index if the keyword is found, otherwise return -1
}

//---------------------------------------------------------------------
// Function: searchRequest
// Description: Function to search for a keyword in the request file and return the index of the record where it is located
// Space Complexity: O(n) where n is the number of records in the request file
// Implementation: This function opens the request file in binary read mode, reads each Request object, and checks if any field contains the keyword.
// It returns the index of the matching record or -1 if no match is found.
//---------------------------------------------------------------------
int searchRequest(const std::string& keyword) {
    ifstream inFile(REQUEST_FILE, ios::binary);  // Open the request file in binary read mode
    int index = 0;
    bool found = false;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open request file for searching!" << endl;
        return -1;
    }
    Request request;

    // Continue until the end of the file
    while (inFile.peek() != EOF) {
        readFileByRequest(inFile,request);
        // Check if any field contains the keyword
        if (!strcmp(request.phoneNumber, keyword.c_str())||
            !strcmp(request.releaseId, keyword.c_str())||
            !strcmp(request.changeId, keyword.c_str())||
            !strcmp(request.description, keyword.c_str())||
            !strcmp(request.priority, keyword.c_str())||
            !strcmp(request.date, keyword.c_str())||
            !strcmp(request.anticipatedReleaseId, keyword.c_str())||
            !strcmp(request.state, keyword.c_str())||
            !strcmp(request.productName, keyword.c_str())){
            found = true;
            break; // Exit the loop if the keyword is found
        }
        index++;
    }

    inFile.close(); // Close the file after reading
    return found ? index : -1; // Return the index if the keyword is found, otherwise return -1
}

//---------------------------------------------------------------------
// Function: searchProduct
// Description: Function to search for a keyword in the product file and return the index of the record where it is located
// Space Complexity: O(n) where n is the number of records in the product file
// Implementation: This function opens the product file in binary read mode, reads each Product object, and checks if any field contains the keyword.
// It returns the index of the matching record or -1 if no match is found.
//---------------------------------------------------------------------
int searchProduct(const std::string& keyword) {
    ifstream inFile(PRODUCT_FILE, ios::binary);  // Open the product file in binary read mode
    int index = 0;
    bool found = false;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open product file for searching!" << endl;
        return -1;
    }
    Product product;
    // Continue until the end of the file
    while (inFile.peek() != EOF) {
        readFileByProduct(inFile, product);  // Read the product information using the readFileByProduct function

        // Check if any field contains the keyword
        if (!strcmp(product.productName, keyword.c_str())) {
            found = true;
            break; // Exit the loop if the keyword is found
        }
        index++;
    }

    inFile.close(); // Close the file after reading
    return found ? index : -1; // Return the index if the keyword is found, otherwise return -1
}

//---------------------------------------------------------------------
// Function: searchRelease
// Description: Function to search for a product name and release in the product file and return the index of the record where it is located
// Space Complexity: O(n) where n is the number of records in the product file
// Implementation: This function opens the product file in binary read mode, reads each Product object, and checks if the product name and release match the specified values.
// It returns the index of the matching record or -1 if no match is found.
//---------------------------------------------------------------------
int searchRelease(const std::string& productName, std::string& productRelease) {
    ifstream inFile(PRODUCT_FILE, ios::binary);  // Open the product file in binary read mode
    int index = 0;
    bool found = false;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open release file for searching!" << endl;
        return -1;
    }

    // Continue until the end of the file
    while (inFile.peek() != EOF) {
        Product product;
        readFileByProduct(inFile, product);  // Read the product information using the readFileByProduct function

        // Check if the product name and release match the specified values
        if (!strcmp(product.productName, productName.c_str()) &&
            !strcmp(product.productRelease, productRelease.c_str())) {
            found = true;
            break; // Exit the loop if the keyword is found
        }
        index++;
    }

    inFile.close(); // Close the file after reading
    return found ? index : -1; // Return the index if the keyword is found, otherwise return -1
}

//---------------------------------------------------------------------
// Function: displayProductName
// Description: Displays the product name with an option number
// Space Complexity: O(1)
// Implementation: User needs to provide the product name and an integer option
//---------------------------------------------------------------------
void displayProductName(const char* productName, int option) {
    cout << "   " << std::right << setw(2) << option << ") " << productName << endl;
}

//---------------------------------------------------------------------
// Function: selectProduct
// Description: Allows the user to select a product from a list of products
// Space Complexity: O(1)
// Implementation: Returns the selected Product object
//---------------------------------------------------------------------
Product selectProduct() {
    Product P[20];  // Array to store up to 20 Product objects
    int index = 0;  // Index for the array

    // Retrieves product information from a file and updates the index
    index = getProductFromFile(0, index, P, 0);
    // Checks if the file read operation was unsuccessful
    if (index == -1) {
        // Returns an empty Product object if there was an error reading the file
        return Product();
    }

    // Returns the selected Product object from the array
    return P[index];
}

//---------------------------------------------------------------------
// Function: getProductFromFile
// Description: Retrieves product information from a file and handles pagination for displaying products
// Space Complexity: O(1)
// Implementation: Displays 20 product names at a time, handles user input for navigating product lists
//---------------------------------------------------------------------
int getProductFromFile(int oldIndex, int index, Product* P, int storeList) {
    // Display product names 20 at a time
    ifstream inFile(PRODUCT_FILE, ios::binary | ios::in);  // Open the product file in binary read mode
    int originIndex = index;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        // If the file cannot be opened, display an error message and exit the program
        cout << "Unable to open file for reading!" << endl;
        exit(0);
    }

    int list = 0;
    int i = 0;

    // Read products from the file until 20 products are read or the end of file is reached
    while (list < 20 && inFile.peek() != EOF) {
        Product product;
        readFileByProduct(inFile,product);
        // Check if the product release is empty
        if (product.productRelease[0] == '\0') {
            // If the current index matches the index to start reading from
            if (i == index) {
                // Copy the product name to the list and update the index
                strcpy(P[list].productName, product.productName);
                index++;
                list++;
            }
            i++;
        }
    }
    inFile.close(); // Close the file after reading

    int choice;
    // Check if no new products were read
    if (index == originIndex) {
        cout << "No next product list.\nPlease choose another option: ";
        choice = enterCorrectIntValue();

        // Ensure the user makes a valid choice
        while (choice < 1 || choice > storeList + 2) {
            cout << "Wrong selection. Please enter correct selection: ";
            choice = enterCorrectIntValue();
        }

        // Handle the option to display the previous product list
        if (choice == storeList + 2) {
            if (oldIndex == 0) {
                cout << "No previous product list.\nPlease choose another option: ";
                choice = enterCorrectIntValue();
                while (choice < 1 || choice >= storeList + 2) {
                    cout << "Wrong selection. Please enter correct selection: ";
                    choice = enterCorrectIntValue();
                }
                if (choice == storeList + 1) {
                    return -1;
                }
                else {
                    return choice - 1;
                }
            }
            else {
                index = getProductFromFile(oldIndex, originIndex - 20 - storeList, P, 0);
            }
        }
        else if (choice == storeList + 1) {
            return -1;
        }
        else {
            return choice - 1;
        }
    }
    else {
        system("CLS");
        // Display the products and additional options to the user
        cout << "Select Particular Product" << endl;
        for (int i = 0; i < list; i++) {
            displayProductName(P[i].productName, i + 1);
        }
        cout << "   " << std::right << setw(2) << list + 1 << ") Go back to previous menu" << endl;
        cout << "   " << std::right << setw(2) << list + 2 << ") Display previous product list" << endl;
        cout << "   " << std::right << setw(2) << list + 3 << ") Display next product list" << endl;
        cout << "CHOOSE AN OPTION FROM [ " << 1 << " - " << list + 3 << " ] AND PRESS 'ENTER': ";
        choice = enterCorrectIntValue();

        // Ensure the user makes a valid choice
        while (choice < 1 || choice > list + 3) {
            cout << "Wrong selection. Please enter correct selection: ";
            choice = enterCorrectIntValue();
        }

        // Return the selected product index
        if (choice <= list) { return choice - 1; }
        else if (choice == list + 1) {
            return -1;
        }
        // Handle the option to display the previous product list
        else if (choice == list + 2) {
            if (originIndex == 0) {
                cout << "No previous product list.\nPlease choose another option: ";
                choice = enterCorrectIntValue();
                while (choice < 1 || choice > list + 3 || choice == list + 2) {
                    cout << "Wrong selection. Please enter correct selection: ";
                    choice = enterCorrectIntValue();
                }
                if (choice == list + 3) {
                    index = getProductFromFile(originIndex, index, P, list);
                }
                else if (choice == list + 1) {
                    return -1;
                }
                else {
                    return choice - 1;
                }
            }
            else {
                index = getProductFromFile(oldIndex, originIndex - 20, P, 0);
            }
        }        
        // Handle the option to display the next product list
        else if (choice == list + 3) {
            index = getProductFromFile(originIndex, index, P, list);
        }
    }
    // Return the current index
    return index;
}

//---------------------------------------------------------------------
// Function: sortRequestByPriority
// Description: Function to sort requests by priority using separate files for each priority level
// Space Complexity: O(6n) where n is the number of records in the request file
// Implementation: Reads the request file, writes requests to separate files based on priority, merges the sorted files into a temporary file, and replaces the original file with the sorted temporary file
//---------------------------------------------------------------------
void sortRequestByPriority() {
    // Create file names for different priority levels
    const string PRIORITY_FILES[] = {
        "priority_1.dat",
        "priority_2.dat",
        "priority_3.dat",
        "priority_4.dat",
        "priority_5.dat"
    };

    // Open the original file for reading
    ifstream inFile(REQUEST_FILE, ios::binary);
    if (!inFile.is_open()) {
        cout << "Unable to open request file for reading!" << endl;
        return;
    }

    // Open separate files for writing based on priority
    ofstream outFiles[5];
    for (int i = 0; i < 5; ++i) {
        outFiles[i].open(PRIORITY_FILES[i], ios::binary);
        if (!outFiles[i].is_open()) {
            cout << "Unable to open temporary file for writing: " << PRIORITY_FILES[i] << endl;
            inFile.close();
            return;
        }
    }

    // Read requests and write to corresponding priority file
    Request request;
    while (inFile.read(reinterpret_cast<char*>(&request), sizeof(Request))) {
        int priority = atoi(request.priority);
        if (priority >= 1 && priority <= 5) {
            // Write to the file corresponding to the priority
            outFiles[5 - priority].write(reinterpret_cast<char*>(&request), sizeof(Request));
        }
    }

    inFile.close();
    for (int i = 0; i < 5; ++i) {
        outFiles[i].close();
    }

    // Create temporary file for sorted output
    const string TEMP_FILE = "sorted_requests.dat";
    ofstream sortedFile(TEMP_FILE, ios::binary);
    if (!sortedFile.is_open()) {
        cout << "Unable to open temporary file for writing sorted data!" << endl;
        return;
    }

    // Merge sorted priority files into the temporary file
    for (int i = 0; i < 5 ; ++i) {
        ifstream tempFile(PRIORITY_FILES[i], ios::binary);
        if (tempFile.is_open()) {
            while (tempFile.read(reinterpret_cast<char*>(&request), sizeof(Request))) {
                sortedFile.write(reinterpret_cast<char*>(&request), sizeof(Request));
            }
            tempFile.close();
            remove(PRIORITY_FILES[i].c_str());
        }
    }

    sortedFile.close();

    // Replace the original file with the sorted temporary file
    if (remove(REQUEST_FILE.c_str()) != 0) {
        cout << "Error deleting original request file!" << endl;
        return;
    }
    if (rename(TEMP_FILE.c_str(), REQUEST_FILE.c_str()) != 0) {
        cout << "Error renaming temporary file to request file!" << endl;
        return;
    }

    cout << "Requests sorted by priority successfully!" << endl;
}

//---------------------------------------------------------------------
// Function: enterCorrectIntValue
// Description: Prompts the user to enter a valid integer value
// Space Complexity: O(1)
// Implementation: Continuously prompts the user until a valid integer is entered
//---------------------------------------------------------------------
int enterCorrectIntValue() {
    string input;
    cin >> input;
    int num = atoi(input.c_str());
    while (num <= 0){
        cout << "Invalid enter value. Please enter only numbers and try again: ";
        cin >> input;
        num = atoi(input.c_str());
    }
    return num;
}

//---------------------------------------------------------------------
// Function: readCustomerInfo
// Description: Reads customer information from a binary file at the specified index
// Space Complexity: O(1)
// Implementation: Opens the customer file in binary read mode, reads each Customer object until the specified index is reached, and returns the Customer object
//---------------------------------------------------------------------
Customer readCustomerInfo(int index) {
    ifstream inFile(CUSTOMER_FILE, ios::binary);  // Open the product file in binary read mode
    int i = 0;
    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open file for reading!" << endl;
        exit(0);
    }
    Customer customer;
    // Continue until the end of the file
    while (inFile.peek() != EOF) {
        inFile.read(customer.name, sizeof(customer.name));                // Read the customer name field
        inFile.read(customer.phoneNumber, sizeof(customer.phoneNumber));          // Read the customer phone number field
        inFile.read(customer.email, sizeof(customer.email));          // Read the customer email field

        // Check if pointer reach the index
        if (i == index) { break; } // Exit the loop if the keyword is found
        i++;
    }

    inFile.close(); // Close the file after reading

    return customer;
}

//---------------------------------------------------------------------
// Function: readEmployeeInfo
// Description: Reads employee information from a binary file at the specified index
// Space Complexity: O(1)
// Implementation: Opens the employee file in binary read mode, reads each Employee object until the specified index is reached, and returns the Employee object
//---------------------------------------------------------------------
Employee readEmployeeInfo(int index) {
    ifstream inFile(EMPLOYEE_FILE, ios::binary);  // Open the product file in binary read mode
    int i = 0;
    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open file for reading!" << endl;
        exit(0);
    }
    Employee employee;
    // Continue until the end of the file
    while (inFile.peek() != EOF) {
        inFile.read(employee.name, sizeof(employee.name));                // Read the employee name field
        inFile.read(employee.phoneNumber, sizeof(employee.phoneNumber));          // Read the employee phone number field
        inFile.read(employee.email, sizeof(employee.email));          // Read the employee email field
        inFile.read(employee.department, sizeof(employee.department));          // Read the employee department field

        // Check if pointer reach the index
        if (i == index) { break; } // Exit the loop if the keyword is found
        i++;
    }

    inFile.close(); // Close the file after reading

    return employee;
}

//---------------------------------------------------------------------
// Function: readRequestInfo
// Description: Reads request information from a binary file based on a keyword
// Space Complexity: O(1) 
// Implementation: Opens the request file in binary read mode, reads each Request object, checks if any field contains the keyword, and returns the matching Request object
//---------------------------------------------------------------------
Request readRequestInfo(const std::string& keyword) {
    ifstream inFile(REQUEST_FILE, ios::binary);  // Open the request file in binary read mode
    int index = 0;
    bool found = false;
    Request request;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        cout << "Unable to open file for reading!" << endl;
        return request;
    }

    // Continue until the end of the file
    while (inFile.peek() != EOF) {

        readFileByRequest(inFile, request);
        // Check if any field contains the keyword
        if (!strcmp(request.phoneNumber, keyword.c_str()) ||
            !strcmp(request.releaseId, keyword.c_str()) ||
            !strcmp(request.changeId, keyword.c_str()) ||
            !strcmp(request.description, keyword.c_str()) ||
            !strcmp(request.priority, keyword.c_str()) ||
            !strcmp(request.date, keyword.c_str()) ||
            !strcmp(request.anticipatedReleaseId, keyword.c_str()) ||
            !strcmp(request.state, keyword.c_str())||
            !strcmp(request.productName, keyword.c_str())) {
            found = true;
            break; // Exit the loop if the keyword is found
        }
        index++;
    }

    inFile.close(); // Close the file after reading
    if (found) { return request; }
    else {
        Request R;
        return R;
    }
}

//---------------------------------------------------------------------
// Function: enterYesOrNo
// Description: Auxillary function to enter Y or N
// Space Complexity : O(1)
// Implementation: enter Y or N
//---------------------------------------------------------------------
bool enterYesOrNo() {
    char input;
    cin >> input;
    // when user not enter Y or N, ask user enter again
    while (input != 'Y' && input != 'y' && input != 'N' && input != 'n') {
        cout << "Please enter correct options (Y/N): ";
        cin >> input;
    }
    if (input == 'Y' || input == 'y') {
        return true;
    }
    return false;
}


//---------------------------------------------------------------------
// Function: selectRelease
// Description: Auxillary function to select release
// Space Complexity : O(n)
// Implementation: select release and return
//---------------------------------------------------------------------
Product selectRelease(char* productName) {
    Product P[20];  // Array to store up to 20 Product objects
    int index = 0;  // Index for the array

    // Retrieves product information from a file and updates the index
    index = getProductReleaseFromFile(0, index, P, 0, productName);

    // Checks if the file read operation was unsuccessful
    if (index == -1) {
        // Returns an empty Product object if there was an error reading the file
        return Product();
    }

    // Returns the selected Product object from the array
    return P[index];
}

//---------------------------------------------------------------------
// Function: getProductReleaseFromFile
// Description: Retrieves product information from a file and handles pagination for displaying products
// Space Complexity: O(1)
// Implementation: Displays 20 releases at a time, handles user input for navigating release lists
//---------------------------------------------------------------------
int getProductReleaseFromFile(int oldIndex, int index, Product* P, int storeList, char* productName) {
    // Display 20 releases at a time
    ifstream inFile(PRODUCT_FILE, ios::binary | ios::in);  // Open the product file in binary read mode
    int originIndex = index;

    // Check if the file is successfully opened
    if (!inFile.is_open()) {
        // If the file cannot be opened, display an error message and exit the program
        cout << "Unable to open file for reading!" << endl;
        exit(0);
    }

    int list = 0;
    int i = 0;

    // Read product releases from the file until 20 releases are read or the end of file is reached
    while (list < 20 && inFile.peek() != EOF) {
        Product product;
        readFileByProduct(inFile,product);
        // Check if the product release is empty
        if (!strcmp(product.productName, productName) && product.productRelease[0] != '\0') {
            // If the current index matches the index to start reading from
            if (i == index) {
                // Copy the product name to the list and update the index
                strcpy(P[list].productName, product.productName);
                strcpy(P[list].productRelease, product.productRelease);
                index++;
                list++;
            }
            i++;
        }
    }
    inFile.close(); // Close the file after reading

    int choice;

    // Check if no new releases were read
    if (index == originIndex) {
        cout << "No next release list.\nPlease choose another option: ";
        choice = enterCorrectIntValue();

        // Ensure the user makes a valid choice
        while (choice < 1 || choice > storeList + 2) {
            cout << "Wrong selection. Please enter correct selection: ";
            choice = enterCorrectIntValue();
        }

        // Handle the option to display the previous release list
        if (choice == storeList + 2) {
            if (oldIndex == 0) {
                cout << "No previous release list.\nPlease choose another option: ";
                choice = enterCorrectIntValue();
                while (choice < 1 || choice >= storeList + 2) {
                    cout << "Wrong selection. Please enter correct selection: ";
                    choice = enterCorrectIntValue();
                }
                if (choice == storeList + 1) {
                    return -1;
                }
                else {
                    return choice - 1;
                }
            }
            else {
                index = getProductReleaseFromFile(oldIndex, originIndex - 20 - storeList, P, 0, productName);
            }
        }
        else if (choice == storeList + 1) {
            return -1;
        }
        else {
            return choice - 1;
        }
    }
    else {
        system("CLS");
        // Display the releases and additional options to the user
        cout << "Select Product Release" << endl;
        for (int i = 0; i < list; i++) {
            cout << "   " << std::right << setw(2) << i + 1 << ") " << P[i].productRelease << endl;
        }
        cout << "   " << std::right << setw(2) << list + 1 << ") Go back to previous menu" << endl;
        cout << "   " << std::right << setw(2) << list + 2 << ") Display previous release list" << endl;
        cout << "   " << std::right << setw(2) << list + 3 << ") Display next release list" << endl;
        cout << "CHOOSE AN OPTION FROM [ " << 1 << " - " << list + 3 << " ] AND PRESS 'ENTER': ";
        choice = enterCorrectIntValue();

        // Ensure the user makes a valid choice
        while (choice < 1 || choice > list + 3) {
            cout << "Wrong selection. Please enter correct selection: ";
            choice = enterCorrectIntValue();
        }
        // Return the selected release index
        if (choice <= list) { return choice - 1; }
        else if (choice == list + 1) {
            return -1;
        }
        // Handle the option to display the previous release list
        else if (choice == list + 2) {
            if (originIndex == 0) {
                cout << "No previous release list.\nPlease choose another option: ";
                choice = enterCorrectIntValue();
                while (choice < 1 || choice > list + 3 || choice == list + 2) {
                    cout << "Wrong selection. Please enter correct selection: ";
                    choice = enterCorrectIntValue();
                }
                if (choice == list + 3) {
                    index = getProductReleaseFromFile(originIndex, index, P, list, productName);
                }
                else if (choice == list + 1) {
                    return -1;
                }
                else {
                    return choice - 1;
                }
            }
            else {
                index = getProductReleaseFromFile(oldIndex, originIndex - 20, P, 0, productName);
            }
        }
        // Handle the option to display the next release list
        else if (choice == list + 3) {
            index = getProductReleaseFromFile(originIndex, index, P, list, productName);
        }
    }
    // Return the current index
    return index;
}

//---------------------------------------------------------------------
// Function: readCounter
// Description: Reads the current counter value from a file.
// Space Complexity: O(1)
// Implementation: Open the file in binary mode, read the integer counter, and close the file.
//---------------------------------------------------------------------

int readCounter() {
    ifstream inFile(COUNTER_FILE, ios::binary);
    int counter = 0;
    if (inFile.is_open()) {
        inFile.read(reinterpret_cast<char*>(&counter), sizeof(counter));
        inFile.close();
    }
    return counter;
}

//---------------------------------------------------------------------
// Function: writeCounter
// Description: Writes the updated counter value to a file.
// Space Complexity: O(1)
// Implementation: Open the file in binary and truncate mode, then write the integer counter.
//---------------------------------------------------------------------
void writeCounter(int counter) {
    ofstream outFile(COUNTER_FILE, ios::binary | ios::trunc);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(&counter), sizeof(counter));
        outFile.close();
    }
}

//---------------------------------------------------------------------
// Function: generateSequentialChangeID
// Description: Generates a sequentially incremented change ID based on a counter.
// Space Complexity: O(1)
// Implementation: Read the current counter, increment it, and write it back.
//---------------------------------------------------------------------
string generateSequentialChangeID() {
    int counter = readCounter();
    counter++;

    ostringstream idStream;
    idStream << setw(6) << setfill('0') << counter;

    writeCounter(counter);

    return idStream.str();
}
//---------------------------------------------------------------------
// Function: getCurrentDate
// Description: Returns the current date in YYYY-MM-DD format.
// Space Complexity: O(1)
// Implementation: Use time and localtime to get current date and format it.
//---------------------------------------------------------------------

string getCurrentDate() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    ostringstream dateStream;
    dateStream << (now->tm_year + 1900) << '-'
               << setfill('0') << setw(2) << (now->tm_mon + 1) << '-'
               << setfill('0') << setw(2) << now->tm_mday;
    return dateStream.str();
}

//---------------------------------------------------------------------
// Function: checkFileExist
// Description:  check whether such file exist
// Space Complexity: O(1)
// Implementation: Check whether file exist, If file exist, it will return false;
//---------------------------------------------------------------------
bool checkFileExist(string fileName) {
    ifstream inFile(fileName, ios::binary | ios::in);  // Open file in binary read mode

    if (!inFile.is_open()) {
        // If the file cannot be opened, display an error message and return false;
        return false;
    }
    return true;
}
