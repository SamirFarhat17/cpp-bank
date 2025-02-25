# Bank Simulation Project

## Overview
This project simulates a banking system where customers can open accounts, deposit, withdraw, and transfer money. The system also implements exception handling for invalid transactions, logging, and various data structures to ensure efficiency. The implementation covers every major topic from the LearnCpp tutorial, making it an excellent educational resource for mastering C++.

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

## Chapters Covered from LearnCpp
This project is designed to cover all major C++ concepts taught in LearnCpp:

### **1. Basics of C++**
- Variables, data types, and operators.
- Control flow (`if`, `switch`, `for`, `while`).

### **2. Functions**
- Function declarations, definitions, and overloading.
- Pass-by-value vs pass-by-reference.

### **3. Classes & Object-Oriented Programming**
- Encapsulation: Private and public access specifiers.
- Constructors and destructors.
- Member functions and operator overloading.
- Inheritance and polymorphism (`Account` as a base class for different account types).

### **4. Memory Management**
- Dynamic memory allocation (`new`, `delete`).
- Smart pointers (`std::unique_ptr`, `std::shared_ptr`).

### **5. Standard Template Library (STL)**
- `std::vector`, `std::map`, and `std::unordered_map` for storing customers and accounts.
- `std::sort` for sorting transactions.

### **6. Exception Handling**
- `try`, `catch`, and `throw` for transaction failures.

### **7. File I/O**
- Reading and writing customer and transaction data to files.

### **8. Multithreading**
- `std::thread` for simulating concurrent transactions.
- `std::mutex` for synchronizing shared resources.

### **9. Templates**
- Generic functions for handling different transaction types.

### **10. Lambda Expressions & Functional Programming**
- Using lambdas for sorting and filtering transactions.

## Installation & Compilation
### **Requirements**
- C++11 or newer
- g++ or MSVC compiler

### **Building the Project**
make
```

## Running the Simulation
After building the project, run:
```sh
./BankSimulation
./main.exe
```

## Future Improvements
- Implement a GUI using Qt or SFML.
- Connect to an actual database.
- Add more complex financial instruments.

## Contributors
- Samir Farhat(SamirFarhat17)

