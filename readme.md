# Stock and Inventory Management System

A C-based console application for managing product records, stock levels, sales, and invoices. This project is designed for small retail or inventory operations where the admin can add products, update stock, sell items, and generate customer invoices.

## Features

- User registration and login
- Admin menu for managing stock records
- Add new product items
- Display all items
- Search for a specific item by item number
- Modify existing product details
- Delete product records
- Buy and sell products
- Update stock after each transaction
- Calculate profit for sales
- Generate an invoice for customer orders

## Project Files

- `StockAndInventoryManagement.c` – main source code
- `inventory.txt` – inventory data file
- `store.dat` – product records saved in binary format
- `users.dat` – registered user data
- `readme.md` – project documentation

## Technology Used

- Language: C
- Compiler: GCC / MinGW on Windows
- Console graphics: Windows API functions such as `SetConsoleCursorPosition` and `gotoxy`

## How to Run

1. Open the project in a C compiler such as Code::Blocks, Dev C++, or any MinGW-compatible environment.
2. Compile the source file:

   ```bash
   gcc StockAndInventoryManagement.c -o stock_manager.exe
   ```

3. Run the program:

   ```bash
   stock_manager.exe
   ```

> This project uses Windows-specific console functions, so it is best suited for Windows systems.

## Main Menu Options

When the program starts, the user can:

1. Register
2. Login
3. Exit

After login, the main menu includes:

1. Product Purchase
2. Admin
3. Exit

### Admin Menu

The admin can perform:

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

## Data Storage

The application stores data in local files:

- `users.dat` for login credentials
- `store.dat` for product records
- `inventory.txt` for inventory updates
- `temp.dat` is used temporarily during delete operations

## Example Workflow

1. Register a user.
2. Log in to the system.
3. Add products to inventory.
4. View or modify stock details as needed.
5. Generate product purchase orders or invoices.
6. Sell items and check profit information.

## Notes

This is a beginner/intermediate C project intended for academic or learning purposes. It demonstrates file handling, structures, login functionality, inventory management, and basic business operations in a console application.

## Future Improvements

- Add password encryption
- Improve validation for item numbers and quantities
- Add a search feature for item names
- Add sales history and reporting
- Create a graphical user interface (GUI)
- Support database storage instead of local files

## Author

This project was developed as a stock and inventory management system for C programming practice and academic use.
