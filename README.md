# Bank Simulation Project

## Overview
This project simulates a banking system where customers can open accounts, deposit, withdraw, and transfer money. The system also implements exception handling for invalid transactions, logging, and various data structures to ensure efficiency. The implementation covers every major topic from the LearnCpp tutorial, making it an excellent educational resource for mastering C++. Additionally, the project includes advanced algorithm and data structure workloads and has been successfully Dockerized with Kubernetes for container orchestration.

## Features
- **Customer Management:** Create and manage customers with multiple accounts.
- **Account Management:** Open, close, and manage accounts with unique IDs.
- **Transactions:** Supports deposits, withdrawals, and transfers between accounts.
- **Exception Handling:** Handles errors such as insufficient funds, invalid account IDs, and negative transactions.
- **Data Persistence:** Uses file I/O to save and load bank data.
- **Multithreading:** Simulates concurrent transactions.
- **Smart Pointers:** Ensures proper memory management.
- **Templates & STL:** Uses vectors, maps, and other STL containers for efficiency.
- **Object-Oriented Design:** Implements classes for `Bank`, `Customer`, `Account`, and `Transaction`.
- **Advanced Algorithms and Data Structures:** Includes workloads for sorting, searching, and optimizing transaction processing.
- **Dockerized with Kubernetes:** The application is containerized using Docker and orchestrated with Kubernetes for scalability and deployment flexibility.

## Chapters Covered from LearnCpp
This project is designed to cover all major C++ concepts taught in LearnCpp:

### Introduction / Getting Started
Covers fundamental C++ concepts, setting up the development environment, configuring compilers, and compiling code. These fundamentals are used to set up the banking app project and ensure compatibility across different platforms.

### C++ Basics
Covers the basics of program structure, variables, input/output, and expressions. These concepts are used in the banking app to handle user interactions, such as account creation and balance inquiries.

### Functions and Files
Functions help modularize the banking app, improving maintainability. They are used to implement deposit, withdrawal, and balance-check functionalities. Header files organize the project efficiently.

### Debugging C++ Programs
Debugging techniques assist in resolving issues in transaction processing and error handling.

### Fundamental Data Types
Understanding data types helps in defining account numbers (integers), balances (floating point), and user authentication flags (booleans).

### Constants and Strings
Constants ensure fixed transaction limits, and strings handle customer names and account details.

### Operators
Arithmetic operators are used in calculations like interest and transaction fees. Logical operators validate user inputs and authentication.

### Scope, Duration, and Linkage
Defines variable scopes to manage global settings (interest rates) and local variables (session data).

### Control Flow
If statements handle authentication, loops process transaction logs, and switch statements manage menu selections.

### Error Detection and Handling
Validates user input, prevents overdrafts, and ensures secure authentication mechanisms.

### Type Conversion, Type Aliases, and Type Deduction
Used to handle currency conversion and flexible numeric computations.

### Function Overloading and Function Templates
Function overloading optimizes transaction processing for different account types.

### References and Pointers
Used in memory management and handling account references efficiently.

### Enums and Structs
Enums categorize transaction types, and structs store account details.

### Classes and Object-Oriented Programming
Encapsulates account details, user profiles, and transaction history within structured classes.

### Containers and Arrays
`std::vector` manages transaction records; `std::array` is used for static storage of bank branches.

### Iterators and Algorithms
Sorting algorithms organize transaction history, and iterators traverse account records.

### Dynamic Allocation
Manages dynamic user session data and memory-efficient transaction logs.

### Functions and Lambdas
Lambda functions streamline filtering operations (e.g., retrieving recent transactions).

### Operator Overloading
Overloaded operators compare account balances and format output statements.

### Move Semantics and Smart Pointers
Smart pointers manage dynamic memory for user sessions and avoid memory leaks.

### Object Relationships
Composition models customer-bank relationships, while dependencies handle linked accounts.

### Inheritance and Virtual Functions
Base classes represent general bank accounts, while derived classes specialize savings and checking accounts.

### Templates and Classes
Templates provide generic account operations, improving code reusability.

### Exceptions
Exception handling ensures robust transaction processing and prevents application crashes.

### Input and Output (I/O)
File I/O stores user data, transaction logs, and configurations securely.

By applying these C++ concepts, our banking app is modular, efficient, and secure, ensuring a seamless user experience.

---

## Installation & Compilation

### **Requirements**
- C++14 or newer
- g++ or MSVC compiler
- Docker (for containerization)
- Kubernetes (for orchestration)

### **Building and running the Project**
To build the project locally:(EXAMPLE)
```bash
make NUM_TRANSACTIONS=5000 NUM_CUSTOMERS=500 TEST_MODE=0  NDEBUG=0 CONCURRENCY=0
./BankSimulation
```
Here's a clear **Building and Running in Docker** section for your README.md, covering both individual service builds and the complete `compose.yaml` setup:

---

## 🐳 Building and Running in Docker

### **1. Bank Service Only**
Build and run just the C++ bank service:

```bash
# Build the image
docker build `
>>   --build-arg NUM_CUSTOMERS=100 `
>>   --build-arg NUM_TRANSACTIONS=1000 `
>>   --build-arg NDEBUG=0 `
>>   --build-arg TEST_MODE=0 `
>>   --build-arg CONCURRENCY=0 `
>>   -t bank-service .

# Run the container (mounts ./records to /app/records)
docker run -v ${PWD}/records:/app/records bank-servicedocker build `
>>   --build-arg NUM_CUSTOMERS=100 `
>>   --build-arg NUM_TRANSACTIONS=1000 `
>>   --build-arg NDEBUG=0 `
>>   --build-arg CONCURRENCY=0 `
>>   --build-arg TEST_MODE=0 `
>>   -t bank-service .
```

---

### **2. Full System with Compose**
For running both the bank service and file monitor together:

#### Commands
```bash
# Build and start all services
docker compose --env-file bank.env build

# Stop and remove containers
docker compose down

# Rebuild specific service
docker compose build bank-service
```

## Installation & Compilation
-Implement a GUI using Qt or SFML.
-Connect to an actual database.
-Add more complex financial instruments.
-Enhance Kubernetes deployment with auto-scaling and load balancing.

## Contributors
### Samir Farhat (SamirFarhat17)


