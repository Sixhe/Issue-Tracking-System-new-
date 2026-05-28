/*
 * Engineer.cpp
 *
 * Revision History:
 * - 2024-07-09: Initial implementation
 * - 2024-07-11: Create and delete some functions
 * - 2024-07-15: Fixed some bugs
 * - 2024-07-16: Comment updated
 * - 2024-07-24: fixed createProductRelease bug
 * - 2024-07-26: fixed select bug
 * - 2024-07-28: fixed updateChangeItem bug
 * - 2024-07-30: add no file eixst detection
 *
 * Description:
 * This file contains the declarations for functions that handle engineer-related operations in
 * the Issue Tracking System (ITS) application. It includes functions for creating and managing
 * product releases, change items, and generating reports.
 * 
 * Discussion:
 * 		Memory Usage:
 * 			Static Allocation: Fixed-size arrays, such as Request R[20] and Product P[20], are used in 
 * 				functions to read a predefined number of items (e.g., getPreviousReleaseFromFile, getNextReleaseFromFile). 
 * 				This approach ensures predictable memory usage and simple memory management but can lead to wasted space 
 * 				if fewer than 20 items are needed.
 * 			In-Memory Data Structures: Storing large amounts of data in memory (e.g., reading 20 change items or product 
 * 				releases) lead to high memory usage but it is under the minimum hardware requirement.
 * 		Speed and Time Efficiency:
 * 			Sequential Reading: Functions that read or write data sequentially (getPreviousReleaseFromFile, 
 * 				getNextReleaseFromFile) seems slow for large datasets. However, sequential access is simple for implementation
 * 				and debug under limit project time.
 * 		Complexity and Design Choices:
 * 			Error Handling: Robust error handling for file I/O and user input (e.g., enterYesOrNo, enterChange) is crucial.
 * 				Functions handle errors gracefully, providing meaningful feedback on screen and ensuring the system remains
 * 				in a consistent state.
 * 			Validation: Ensuring that user inputs and data read from files are valid is essential to prevent errors and 
 * 				maintain data integrity.
 */

// Inlude Header File
#include "Engineer.h"

// Define constants for the file names
const string REQUEST_FILE = "requests.dat";
const string PRODUCT_FILE = "products.dat";
const string EMPLOYEE_FILE = "employees.dat";
const string CUSTOMER_FILE = "customers.dat";

//---------------------------------------------------------------------
// Function: createProductRelease
// Description: Function to create product release
// Space Complexity : O(n)
// Implementation: select product name, enter release id
//---------------------------------------------------------------------
void createProductRelease() {
	try {
		// Check if file exist.If file not exist, end function
		if (!checkFileExist(PRODUCT_FILE)) {
			cout << "No product exist. Please create product first!" << endl;
			return;
		}
		Product P; // Value to store enter value
		bool check = false; // Value for check whether enter is wrong
		int i = 0; // Value for while loop
		string input; // Value for cin

		P = selectProduct(); // get product selection information
		if (P.productName[0] == '\0') { return; } // When product name is empty, end function
		cout << "Enter Release ID (6 digits): ";
		cin.ignore();
		getline(cin, input);
		// eheck whether release exist, of exist ask user enter again
		while (searchRelease(P.productName, input) != -1) {
			cout << "Release exist. Please enter another release id: ";
			getline(cin, input);
		}
		// check length of input value
		if (input.length() != 6) {
			check = true;
		}
		else {
			input.copy(P.productRelease, 6, 0);
			// loop for check whether input value is digit
			while (i != 6) {
				if (!isdigit(P.productRelease[i])) {
					check = true;
				}
				i++;
			}
		}
		// When input value length equal to 6, but value is not digit
		// ask user enter again
		while (input.length() != 6 || check) {
			check = false;
			cout << "Please enter a valid Release ID with exactly 6 digits.\nEnter Release ID (6 digits): ";
			getline(cin, input);
			// eheck whether release exist, of exist ask user enter again
			while (searchRelease(P.productName, input) != -1) {
				cout << "Release exist. Please enter another release id: ";
				getline(cin, input);
			}
			input.copy(P.productRelease, 6, 0);
			int j = 0;
			// loop for check whether input value is digit
			while (j != 6) {
				if (!isdigit(P.productRelease[j])) {
					check = true;
				}
				j++;
			}
		}
		input.copy(P.productRelease, 6, 0);
		insertProduct(P);
		cout << "Success create product release!" << endl;
	}
	catch (const invalid_argument& e) {
		cout << "Error: " << e.what() << "\n";
		cout << "Returning to main menu.\n";
	}
	catch (...) {
		cout << "An unexpected error occurred. Returning to main menu.\n";
	}
}

