#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> // For exit()

using namespace std;

class Item {
    int itemno;
    string iname;
    float price, tax, dis;

public:
    void getdata() {
        cin.ignore();
        cout << "\nEnter Item Number: ";
        cin >> itemno;
        cin.ignore();
        cout << "Enter Item Name: ";
        getline(cin, iname);
        cout << "Enter Item Price: ";
        cin >> price;
        cout << "Enter Discount (%): ";
        cin >> dis;
    }

    void showdata() const {
        cout << "\nItem Number: " << itemno
             << "\nItem Name: " << iname
             << "\nPrice: " << price
             << "\nDiscount: " << dis << "%";
    }

    int retitemno() const { return itemno; }
    float retprice() const { return price; }
    string retiname() const { return iname; }
    float retdis() const { return dis; }
};

fstream f; // File stream object
Item i;

// Function to write an item to the file
void write_to_file() {
    f.open("store.dat", ios::out | ios::app | ios::binary);
    if (!f) {
        cerr << "Error: File could not be opened.\n";
        return;
    }
    i.getdata();
    f.write(reinterpret_cast<char*>(&i), sizeof(Item));
    f.close();
    cout << "\nItem has been created.";
}

// Function to display all records from the file
void disp_all() {
    f.open("store.dat", ios::in | ios::binary);
    if (!f) {
        cerr << "Error: File could not be opened.\n";
        return;
    }
    cout << "\n\nDisplaying All Records:\n";
    while (f.read(reinterpret_cast<char*>(&i), sizeof(Item))) {
        i.showdata();
        cout << "\n-------------------------------\n";
    }
    f.close();
}

// Function to display a specific record
void display_sp(int n) {
    bool found = false;
    f.open("store.dat", ios::in | ios::binary);
    if (!f) {
        cerr << "Error: File could not be opened.\n";
        return;
    }
    while (f.read(reinterpret_cast<char*>(&i), sizeof(Item))) {
        if (i.retitemno() == n) {
            i.showdata();
            found = true;
            break;
        }
    }
    f.close();
    if (!found) {
        cout << "\nRecord does not exist.";
    }
}

// Function to modify a record
void modify() {
    int no;
    bool found = false;
    cout << "\nEnter the Item Number to Modify: ";
    cin >> no;

    f.open("store.dat", ios::in | ios::out | ios::binary);
    if (!f) {
        cerr << "Error: File could not be opened.\n";
        return;
    }

    while (f.read(reinterpret_cast<char*>(&i), sizeof(Item)) && !found) {
        if (i.retitemno() == no) {
            cout << "\nCurrent Record Details:\n";
            i.showdata();

            cout << "\n\nEnter New Details:\n";
            i.getdata();

            f.seekp(-static_cast<int>(sizeof(Item)), ios::cur);
            f.write(reinterpret_cast<char*>(&i), sizeof(Item));
            cout << "\nRecord Updated Successfully.";
            found = true;
        }
    }
    f.close();
    if (!found) {
        cout << "\nRecord Not Found.";
    }
}

// Function to delete a record
void deleterec() {
    int no;
    cout << "\nEnter the Item Number to Delete: ";
    cin >> no;

    f.open("store.dat", ios::in | ios::binary);
    if (!f) {
        cerr << "Error: File could not be opened.\n";
        return;
    }

    fstream temp;
    temp.open("temp.dat", ios::out | ios::binary);
    if (!temp) {
        cerr << "Error: Temporary file could not be created.\n";
        f.close();
        return;
    }

    while (f.read(reinterpret_cast<char*>(&i), sizeof(Item))) {
        if (i.retitemno() != no) {
            temp.write(reinterpret_cast<char*>(&i), sizeof(Item));
        }
    }
    f.close();
    temp.close();

    remove("store.dat");
    rename("temp.dat", "store.dat");
    cout << "\nRecord Deleted Successfully.";
}

// Function to display all items in menu format
void menu() {
    f.open("store.dat", ios::in | ios::binary);
    if (!f) {
        cerr << "Error: File could not be opened.\n";
        return;
    }
    cout << "\n\nItem Menu:\n";
    cout << "====================================\n";
    cout << "ITEM NO\t\tNAME\t\tPRICE\n";
    cout << "====================================\n";
    while (f.read(reinterpret_cast<char*>(&i), sizeof(Item))) {
        cout << i.retitemno() << "\t\t" << i.retiname() << "\t\t" << i.retprice() << "\n";
    }
    f.close();
}

// Function to place an order and generate a bill
void place_order() {
    vector<int> order_arr;
    vector<int> quan;
    char ch;

    menu();
    cout << "\nPlace Your Order:\n";
    do {
        int item_no, quantity;
        cout << "\nEnter Item Number: ";
        cin >> item_no;
        cout << "Enter Quantity: ";
        cin >> quantity;
        order_arr.push_back(item_no);
        quan.push_back(quantity);

        cout << "Do you want to order another item? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    cout << "\nGenerating Invoice...\n";
    float total = 0;

    cout << "Item No\tName\tQuantity\tPrice\tAmount\tAmount after Discount\n";
    for (size_t x = 0; x < order_arr.size(); x++) {
        f.open("store.dat", ios::in | ios::binary);
        if (!f) {
            cerr << "Error: File could not be opened.\n";
            return;
        }

        while (f.read(reinterpret_cast<char*>(&i), sizeof(Item))) {
            if (i.retitemno() == order_arr[x]) {
                float amt = i.retprice() * quan[x];
                float damt = amt - (amt * i.retdis() / 100);
                cout << order_arr[x] << "\t" << i.retiname() << "\t" << quan[x]
                     << "\t\t" << i.retprice() << "\t" << amt << "\t" << damt << "\n";
                total += damt;
            }
        }
        f.close();
    }
    cout << "\nTotal Amount: " << total << "\n";
}

// Admin menu
void admin_menu() {
    char ch;
    do {
        cout << "\nAdmin Menu:";
        cout << "\n1. Create Item";
        cout << "\n2. Display All Items";
        cout << "\n3. Query Item";
        cout << "\n4. Modify Item";
        cout << "\n5. Delete Item";
        cout << "\n6. Back to Main Menu";
        cout << "\nEnter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case '1': write_to_file(); break;
            case '2': disp_all(); break;
            case '3': {
                int num;
                cout << "\nEnter Item Number to Query: ";
                cin >> num;
                display_sp(num);
                break;
            }
            case '4': modify(); break;
            case '5': deleterec(); break;
            case '6': return;
            default: cout << "\nInvalid Choice! Try again.";
        }
    } while (ch != '6');
}

// Main function
int main() {
    char ch;
    do {
        cout << "\nMain Menu:";
        cout << "\n1. Customer";
        cout << "\n2. Administrator";
        cout << "\n3. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case '1': place_order(); break;
            case '2': admin_menu(); break;
            case '3': exit(0);
            default: cout << "\nInvalid Choice! Try again.";
        }
    } while (ch != '3');
    return 0;
}
