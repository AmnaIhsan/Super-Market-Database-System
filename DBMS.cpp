#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
using namespace std;

struct Product
{
	int id;
	char name[50];
	float price;
	int quantity;
};

void addProduct();
void viewInventory();
void searchProduct();
void deleteProduct();
void restockProduct();
void displayInventory();
void generateBill();

int main()
{
	int choice;
	do
	{
		cout << "========== SUPER MARKET ==========\n";
		cout << "1. Add Product\n";
		cout << "2. View Inventory\n";
		cout << "3. Search Product\n";
		cout << "4. Delete Product\n";
		cout << "5. Restock Product\n";
		cout << "6. Generate Bill\n";
		cout << "7. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			addProduct();
			break;
		case 2:
			viewInventory();
			break;
		case 3:
			searchProduct();
			break;
		case 4:
			deleteProduct();
			break;
		case 5:
			restockProduct();
			break;
		case 6:
			generateBill();
			break;
		case 7:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice!\n";
		}
	} while (choice != 7);
	return 0;
}

void addProduct()
{
	Product p;
	ofstream fout("Inventory.txt", ios::app);
	if (!fout)
	{
		cout << "Error opening the file.\n";
		return;
	}
	cout << "Enter Product ID: ";
	cin >> p.id;
	cout << "Enter Product Name: ";
	cin.ignore();
	cin.getline(p.name, 50);
	cout << "Enter Price: ";
	cin >> p.price;
	cout << "Enter Quantity: ";
	cin >> p.quantity;

	fout << p.id << '\n';
	fout << p.name << '\n';
	fout << p.price << '\n';
	fout << p.quantity << '\n';

	fout.close();
	cout << "Product Added Succesfully!\n";
}

void viewInventory()
{
	Product p;
	ifstream fin("Inventory.txt");
	if (!fin)
	{
		cout << "No Inventory Found.";
		return;
	}
	cout << "===== INVENTORY =====\n";
	while (fin >> p.id)
	{
		fin.ignore();
		fin.getline(p.name, 50);
		fin >> p.price;
		fin >> p.quantity;

		cout << "\nID: " << p.id;
		cout << "\nName: " << p.name;
		cout << "\nPrice: " << p.price;
		cout << "\nQuantity: " << p.quantity;
		cout << "\n---------------------\n";
	}
	fin.close();
}

void searchProduct()
{
	Product p;
	int searchID;
	bool found = false;
	ifstream fin("Inventory.txt");
	if (!fin)
	{
		cout << "No Inventory Found.\n";
		return;
	}
	cout << "Enter Product ID to search: ";
	cin >> searchID;

	while (fin >> p.id)
	{
		fin.ignore();
		fin.getline(p.name, 50);
		fin >> p.price;
		fin >> p.quantity;

		if (p.id == searchID)
		{
			cout << "\nProduct Found!";
			cout << "\nID: " << p.id;
			cout << "\nName: " << p.name;
			cout << "\nPrice: " << p.price;
			cout << "\nProduct Quantity: " << p.quantity<<"\n";
			found = true;
			break;
		}
	}
	fin.close();

	if (!found)
	{
		cout << "Product not found!\n";
	}
}

void deleteProduct()
{
	Product p;
	int id;
	bool found = false;
	ifstream fin("Inventory.txt");
	ofstream fout("temp.txt");
	if (!fin)
	{
		cout << "No Inventory Found.\n";
		return;
	}
	cout << "Enter Product ID to delete: ";
	cin >> id;
	
	while (fin >> p.id)
	{
		fin.ignore();
		fin.getline(p.name, 50);
		fin >> p.price;
		fin >> p.quantity;
		if (p.id == id)
		{
			found = true;
			continue;
		}
		fout << p.id << "\n";
		fout << p.name << "\n";
		fout << p.price << "\n";
		fout << p.quantity << "\n";
	}
	fin.close();
	fout.close(); 
	if (remove("Inventory.txt") != 0)
		cout << "Error deleting old file.";
	if (rename("temp.txt", "Inventory.txt") != 0)
		cout << "Error renaming file.";
	if (found)
		cout << "Product deleted successfully!\n";
	else
		cout << "Product not found!\n";
}