//---------------------------------------------------------------------
// Function: createProduct
// Description: Function to create product
// Space Complexity : O(1)
// Implementation: enter product name
//---------------------------------------------------------------------
void createProduct() {
	try {
		Product P; // Value to store enter value
		string input; // Value for cin

		cout << "Enter Product Name (1-12 characters): ";
		cin.ignore();
		getline(cin, input);
		// loop for check whether input value meet requirement
		while (input.length() > 12 || input.length() < 1) {
			cout << "Please enter a valid name with 1-12 characters.\nEnter Product Name (1-12 characters): ";
			getline(cin, input);
		}
		input.copy(P.productName, input.length(), 0);
		if (checkFileExist("PRODUCT_FILE")) {
			// loop for check whether product name exit
			while (searchProduct(P.productName) != -1) {
				cout << "Product exist. Please enter another product name: ";
				getline(cin, input);
				// loop for check whether input value meet requirement
				while (input.length() > 12 || input.length() < 1) {
					cout << "Please enter a valid name with 1-12 characters.\nEnter Product Name (1-12 characters): ";
					getline(cin, input);
				}
				input.copy(P.productName, input.length(), 0);
			}
		}
		P.productRelease[0] = '\0';
		P.productName[input.length()] = '\0';
		insertProduct(P);
		cout << "Success create product!" << endl;
	}
	catch (const invalid_argument& e) {
		cout << "Error: " << e.what() << "\n";
		cout << "Returning to main menu.\n";
	}
	catch (...) {
		cout << "An unexpected error occurred. Returning to main menu.\n";
	}
}

//---------------------------------------------------------------------
// Function: generateReport1
// Description: Function to generate all not done change item lists report
// Space Complexity : O(1)
// Implementation: select product name, display report
//---------------------------------------------------------------------
void generateReport1() {
	try {
		// Check if file exist.If file not exist, end function
		if (!checkFileExist(PRODUCT_FILE)) {
			cout << "No product exist. Please create product first!" << endl;
			return;
		}

		cout << "Issue Tracking System - Generate Report-#1" << endl;
		Product P = selectProduct(); // get product selection information
		if (P.productName[0] == '\0') { return; } // When product name is empty, end function

		// Check if file exist.If file not exist, end function
		if (!checkFileExist(REQUEST_FILE)) {
			cout << "No request exist. Please create request first!" << endl;
			return;
		}

		if (searchRequest(P.productName) == -1) { return; }
		cout << "Success generates report list!" << endl;
		cout << "List of all not done change items - " << P.productName << endl;
		displayAllNotDoneChangeItem(P.productName); // display report
	}
	catch (const invalid_argument& e) {
		cout << "Error: " << e.what() << "\n";
		cout << "Returning to main menu.\n";
	}
	catch (...) {
		cout << "An unexpected error occurred. Returning to main menu.\n";
	}
}

