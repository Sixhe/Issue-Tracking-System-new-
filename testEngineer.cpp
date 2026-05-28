/*
 * testEngineer.cpp
 *
 * Revision History:
 * - 2024-07-08: Initial implementation
 * - 2024-07-14: Fixed bugs
 * - 2024-07-15: Added comments
 *
 * Description:
 * This file will be test multiple aspects on function createproduct from engineer.cpp.
 * Branch coverage: 4.16%
 */

#include "Engineer.h"
#include "FileHandler.h"

#include <cassert>
using namespace std;

//---------------------------------------------------------------------
// Helper function to set up input and capture output
// 
// Type: Functional Test
// Pre-conditions: None
// Steps:
// 1. Redirect standard input to simulate user input.
// 2. Redirect standard output to capture function output.
// 3. Call the createProduct function.
// 4. Restore standard input and output.
// 5. Return the captured output.
// 
//
//---------------------------------------------------------------------

// Helper function to set up input and capture output
string runCreateProduct(const string& inputStr) {
    // Set up the input stream
    istringstream input(inputStr);
    cin.rdbuf(input.rdbuf());

    // Redirect cout to capture output
    ostringstream output;
    streambuf* coutBuf = cout.rdbuf(output.rdbuf());

    // Call the function
    createProduct();

    // Restore the original buffer
    cout.rdbuf(coutBuf);

    return output.str();
}

//---------------------------------------------------------------------
// Test function for createProduct success scenario
// 
// Type: Functional Test
// Pre-conditions: None
// Steps:
// 1. Simulate valid user input "Wizbang".
// 2. Call runCreateProduct to execute the function.
// 3. Compare the actual output with the expected output.
// 4. Verify that the product was written correctly to the file.
//---------------------------------------------------------------------
void testCreateProductSuccess() {
    cout << "Starting testCreateProductSuccess()" << endl;

    string expectedOutput =
        "Enter Product Name (1-12 characters):\n"
        "Success create product!\n";

    string actualOutput = runCreateProduct("Wizbang");

    // Debug output
    cout << "Function output:\n" << actualOutput << endl;
    cout << "Expected output:\n" << expectedOutput << endl;

    // Check the output
    if (actualOutput != expectedOutput) {
        cout << "testCreateProductSuccess failed" << endl;
        cout << "Actual output: " << actualOutput << endl;
        cout << "Expected output: " << expectedOutput << endl;
    }

    assert(actualOutput == expectedOutput && "testCreateProductSuccess failed");

    // Read the product back from the file
    Product readBackProduct;
    ifstream inFile("products.dat", ios::binary);
    assert(inFile && "Failed to open products.dat for reading");
    inFile.read(reinterpret_cast<char*>(&readBackProduct), sizeof(Product));
    inFile.close();

    // Expected values
    const char* expectedProductName = "Wizbang";

    // Check the contents
    assert(strcmp(readBackProduct.productName, expectedProductName) == 0 && "Product name mismatch");

    cout << "testCreateProductSuccess passed\n" << endl;
}

//---------------------------------------------------------------------
// Test function for createProduct error scenario: input too long
// 
// Type: Boundary Test
// Pre-conditions: None
// Steps:
// 1. Simulate user input that exceeds the character limit "ThisIsWayTooLongName".
// 2. Simulate valid user input "Wizbang".
// 3. Call runCreateProduct to execute the function.
// 4. Compare the actual output with the expected output.
//---------------------------------------------------------------------
void testCreateProductErrorTooLong() {
    cout << "Starting testCreateProductErrorTooLong()" << endl;

    string expectedOutput =
        "Enter Product Name (1-12 characters):\n"
        "Please enter a valid name with 1-12 characters.\n"
        "Enter Product Name (1-12 characters):\n"
        "Success create product!\n";

    string actualOutput = runCreateProduct("ThisIsWayTooLongName\nWizbang");

    // Debug output
    cout << "Function output:\n" << actualOutput << endl;
    cout << "Expected output:\n" << expectedOutput << endl;

    // Check the output
    if (actualOutput != expectedOutput) {
        cout << "testCreateProductErrorTooLong failed" << endl;
        cout << "Actual output: " << actualOutput << endl;
        cout << "Expected output: " << expectedOutput << endl;
    }

    assert(actualOutput == expectedOutput && "testCreateProductErrorTooLong failed");

    cout << "testCreateProductErrorTooLong passed\n" << endl;
}

//---------------------------------------------------------------------
// Test function for createProduct error scenario: input with only spaces
// 
// Type: Boundary Test
// Pre-conditions: None
// Steps:
// 1. Simulate user input that contains only spaces.
// 2. Simulate valid user input "Wizbang".
// 3. Call runCreateProduct to execute the function.
// 4. Compare the actual output with the expected output.
//---------------------------------------------------------------------
void testCreateProductErrorSpace() {
    cout << "Starting testCreateProductErrorSpace()" << endl;

    string expectedOutput =
        "Enter Product Name (1-12 characters):\n"
        "Please enter a valid name with 1-12 characters.\n"
        "Enter Product Name (1-12 characters):\n"
        "Success create product!\n";

    string actualOutput = runCreateProduct("            \nWizbang\n");

    // Debug output
    cout << "Function output:\n" << actualOutput << endl;
    cout << "Expected output:\n" << expectedOutput << endl;

    // Check the output
    assert(actualOutput == expectedOutput && "testCreateProductErrorSpace failed");

    cout << "testCreateProductErrorSpace passed" << endl;
}

int main() {
    testCreateProductSuccess();
    testCreateProductErrorTooLong();
    testCreateProductErrorSpace();
    return 0;
}
