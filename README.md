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

Introduction / Getting Started

0.1 - 0.13: These sections cover fundamental C++ concepts, setting up the development environment, configuring compilers, and compiling code. We use these fundamentals to set up our banking app project and ensure compatibility across different platforms.

Chapter 1: C++ Basics

1.1 - 1.11: Covers the basics of program structure, variables, input/output, and expressions. These concepts are used in the banking app to handle user interactions, such as account creation and balance inquiries.

Chapter 2: Functions and Files

2.1 - 2.13: Functions help modularize the banking app, improving maintainability. We use them to implement deposit, withdrawal, and balance-check functionalities. Header files organize the project efficiently.

Chapter 3: Debugging C++ Programs

3.1 - 3.10: Debugging techniques assist in resolving issues in transaction processing and error handling.

Chapter 4: Fundamental Data Types

4.1 - 4.12: Understanding data types helps in defining account numbers (integers), balances (floating point), and user authentication flags (booleans).

Chapter 5: Constants and Strings

5.1 - 5.9: Constants ensure fixed transaction limits, and strings handle customer names and account details.

Chapter 6: Operators

6.1 - 6.8: Arithmetic operators are used in calculations like interest and transaction fees. Logical operators validate user inputs and authentication.

Chapter 7: Scope, Duration, and Linkage

7.1 - 7.14: Defines variable scopes to manage global settings (interest rates) and local variables (session data).

Chapter 8: Control Flow

8.1 - 8.15: If statements handle authentication, loops process transaction logs, and switch statements manage menu selections.

Chapter 9: Error Detection and Handling

9.1 - 9.6: Validates user input, prevents overdrafts, and ensures secure authentication mechanisms.

Chapter 10: Type Conversion, Type Aliases, and Type Deduction

10.1 - 10.9: Used to handle currency conversion and flexible numeric computations.

Chapter 11: Function Overloading and Function Templates

11.1 - 11.10: Function overloading optimizes transaction processing for different account types.

Chapter 12: References and Pointers

12.1 - 12.15: Used in memory management and handling account references efficiently.

Chapter 13: Enums and Structs

13.1 - 13.15: Enums categorize transaction types, and structs store account details.

Chapter 14-15: Classes and Object-Oriented Programming

14.1 - 15.x: Encapsulates account details, user profiles, and transaction history within structured classes.

Chapter 16-17: Containers and Arrays

16.1 - 17.x: std::vector manages transaction records; std::array is used for static storage of bank branches.

Chapter 18: Iterators and Algorithms

18.1 - 18.4: Sorting algorithms organize transaction history, and iterators traverse account records.

Chapter 19: Dynamic Allocation

19.1 - 19.5: Manages dynamic user session data and memory-efficient transaction logs.

Chapter 20: Functions and Lambdas

20.1 - 20.7: Lambda functions streamline filtering operations (e.g., retrieving recent transactions).

Chapter 21: Operator Overloading

21.1 - 21.x: Overloaded operators compare account balances and format output statements.

Chapter 22: Move Semantics and Smart Pointers

22.1 - 22.x: Smart pointers manage dynamic memory for user sessions and avoid memory leaks.

Chapter 23: Object Relationships

23.1 - 23.x: Composition models customer-bank relationships, while dependencies handle linked accounts.

Chapter 24-25: Inheritance and Virtual Functions

24.1 - 25.x: Base classes represent general bank accounts, while derived classes specialize savings and checking accounts.

Chapter 26: Templates and Classes

26.1 - 26.x: Templates provide generic account operations, improving code reusability.

Chapter 27: Exceptions

27.1 - 27.x: Exception handling ensures robust transaction processing and prevents application crashes.

Chapter 28: Input and Output (I/O)

28.1 - 28.7: File I/O stores user data, transaction logs, and configurations securely.

By applying these C++ concepts, our banking app is modular, efficient, and secure, ensuring a seamless user experience.
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