//---------------------------------------------------------------------
// Function: generateReport2
// Description: Function to generate particulat change item information
// Space Complexity : O(1)
// Implementation: select product name, select change item, display report
//---------------------------------------------------------------------
void generateReport2() {
	try {
		// Check if file exist.If file not exist, end function
		if (!checkFileExist(PRODUCT_FILE)) {
			cout << "No product exist. Please create product first!" << endl;
			return;
		}

		cout << "Issue Tracking System - Generate Report-#2" << endl;
		Product P = selectProduct(); // get product selection information
		if (P.productName[0] == '\0') { return; } // When product name is empty, end function

		// Check if file exist.If file not exist, end function
		if (!checkFileExist(REQUEST_FILE)) {
			cout << "No request exist. Please create request first!" << endl;
			return;
		}

		cout << "Issue Tracking System - Generate Report-#2" << endl;
		Request R = selectFromAllChangeItem(P.productName); // get change item selection information
		if (R.changeId[0] == '\0') { return; } // When change id is empty, end function
		cout << "Issue Tracking System - Generate Report-#2" << endl;
		char select[7]; // Value to store release id
		strcpy(select, selectRelease(R.productName).productRelease); 
		if (select[0] == '\0') { return; }// When value is empty, end function 
		else { strcpy(R.releaseId, select); }

		cout << "Enter Report Description (1-30 characters): ";
		string eDes;
		cin.ignore();
		getline(cin, eDes);
		// loop for check whether input value meet requirement
		while (eDes.length() > 30 || eDes.length() < 1) {
			cout << "Please enter a valid description with 1-30 characters.\nEnter Report Description (1-30 characters): ";
			getline(cin, eDes);
		}

		Customer C;
		Employee E;
		int index = 0;

		if (!checkFileExist(CUSTOMER_FILE)) { readEmployeeInfo(searchEmployee(R.phoneNumber)); }
		else if (!checkFileExist(EMPLOYEE_FILE)) { 
			readCustomerInfo(searchCustomer(R.phoneNumber)); 
			index = -1;
		}
		else {
			// search whether customer exist
			index = searchCustomer(R.phoneNumber);
			// If exist, read it
			if (index != -1) { C = readCustomerInfo(index); }
			// If not exist, read employee
			else { E = readEmployeeInfo(searchEmployee(R.phoneNumber)); }
		}
		

		strcpy(R.state, "Reported");
		modifyRequest(R);
		system("CLS");
		cout << "Success generates report!\n" << endl;

		cout << "Report of the change item\n" << endl;
		cout << "State: " << R.state << endl;
		cout << "Change ID: " << R.changeId << endl;
		cout << "Release ID: " << R.releaseId << endl;
		cout << "Date: " << R.date << endl;
		if (index != -1) {
			cout << "Customer name: " << C.name << endl;
			cout << "Customer phone number: " << C.phoneNumber << endl;
			cout << "Customer email: " << C.email << endl;
		}
		else {
			cout << "Employee name: " << E.name << endl;
			cout << "Employee phone number: " << E.phoneNumber << endl;
			cout << "Employee email: " << E.email << endl;
			cout << "Employee department: " << E.department << endl;
		}
		cout << "Description: " << R.description << endl;
		cout << "Engineer Description: " << eDes << endl;
	}
	catch (const invalid_argument& e) {
		cout << "Error: " << e.what() << "\n";
		cout << "Returning to main menu.\n";
	}
	catch (...) {
		cout << "An unexpected error occurred. Returning to main menu.\n";
	}
}