void restockProduct()
{
	Product p;
	int id, addQty;
	bool found = false;

	ifstream fin("Inventory.txt");
	ofstream fout("temp.txt");

	if (!fin)
	{
		cout << "No Inventory Found.\n";
		return;
	}

	cout << "Enter Product ID to restock: ";
	cin >> id;
	while (fin >> p.id)
	{
		fin.ignore();
		fin.getline(p.name, 50);
		fin >> p.price;
		fin >> p.quantity;
		if (p.id == id)
		{
			found = true;
			cout << "Enter quantity to add: ";
			cin >> addQty;
			p.quantity = p.quantity + addQty;
		}
		fout << p.id << "\n";
		fout << p.name << "\n";
		fout << p.price << "\n";
		fout << p.quantity << "\n";
	}
	fin.close();
	fout.close();

	if (remove("Inventory.txt") != 0)
		cout << "Error deleting old file.";
	if (rename("temp.txt", "Inventory.txt") != 0)
		cout << "Error renaming file.";

	if (found)
		cout << "Stock Updated!\n";
	else
		cout << "Product not found\n";

}

void displayInventory()
{
	Product p;
	ifstream fin("Inventory.txt");
	if (!fin)
	{
		cout << "No Inventory Found.\n";
		return;
	}
	cout << "\nAvailable Products:\n";
	cout << "ID\tName\tPrice\tQuantity\n";
	while (fin >> p.id)
	{
		fin.ignore();
		fin.getline(p.name, 50);
		fin >> p.price;
		fin >> p.quantity;
		cout << p.id << "\t" << p.name << "\t" << p.price << "\t" << p.quantity << "\n";
	}
	fin.close();
}

void generateBill()
{
	Product p;
	int id, qty;
	char choice;
	float total = 0;

	struct BillItem
	{
		char name[50];
		float price;
		int qty;
	};
	BillItem bill[50] = {0};
	int count = 0;

	do
	{
		displayInventory();
		cout << "\nEnter product ID to purchase: ";
		cin >> id;
		cout << "Enter quantity: ";
		cin >> qty;
		ifstream fin("Inventory.txt");
		ofstream fout("temp.txt");
		bool found = false;
		while (fin >> p.id)
		{
			fin. ignore();
			fin.getline(p.name, 50);
			fin >> p.price;
			fin >> p.quantity;
			if (p.id == id)
			{
				found = true;
				if (qty > p.quantity)
				{
					cout << "Insufficient stock! Available: " << p.quantity << "\n";
				}
				else
				{
					p.quantity = p.quantity - qty;
					strcpy(bill[count].name, p.name);
					bill[count].price = p.price;
					bill[count].qty = qty;
					total = total + p.price * qty;
					count = count + 1;
				}
			}
			fout << p.id << "\n";
			fout << p.name << "\n";
			fout << p.price << "\n";
			fout << p.quantity << "\n";
		}
		fin.close();
		fout.close();

		if (remove("Inventory.txt") != 0)
			cout << "Error deleting old file.";
		if (rename("temp.txt", "Inventory.txt") != 0)
			cout << "Error renaming file.";
		if (!found)
		{
			cout << "Product ID not found.\n";
		}
		cout << "Add another item? (Y/N): ";
		cin >> choice;

	} while ((choice == 'Y' || choice == 'y') && (count < 50));
	if (count == 0)
	{
		cout << "No Item purchased.\n";
		return;
	}

	cout << "\n==========BILL==========\n";
	for (int i = 0; i < count; i++)
	{
		cout << bill[i].name << "\t" << bill[i].qty << " x " << bill[i].price << " = " << bill[i].qty * bill[i].price << "\n";
	}
	cout << "________________________\n";
	cout << "Grand Total = " << total << "\n";
	cout << "========================\n";

	ofstream fout("Bills.txt", ios::app);
	if (fout)
	{
		fout << "\n==========BILL==========\n";
		for (int i = 0; i < count; i++)
		{
			fout << bill[i].name << "\t" << bill[i].qty << " x " << bill[i].price << " = " << bill[i].qty * bill[i].price << "\n";
		}
		fout << "________________________\n";
		fout << "Grand Total = " << total << "\n";
		fout << "========================\n";
		fout.close();
	}
}