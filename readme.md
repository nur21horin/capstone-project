# Stock and Inventory Management System

## Project Title

Stock and Inventory Management System

## Overview

This project is a console-based inventory management application developed in the C programming language. It is designed to help manage product records, stock levels, purchasing, selling, and invoice generation in a simple and efficient manner. The system allows administrators to maintain product information, monitor inventory, and perform business-related operations through a menu-driven interface.

## Objective

The main purpose of this project is to provide a practical solution for stock management using structured programming concepts. It demonstrates the use of file handling, data structures, user authentication, menu-driven programming, and basic business operations in C.

## Features

- User registration and login system
- Admin-based product management
- Add new items to the inventory
- Display all stored product records
- Search for an item by item number
- Modify existing product details
- Delete product records
- Purchase and stock update functionality
- Sell product items and update current stock
- Profit calculation for sales transactions
- Invoice generation for customer orders

## Problem Statement

In many small retail businesses, product records and stock information are often maintained manually, which can lead to errors, mismanagement, and poor decision-making. This project addresses that issue by automating the process of tracking products, stock quantities, prices, discounts, and sales information in a digital system.

## Scope

The system is intended for small-scale inventory operations and supports basic stock and sales management tasks. It is suitable for academic learning and demonstration of programming concepts rather than a large-scale enterprise-level inventory system.

## Tools and Technologies

- Programming Language: C
- Compiler: GCC / MinGW
- Operating System: Windows-based console environment
- Libraries: stdio.h, stdlib.h, string.h, time.h, conio.h, windows.h

## Project Structure

- `StockAndInventoryManagement.c` – main source code
- `store.dat` – binary file used to store product data
- `inventory.txt` – inventory records in text format
- `users.dat` – user registration and login data
- `temp.dat` – temporary file created during record deletion
- `readme.md` – project documentation

## System Workflow

1. The user registers or logs in.
2. After successful login, the main menu appears.
3. The admin can create, view, query, modify, or delete item records.
4. The system allows product purchases and sales.
5. Inventory stock is updated after sales and purchase operations.
6. The transaction details can be used to calculate profit.
7. An invoice can be generated from the selected order items.

## Main Functional Modules

### 1. User Management

- Registration of users
- Login validation for admin access

### 2. Inventory Management

- Add new product records
- Display all items
- Search a specific product
- Update product information
- Remove item entries

### 3. Sales and Purchase Operations

- Buy product items and save them to inventory
- Sell items while checking stock availability
- Update stock after each sale

### 4. Financial Module

- Calculate selling price after discount
- Compute total revenue
- Display cost price and profit

### 5. Invoice Module

- Accept multiple item orders
- Calculate total amount after discount
- Generate a simple invoice summary

## Menu Description

After login, the user can access the following menu options:

1. Create Item
2. Display All Items
3. Query Item
4. Modify Item
5. Delete Item
6. Buy Product
7. Sell Product
8. Profit
9. Create Invoice
10. Back to Main Menu

## How to Run the Program

1. Open the project in a C compiler such as Code::Blocks, Dev C++, or a MinGW environment.
2. Compile the source file using:

```bash
gcc StockAndInventoryManagement.c -o stock_manager.exe
```

3. Run the executable:

```bash
stock_manager.exe
```

> The program uses Windows-specific console functions, so it is recommended to run it on a Windows operating system.

## Data Storage

The application uses local files to store data instead of a database. This makes the project simple, portable for learning purposes, and easy to understand for beginners.

## Advantages

- Simple and user-friendly interface
- Easy to understand and modify
- Demonstrates practical file handling in C
- Covers stock management and business logic
- Suitable for academic and learning projects

## Limitations

- No real database integration
- No advanced security features
- Limited validation for incorrect user inputs
- Basic invoice and profit calculations
- Not optimized for large-scale commercial use

## Future Enhancements

- Add password encryption
- Improve input validation and error handling
- Add product category and supplier details
- Include sales history and reports
- Add graphical user interface (GUI)
- Store data in a database such as MySQL or SQLite
- Add search by product name and category

## Conclusion

The Stock and Inventory Management System is a practical C programming project that demonstrates the implementation of inventory control, user authentication, file handling, and sales calculations in a simple console application. It provides an efficient foundation for learning how real-world inventory systems can be modeled using structured programming.

## Author

This project was developed as an academic C programming assignment/project for stock and inventory management.
