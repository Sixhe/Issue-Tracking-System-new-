/*
 * testFileOps.cpp
 *
 * Revision History:
 * - 2024-07-08: Initial implementation
 * - 2024-07-15: Added comments
 *
 * Description:
 * This file unit tests one or more functions in FileHandler.cpp.
 * Branch coverage: 3.7%
 */

#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;


//---------------------------------------------------------------------
// Test function for file operations
// 
// Type: Functional Test
// Pre-conditions: None
// Steps:
// 1. Create `Request` objects with different data.
// 2. Call `insertRequest` function to write `Request` objects to the file.
// 3. Call `readFileByRequest` function to read `Request` objects from the file.
// 4. Compare the read data with the written data to ensure they match.
// 5. Check if the read operation stops correctly at the end of the file.
// 
//---------------------------------------------------------------------
void testFileOperations() {
    string filename = "requests.dat"; 

    // Create a couple of Request records
    Request request1 = {"1234567890", "654321", "123456", "Description1", "5", "2023-07-14", "654321", "Open", "ProductA"};
    Request request2 = {"0987654321", "123456", "654321", "Description2", "3", "2023-07-15", "123456", "Closed", "ProductB"};

    // Write records to file using insertRequest function
    insertRequest(request1);
    insertRequest(request2);

    // Read records back from file one at a time
    Request readRequest1, readRequest2;
    {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            cerr << "Error opening file for reading: " << filename << endl;
            assert(inFile && "Error opening file for reading");
        }
        readFileByRequest(inFile, readRequest1);
        readFileByRequest(inFile, readRequest2);
        inFile.close();
    }

    // Programmatically check the data is the same
    bool pass = true;
    if (string(request1.phoneNumber) != string(readRequest1.phoneNumber)) { pass = false; cout << "Fail: request1.phoneNumber" << endl; }
    if (string(request1.releaseId) != string(readRequest1.releaseId)) { pass = false; cout << "Fail: request1.releaseId" << endl; }
    if (string(request1.changeId) != string(readRequest1.changeId)) { pass = false; cout << "Fail: request1.changeId" << endl; }
    if (string(request1.description) != string(readRequest1.description)) { pass = false; cout << "Fail: request1.description" << endl; }
    if (string(request1.priority) != string(readRequest1.priority)) { pass = false; cout << "Fail: request1.priority" << endl; }
    if (string(request1.date) != string(readRequest1.date)) { pass = false; cout << "Fail: request1.date" << endl; }
    if (string(request1.anticipatedReleaseId) != string(readRequest1.anticipatedReleaseId)) { pass = false; cout << "Fail: request1.anticipatedReleaseId" << endl; }
    if (string(request1.state) != string(readRequest1.state)) { pass = false; cout << "Fail: request1.state" << endl; }
    if (string(request1.productName) != string(readRequest1.productName)) { pass = false; cout << "Fail: request1.productName" << endl; }

    if (string(request2.phoneNumber) != string(readRequest2.phoneNumber)) { pass = false; cout << "Fail: request2.phoneNumber" << endl; }
    if (string(request2.releaseId) != string(readRequest2.releaseId)) { pass = false; cout << "Fail: request2.releaseId" << endl; }
    if (string(request2.changeId) != string(readRequest2.changeId)) { pass = false; cout << "Fail: request2.changeId" << endl; }
    if (string(request2.description) != string(readRequest2.description)) { pass = false; cout << "Fail: request2.description" << endl; }
    if (string(request2.priority) != string(readRequest2.priority)) { pass = false; cout << "Fail: request2.priority" << endl; }
    if (string(request2.date) != string(readRequest2.date)) { pass = false; cout << "Fail: request2.date" << endl; }
    if (string(request2.anticipatedReleaseId) != string(readRequest2.anticipatedReleaseId)) { pass = false; cout << "Fail: request2.anticipatedReleaseId" << endl; }
    if (string(request2.state) != string(readRequest2.state)) { pass = false; cout << "Fail: request2.state" << endl; }
    if (string(request2.productName) != string(readRequest2.productName)) { pass = false; cout << "Fail: request2.productName" << endl; }

    // Test that reads will stop at the end of the file
    Request readBeyondEOF;
    {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            cerr << "Error opening file for reading: " << filename << endl;
            assert(inFile && "Error opening file for reading");
        }
        inFile.seekg(2 * sizeof(Request));  // Move the file pointer to beyond the last record
        readFileByRequest(inFile, readBeyondEOF);
        assert(inFile.eof() && "Fail: did not reach end of file");
        inFile.close();
    }

    if (pass) {
        cout << "testFileOperations: Pass" << endl;
    } else {
        cout << "testFileOperations: Fail" << endl;
    }
}

int main() {
    testFileOperations();
    return 0;
}
