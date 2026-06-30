# Super Market DBMS

A simple console-based Super Market Inventory & Billing system written in C++. It stores product data in text files and lets you add, view, search, delete, restock products, and generate bills.

## About

This is a mini DBMS-style project built using core C++ concepts like structures, file handling, and functions. It does not use any external database — all data is read from and written to plain text files. It's meant as a beginner/intermediate project to practice file-based data management and basic billing logic.

## Features

- Add Product
- View Inventory
- Search Product
- Delete Product
- Restock Product
- Generate Bill

## Files

- `Inventory.txt` – stores product data
- `Bills.txt` – stores generated bills

## Example Usage

### 1. Add Product
```
Enter your choice: 1
Enter Product ID: 101
Enter Product Name: Sugar
Enter Price: 60
Enter Quantity: 20
Product Added Succesfully!
```

### 2. View Inventory
```
Enter your choice: 2
===== INVENTORY =====

ID: 101
Name: Sugar
Price: 60
Quantity: 20
---------------------
```

### 3. Search Product
```
Enter your choice: 3
Enter Product ID to search: 101

Product Found!
ID: 101
Name: Sugar
Price: 60
Product Quantity: 20
```

### 4. Delete Product
```
Enter your choice: 4
Enter Product ID to delete: 101
Product deleted successfully!
```

### 5. Restock Product
```
Enter your choice: 5
Enter Product ID to restock: 101
Enter quantity to add: 10
Stock Updated!
```

### 6. Generate Bill
```
Enter your choice: 6

Available Products:
ID	Name	Price	Quantity
101	Sugar	60	20

Enter product ID to purchase: 101
Enter quantity: 5
Add another item? (Y/N): n

==========BILL==========
Sugar	5 x 60 = 300
________________________
Grand Total = 300
========================
```

## License

This project is open-source and available for personal or educational use.
