# Issue Tracking System (ITS)

## Overview
The Issue Tracking System (ITS) is a console-based application for creating, tracking, and
managing change requests from customers and employees, with engineer workflows for
product releases and reporting.

## Features
- Create customer requests and view them by change ID
- Create employee requests and view them by change ID
- Create products and product releases
- Update change items (state, description, priority, anticipated release)
- Generate reports for not-done and completed change items
- Sequential change ID generation

## Build

### Option 1: Build the native console app
This target builds a local executable named `run`:

```
make -f main-makefile
```

### Option 2: Build a Windows executable
This target builds a Windows executable named `ITS.exe`:

```
make -f makefile
```

### Manual compile (g++)
```
g++ -Wall main.cpp mainUI.cpp FileHandler.cpp Customer.cpp Employee.cpp Engineer.cpp -o run
```

## Run
```
./run
```

On Windows, run:
```
ITS.exe
```

## Usage
The main menu exposes three roles:
- Customer: create requests and view by change ID
- Employee: create requests and view by change ID
- Engineer: update change items, create products/releases, and generate reports

## Data Files
The application stores data in binary files in the working directory:
- customers.dat
- employees.dat
- products.dat
- requests.dat
- id_counter.dat

Deleting these files resets the corresponding data.

## Tests and Utilities
- testFileOps.cpp: basic read/write checks for request storage
- testEngineer.cpp: functional tests for product creation
- requestgenerator.cpp: generates random requests and seed data
- unitTestMain.cpp: manual test driver

## Notes
- Phone numbers are expected to be 10 to 11 digits.
- Change IDs and release IDs are expected to be 6 digits.
- The console UI uses Windows-specific commands (for example, clearing the screen).