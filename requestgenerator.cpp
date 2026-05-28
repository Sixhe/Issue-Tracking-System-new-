#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;


int currentChangeId = 0;

int randNum(int min_val, int max_val)
{
    int num_val = rand() % (max_val - min_val + 1) + min_val;
    return num_val;
}

void generateRandomRequests(vector<Request>& requests, int count) {
    const char* states[] = { "Done", "Cancelled", "Accessed", "InProgress" };
    const char* products[] = { "ProductA", "ProductB", "ProductC", "ProductD" };

    for (int i = 0; i < count; ++i) {
        Request req;
        Customer cus;
        Employee emp;

        int phoneNumber = randNum(1000000000, 100000000000);
        snprintf(req.phoneNumber, 12, "%d", phoneNumber);

        strncpy(req.releaseId, "000001", 7);

        string changeId = generateSequentialChangeID();
        strncpy(req.changeId, changeId.c_str(), 7);

        snprintf(req.description, 31, "Description%d", i + 1);
        snprintf(req.priority, 2, "%d", 1);
        snprintf(req.date, 11, "2024-%02d-%02d", (rand() % 12) + 1, (rand() % 28) + 1);
        snprintf(req.anticipatedReleaseId, 7, "%06d", rand() % 1000000);
        snprintf(req.state, 12, "%s", states[rand() % 4]);
        snprintf(req.productName, 13, "%s", products[rand() % 4]);

        if ((rand() % 2) == 1) {
            snprintf(cus.name, 12, "C Name%d", i + 1);
            snprintf(cus.email, 24, "customer@email%d", i + 1);
            snprintf(cus.phoneNumber, 12, "%d", phoneNumber);
            insertCustomer(cus);
        }
        else {
            snprintf(emp.name, 12, "E Name%d", i + 1);
            snprintf(emp.email, 24, "employee@email%d", i + 1);
            snprintf(emp.phoneNumber, 12, "%d", phoneNumber);
            strncpy(emp.department, "Test Department", 30);
            insertEmployee(emp);
        }

        requests.push_back(req);
    }
}


extern void insertRequest(const Request& req);

void testFileOperations() {
    string filename = "requests.dat";

    // Generate 50 random requests
    vector<Request> requests;
    generateRandomRequests(requests, 500);

    // Write records to file using insertRequest function
    for (const auto& req : requests) {
        insertRequest(req);
    }

    // You can add reading and verification code here
}

int main() {
    srand(time(0));
    testFileOperations();
    return 0;
}
