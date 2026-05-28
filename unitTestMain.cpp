/*
 * unitTestMain.cpp
 *
 * Revision History:
 * - 2024-06-27: Initial implementation
 *
 * Description:
 * This file would unit test one or several of the functions in one of header files.
 * the Issue Tracking System (ITS) application. It includes functions for creating and managing
 * product releases, change items, and generating reports.
 */

#include <iostream>
#include "mainUI.h"
#include "Customer.h"
#include "Employee.h"
#include "Engineer.h"

using namespace std;

// unit test for mainUI.h
int main() {
	//Function Name: displayMainMenuUI()
 	//Preconditions: none
  	//Expected results：function will display main menu correctly
	cout "test function: displayMainMenuUI()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		displayMainMenuUI();
	}
	//Function Name: displayCustomerMenuUI()
 	//Preconditions: none
  	//Expected results：function will display main menu correctly
	cout "test function: displayCustomerMenuUI()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		displayCustomerMenuUI();
	}
	//Function Name: displayEmployeeMenuUI()
 	//Preconditions: none
  	//Expected results：function will display main menu correctly
	cout "test function: displayEmployeeMenuUI()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		displayEmployeeMenuUI();
	}
	//Function Name: displayEngineerMenuUI()
 	//Preconditions: none
  	//Expected results：function will display main menu correctly
	cout "test function: displayEngineerMenuUI()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		displayEngineerMenuUI();
	}
}


// unit test for Customer.h
/*
int main() {
	//Function Name: enterCustomerPhoneNumber()
 	//Preconditions: user enter '7789994556'
  	//Expected results：function return '7789994556' and function will display 'Test successed'
	cout "test function: enterCustomerPhoneNumber()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterCustomerPhoneNumber() == "7789994556"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}

int main() {
	//Function Name:enterCustomerName()
 	//Preconditions: user enter 'Test Name'
  	//Expected results：function return 'Test Name' and function will display 'Test successed'
	cout "test function: enterCustomerName()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterCustomerName() == "Test Name"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}

int main() {
	//Function Name:enterCustomerEmail()
 	//Preconditions: user enter 'test.email@gmail.com'
  	//Expected results：function return 'test.email@gmail.com' and function will display 'Test successed'
	cout "test function: enterCustomerEmail()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterCustomerEmail() == "test.email@gmail.com"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}

int main() {
	//Function Name:enterCustomerDescription()
 	//Preconditions: user enter 'test description'
  	//Expected results：function return 'test description' and function will display 'Test successed'
	cout "test function: enterCustomerDescription()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterCustomerDescription() == "test description"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}
 */

// unit test for Employee.h
/*
int main() {
	//Function Name: enterEmployeePhoneNumber()
 	//Preconditions: user enter '7789994556'
  	//Expected results：function return '7789994556' and function will display 'Test successed'
	cout "test function: enterEmployeePhoneNumber()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterEmployeePhoneNumber() == "7789994556"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}

int main() {
	//Function Name:enterEmployeeName()
 	//Preconditions: user enter 'Test Name'
  	//Expected results：function return 'Test Name' and function will display 'Test successed'
	cout "test function: enterEmployeeName()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterEmployeeName() == "Test Name"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}

int main() {
	//Function Name:enterEmployeeEmail()
 	//Preconditions: user enter 'test.email@gmail.com'
  	//Expected results：function return 'test.email@gmail.com' and function will display 'Test successed'
	cout "test function: enterEmployeeEmail()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterEmployeeEmail() == "test.email@gmail.com"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}

int main() {
	//Function Name:enterEmployeeDescription()
 	//Preconditions: user enter 'test description'
  	//Expected results：function return 'test description' and function will display 'Test successed'
	cout "test function: enterEmployeeDescription()" << endl << "Press any keys to test" << endl;
 	if (kbhit()) {
		if(enterEmployeeDescription() == "test description"){
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}
 */

// unit test for Engineer.h
/*
int main() {
	//Function Name: GenerateReport1()
 	//Preconditions: none
  	//Expected results：function will display report 1 correctly, like User Manual section 4.9
	cout "test function: GenerateReport1()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		GenerateReport1();
	}
}
int main() {
	//Function Name: GenerateReport2()
 	//Preconditions: none
  	//Expected results：function will display report 2 correctly, like User Manual section 4.8
	cout "test function: GenerateReport2()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		GenerateReport2();
	}
}
int main() {
	//Function Name: QueryChangeItems()
 	//Preconditions: none
  	//Expected results：function will display change item list correctly, like User Manual section 4.4
	cout "test function: QueryChangeItems()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		QueryChangeItems();
	}
}
int main() {
	//Function Name: selectProduct()
 	//Preconditions: user enter 'Product F'
  	//Expected results：function will return 'Product F' and function will display 'Test successed'
	cout "test function: selectProduct()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		if(selectProduct() == 'Product F')
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}
int main() {
	//Function Name: selectChangeItem()
 	//Preconditions: user enter 1
  	//Expected results：function will return 1 and function will display 'Test successed'
	cout "test function: selectChangeItem()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		if(selectChangeItem() == 1)
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}
int main() {
	//Function Name: selectRelease()
 	//Preconditions: user enter 1
  	//Expected results：function will return 1 and function will display 'Test successed'
	cout "test function: selectRelease()" << endl << "Press any keys to test" << endl;
	if (kbhit()) {
		if(selectRelease() == 1)
  			cout << "Test successed" << endl;
  		}
    		else{
      			cout << "Test Failed" << endl;
      		}
	}
}
 */