//---------------------------------------------------------------------
// Function: enterChange
// Description: Auxillary function to enter change of one change item
// Space Complexity : O(1)
// Implementation: enter state, enter description, 
//				   enter anticipated release id, enter priority
//---------------------------------------------------------------------
void enterChange(Request& R) {
	string input;
	cout << "Update Change Item '" << R.productName << " - Change ID: "  << R.changeId << "'" << endl;

	cout << "Do you want to change state (Y/N)? ";
	if (enterYesOrNo()) {
		cout << "Old State: " << R.state << "\nNew State: ";
		cin.clear();
		cin.ignore();
		getline(cin, input);
		// When user enter invalid value, ask user enter again
		while (input != "Done" && input != "Cancelled" && input != "Assessed" && input != "InProgress") {
			cout << "State must be Done/Cancelled/Assessed/InProgress Only.\nNew State: ";
			cin.clear();
			getline(cin, input);
		}
		input.copy(R.state, input.length(), 0);
		R.state[input.length()] = '\0';

	}

	cout << "Do you want to change description (Y/N)? ";
	if (enterYesOrNo()) {
		cout << "Old Description: " << R.description << "\nNew Description: ";
		cin.clear();
		cin.ignore();
		getline(cin, input);
		// When user enter invalid value, ask user enter again
		while (input.length() > 30 || input.length() < 1) {
			cout << "Please enter a valid description with 1-30 characters.\nNew Description: ";
			cin.clear();
			getline(cin, input);
		}
		input.copy(R.description, input.length(), 0);
		R.description[input.length()] = '\0';
	}

	cout << "Do you want to change the anticipated release (Y/N)? ";
	if (enterYesOrNo()) {
		int i = 0;
		bool check = false;
		cout << "Old Anticipated Release ID: " << R.anticipatedReleaseId << "\nNew Anticipated Release ID: ";
		cin.clear();
		cin.ignore();
		getline(cin, input);
		if (input.length() != 6) {
			check = true;
		}
		else {
			input.copy(R.anticipatedReleaseId, 6, 0);
			// loop for check whether input value is digit
			while (i != 6) {
				if (!isdigit(R.anticipatedReleaseId[i])) {
					check = true;
				}
				i++;
			}
		}
		// When input value length equal to 6, but value is not digit
		// ask user enter again
		while (input.length() != 6 || check) {
			check = false;
			cout << "Please enter a valid Anticipated Release ID with exactly 6 digits.\nEnter Anticipated Release ID (6 digits): ";
			cin.clear();
			getline(cin, input);
			input.copy(R.anticipatedReleaseId, 6, 0);
			int j = 0;
			// loop for check whether input value is digit
			while (j != 6) {
				if (!isdigit(R.anticipatedReleaseId[j])) {
					check = true;
				}
				j++;
			}
		}
		input.copy(R.anticipatedReleaseId, 6, 0);
		R.anticipatedReleaseId[6] = '\0';
	}

	cout << "Current Priority: " << R.priority << endl;
	cout << "Do you want to change priority (Y/N)? ";
	if (enterYesOrNo()) {
		cout << "Enter new priority [number 1-5]: ";
		int pri;
		pri = enterCorrectIntValue();
		// When user enter invalid value, ask user enter again
		while (pri < 1 || pri > 6) {
			cout << "Priority must be a number between 1 and 5.\nEnter new priority [number 1-5]: ";
			pri = enterCorrectIntValue();
		}
		char output[2];
		snprintf(output, sizeof(2), "%d", pri);
		strcpy(R.priority, output);
	}

	cout << "'" << R.productName << " - Change ID: " << R.changeId << "' has been updated" << endl;
}

//---------------------------------------------------------------------
// Function: updateChangeItem
// Description: Function to update some information in particular change item
// Space Complexity : O(1)
// Implementation: select product name, select change item, collect change info
//---------------------------------------------------------------------
void updateChangeItem() {
	try {
		// Check if file exist.If file not exist, end function
		if (!checkFileExist(PRODUCT_FILE)) {
			cout << "No product exist. Please create product first!" << endl;
			return;
		}

		cout << "Issue Tracking System - Update Change Item" << endl;
		Product P = selectProduct(); // get product selection information
		if (P.productName[0] == '\0') { return; } // When product name is empty, end function

		// Check if file exist.If file not exist, end function
		if (!checkFileExist(REQUEST_FILE)) {
			cout << "No request exist. Please create request first!" << endl;
			return;
		}

		cout << "Issue Tracking System - Update Change Item" << endl;
		if (searchRequest(P.productName) == -1) { return; }
		Request R = selectFromAllChangeItem(P.productName); // get change item selection information
		if (R.changeId[0] == '\0') { return; } // When change id is empty, end function
		system("CLS");
		enterChange(R);
		modifyRequest(R);
	}
	catch (const invalid_argument& e) {
		cout << "Error: " << e.what() << "\n";
		cout << "Returning to main menu.\n";
	}
	catch (...) {
		cout << "An unexpected error occurred. Returning to main menu.\n";
	}
}

//---------------------------------------------------------------------
// Function:  selectFromAllChangeItem
// Description: Auxillary function to select all change items
// Space Complexity : O(n)
// Implementation:  select product name, select change item and return
//---------------------------------------------------------------------
Request selectFromAllChangeItem(char* productName) {
	Request R[20];  // Array to store up to 20 Request objects
	int index = 0;  // Index for the array

	// Retrieves change item information from a file and updates the index
	index = getAllChangeItemFromFile(0, index, R, 0, productName);

	// Checks if the file read operation was unsuccessful
	if (index == -1) {
		// Returns an empty Request object if there was an error reading the file
		return Request();
	}

	// Returns the selected Request object from the array
	return R[index];
}

//---------------------------------------------------------------------
// Function: getAllChangeItemFromFile
// Description: Retrieves change item information from a file and handles pagination for displaying change items
// Space Complexity: O(1)
// Implementation: Displays 20 change items at a time, handles user input for navigating change item lists
//---------------------------------------------------------------------
int getAllChangeItemFromFile(int oldIndex, int index, Request* R, int storeList, char* productName) {
	// Display 20 change items at a time
	ifstream inFile(REQUEST_FILE, ios::binary | ios::in);  // Open the request file in binary read mode
	int originIndex = index;

	// Check if the file is successfully opened
	if (!inFile.is_open()) {
		// If the file cannot be opened, display an error message and exit the program
		cout << "Unable to open file for reading!" << endl;
		exit(0);
	}

	int list = 0;
	int i = 0;

	// Read change items from the file until 20 releases are read or the end of file is reached
	while (list < 20 && inFile.peek() != EOF) {
		Request request;
		inFile.read(request.phoneNumber, sizeof(request.phoneNumber));                // Read the phone number field
		inFile.read(request.releaseId, sizeof(request.releaseId));                    // Read the release ID field
		inFile.read(request.changeId, sizeof(request.changeId));                      // Read the change ID field
		inFile.read(request.description, sizeof(request.description));                // Read the description field
		inFile.read(request.priority, sizeof(request.priority));                      // Read the priority field
		inFile.read(request.date, sizeof(request.date));                              // Read the date field
		inFile.read(request.anticipatedReleaseId, sizeof(request.anticipatedReleaseId)); // Read the anticipated release ID field
		inFile.read(request.state, sizeof(request.state));                            // Read the state field
		inFile.read(request.productName, sizeof(request.productName));                // Read the product name field
		// Check if the change item is empty
		if (strcmp(request.productName, productName) == 0) {
			// If the current index matches the index to start reading from
			if (i == index) {
				// Copy the product name to the list and update the index
				strcpy(R[list].phoneNumber, request.phoneNumber);
				strcpy(R[list].releaseId, request.releaseId);
				strcpy(R[list].changeId, request.changeId);
				strcpy(R[list].description, request.description);
				strcpy(R[list].priority, request.priority);
				strcpy(R[list].date, request.date);
				strcpy(R[list].anticipatedReleaseId, request.anticipatedReleaseId);
				strcpy(R[list].state, request.state);
				strcpy(R[list].productName, request.productName);
				index++;
				list++;
			}
			i++;
		}
	}
	inFile.close(); // Close the file after reading

	int choice;

	// Check if no new change items were read
	if (index == originIndex) {
		cout << "No next change item list.\nPlease choose another option: ";
		choice = enterCorrectIntValue();

		// Ensure the user makes a valid choice
		while (choice < 1 || choice > storeList + 2) {
			cout << "Wrong selection. Please enter correct selection: ";
			choice = enterCorrectIntValue();
		}

		// Handle the option to display the previous change item list
		if (choice == storeList + 2) {
			if (oldIndex == 0) {
				cout << "No previous change item list.\nPlease choose another option: ";
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
				index = getAllChangeItemFromFile(oldIndex, originIndex - 20 - storeList, R, 0, productName);
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
		// Display the change items and additional options to the user
		cout << "Select Change Item - " << productName << endl;
		cout << "       Change ID State       Priority Date       Release ID Anticipdated Release ID Description" << endl;
		for (int i = 0; i < list; i++) {
			cout << "   " << std::right << setw(2) << i + 1 << ") " << std::left << setw(6) << R[i].changeId << "    "
				<< setw(11) << R[i].state << " " << R[i].priority << "        " 
				<< setw(10) << R[i].date << " " << setw(6) << R[i].releaseId << "     " 
				<< setw(6) << R[i].anticipatedReleaseId << "                  " 
				<< setw(30) << R[i].description << endl;
		}
		cout << "   " << std::right << setw(2) << list + 1 << ") Go back to previous menu" << endl;
		cout << "   " << std::right << setw(2) << list + 2 << ") Display previous change item list" << endl;
		cout << "   " << std::right << setw(2) << list + 3 << ") Display next change item list" << endl;
		cout << "CHOOSE AN OPTION FROM [ " << 1 << " - " << list + 3 << " ] AND PRESS 'ENTER': ";
		choice = enterCorrectIntValue();

		// Ensure the user makes a valid choice
		while (choice < 1 || choice > list + 3) {
			cout << "Wrong selection. Please enter correct selection: ";
			choice = enterCorrectIntValue();
		}
		// Return the selected change item index
		if (choice <= list) { return choice - 1; }
		else if (choice == list + 1) {
			return -1;
		}
		// Handle the option to display the previous change item list
		else if (choice == list + 2) {
			if (originIndex == 0) {
				cout << "No previous change item list.\nPlease choose another option: ";
				choice = enterCorrectIntValue();
				while (choice < 1 || choice > list + 3 || choice == list + 2) {
					cout << "Wrong selection. Please enter correct selection: ";
					choice = enterCorrectIntValue();
				}
				if (choice == list + 3) {
					index = getAllChangeItemFromFile(originIndex, index, R, list, productName);
				}
				else if (choice == list + 1) {
					return -1;
				}
				else {
					return choice - 1;
				}
			}
			else {
				index = getAllChangeItemFromFile(oldIndex, originIndex - 20, R, 0, productName);
			}
		}
		// Handle the option to display the next change item list
		else if (choice == list + 3) {
			index = getAllChangeItemFromFile(originIndex, index, R, list, productName);
		}
	}
	// Return the current index
	return index;
}

//---------------------------------------------------------------------
// Function: displayAllNotDoneChangeItem
// Description: Auxillary function to display all not done change items
// Space Complexity : O(1)
// Implementation: select product, display list
//---------------------------------------------------------------------
void displayAllNotDoneChangeItem(char* productName) {
	Request R[20];  // Array to store up to 20 Request objects

	// Retrieves change item information from a file and updates the index
	getAllNotDoneChangeItemFromFile(0, 0, R, 0, productName);
}

//---------------------------------------------------------------------
// Function: getAllNotDoneChangeItemFromFile
// Description: Retrieves not done change item information from a file and handles pagination for displaying change items
// Space Complexity: O(1)
// Implementation: Displays 20 not done change items at a time, handles user input for navigating change item lists
//---------------------------------------------------------------------
int getAllNotDoneChangeItemFromFile(int oldIndex, int index, Request* R, int storeList, char* productName) {
	// Display 20 change items at a time
	ifstream inFile(REQUEST_FILE, ios::binary | ios::in);  // Open the request file in binary read mode
	int originIndex = index;

	// Check if the file is successfully opened
	if (!inFile.is_open()) {
		// If the file cannot be opened, display an error message and exit the program
		cout << "Unable to open file for reading!" << endl;
		exit(0);
	}

	int list = 0;
	int i = 0;

	// Read change items from the file until 20 releases are read or the end of file is reached
	while (list < 20 && inFile.peek() != EOF) {
		Request request;
		inFile.read(request.phoneNumber, sizeof(request.phoneNumber));                // Read the phone number field
		inFile.read(request.releaseId, sizeof(request.releaseId));                    // Read the release ID field
		inFile.read(request.changeId, sizeof(request.changeId));                      // Read the change ID field
		inFile.read(request.description, sizeof(request.description));                // Read the description field
		inFile.read(request.priority, sizeof(request.priority));                      // Read the priority field
		inFile.read(request.date, sizeof(request.date));                              // Read the date field
		inFile.read(request.anticipatedReleaseId, sizeof(request.anticipatedReleaseId)); // Read the anticipated release ID field
		inFile.read(request.state, sizeof(request.state));                            // Read the state field
		inFile.read(request.productName, sizeof(request.productName));                // Read the product name field
		// Check if the change item is empty
		if (strcmp(request.productName, productName) == 0 && strcmp(request.state, "Done") != 0) {
			// If the current index matches the index to start reading from
			if (i == index) {
				// Copy the product name to the list and update the index
				strcpy(R[list].phoneNumber, request.phoneNumber);
				strcpy(R[list].releaseId, request.releaseId);
				strcpy(R[list].changeId, request.changeId);
				strcpy(R[list].description, request.description);
				strcpy(R[list].priority, request.priority);
				strcpy(R[list].date, request.date);
				strcpy(R[list].anticipatedReleaseId, request.anticipatedReleaseId);
				strcpy(R[list].state, request.state);
				strcpy(R[list].productName, request.productName);
				index++;
				list++;
			}
			i++;
		}
	}
	inFile.close(); // Close the file after reading

	int choice;

	// Check if no new change items were read
	if (index == originIndex) {
		cout << "No next change item list.\nPlease choose another option: ";
		choice = enterCorrectIntValue();

		// Ensure the user makes a valid choice
		while (choice != storeList + 1 && choice != storeList + 2) {
			cout << "Wrong selection. Please enter correct selection: ";
			choice = enterCorrectIntValue();
		}

		// Handle the option to display the previous change item list
		if (choice == storeList + 2) {
			if (oldIndex == 0) {
				cout << "No previous change item list.\nPlease choose another option: ";
				choice = enterCorrectIntValue();
				while (choice != storeList + 1) {
					cout << "Wrong selection. Please enter correct selection: ";
					choice = enterCorrectIntValue();
				}
				if (choice == storeList + 1) {
					return -1;
				}
			}
			else {
				index = getAllNotDoneChangeItemFromFile(oldIndex, originIndex - 20 - storeList, R, 0, productName);
			}
		}
		else if (choice == storeList + 1) {
			return -1;
		}
	}
	else {
		system("CLS");
		// Display the change items and additional options to the user
		cout << "All Not Done Change Item - " << productName << endl;
		cout << "       Change ID State       Priority Date       Release ID Anticipdated Release ID Description" << endl;
		for (int i = 0; i < list; i++) {
			cout << "   " << std::right << setw(2) << i + 1 << ") " << std::left << setw(6) << R[i].changeId << "    "
				<< setw(11) << R[i].state << " " << R[i].priority << "        "
				<< setw(10) << R[i].date << " " << setw(6) << R[i].releaseId << "     "
				<< setw(6) << R[i].anticipatedReleaseId << "                  "
				<< setw(30) << R[i].description << endl;
		}
		cout << "   " << std::right << setw(2) << list + 1 << ") Go back to previous menu" << endl;
		cout << "   " << std::right << setw(2) << list + 2 << ") Display previous not done change item list" << endl;
		cout << "   " << std::right << setw(2) << list + 3 << ") Display next not done change item list" << endl;
		cout << "CHOOSE AN OPTION FROM [ " << list + 1 << " - " << list + 3 << " ] AND PRESS 'ENTER': ";
		choice = enterCorrectIntValue();

		// Ensure the user makes a valid choice
		while (choice < list + 1 || choice > list + 3) {
			cout << "Wrong selection. Please enter correct selection: ";
			choice = enterCorrectIntValue();
		}
		// End function
		if (choice == list + 1) {
			return -1;
		}
		// Handle the option to display the previous change item list
		else if (choice == list + 2) {
			if (originIndex == 0) {
				cout << "No previous change item list.\nPlease choose another option: ";
				choice = enterCorrectIntValue();
				while (choice != list + 1 && choice != list + 3) {
					cout << "Wrong selection. Please enter correct selection: ";
					choice = enterCorrectIntValue();
				}
				if (choice == list + 3) {
					index = getAllNotDoneChangeItemFromFile(originIndex, index, R, list, productName);
				}
				else if (choice == list + 1) {
					return -1;
				}
			}
			else {
				index = getAllNotDoneChangeItemFromFile(oldIndex, originIndex - 20, R, 0, productName);
			}
		}
		// Handle the option to display the next change item list
		else if (choice == list + 3) {
			index = getAllNotDoneChangeItemFromFile(originIndex, index, R, list, productName);
		}
	}
	return -1;
}