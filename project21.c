#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Item structure declaration
typedef struct {
    int itemno;
    char iname[50];
    float price, dis;
    int stock;  // Add stock attribute for item quantity
} Item;

// Function prototypes
void profit(Item *item, int qtySold, float sellingPrice);
int pass2();
void disp_all();
void display_sp(int n);
void modify();
void deleterec();
void place_order();
void buy(Item *item);
void sell(Item *item);
void write_to_file();
void delay(int milliseconds);

FILE *f;

// Function to buy items and add them to inventory
void buy(Item *item) {
    printf("Enter Item Number: ");
    scanf("%d", &item->itemno);
    printf("Enter Item Name: ");
    getchar();  // to consume the newline left by previous input
    fgets(item->iname, sizeof(item->iname), stdin);
    item->iname[strcspn(item->iname, "\n")] = '\0';  // Remove newline character from the string
    printf("Enter Purchase Price: ");
    scanf("%f", &item->price);
    printf("Enter Discount (%%): ");
    scanf("%f", &item->dis);
    printf("Enter Stock Quantity: ");
    scanf("%d", &item->stock);
    
    // Writing to a file (inventory file)
    f = fopen("inventory.txt", "a");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(f, "%d %s %.2f %.2f %d\n", item->itemno, item->iname, item->price, item->dis, item->stock);
    fclose(f);
    printf("Item Purchased and Added to Inventory Successfully!\n");
}

// Function to sell items and calculate profit
void sell(Item *item) {
    int sellQty;
    printf("Enter Item Number to Sell: ");
    scanf("%d", &item->itemno);
    
    // Read inventory file and find the item
    f = fopen("inventory.txt", "r+");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    int found = 0;
    long pos;
    Item readItem;
    while (fscanf(f, "%d %s %f %f %d\n", &readItem.itemno, readItem.iname, &readItem.price, &readItem.dis, &readItem.stock) != EOF) {
        if (item->itemno == readItem.itemno) {
            found = 1;
            pos = ftell(f);
            break;
        }
    }
    
    if (!found) {
        printf("Item not found in inventory.\n");
        fclose(f);
        return;
    }

    printf("Enter Quantity to Sell: ");
    scanf("%d", &sellQty);
    
    if (sellQty > readItem.stock) {
        printf("Not enough stock available.\n");
        fclose(f);
        return;
    }
    
    // Calculate selling price after discount
    float sellingPrice = readItem.price * (1 - readItem.dis / 100);
    printf("Selling Price after Discount: %.2f\n", sellingPrice);
    
    // Update stock and write to file
    readItem.stock -= sellQty;
    fseek(f, pos - sizeof(Item), SEEK_SET);
    fprintf(f, "%d %s %.2f %.2f %d\n", readItem.itemno, readItem.iname, readItem.price, readItem.dis, readItem.stock);
    fclose(f);
    
    printf("Item Sold Successfully!\n");
    
    // Call profit function to calculate profit from this transaction
    profit(item, sellQty, sellingPrice);
}

// Function to calculate and display profit
void profit(Item *item, int qtySold, float sellingPrice) {
    float totalRevenue = sellingPrice * qtySold;
    float costPrice = item->price * qtySold;
    float profit = totalRevenue - costPrice;

    printf("Total Revenue from Sale: %.2f\n", totalRevenue);
    printf("Total Cost Price: %.2f\n", costPrice);
    printf("Profit from Sale: %.2f\n", profit);
}

// Admin menu
void admin_menu() {
    int choice;
    if (!pass2()) {
        printf("\nIncorrect Password. Returning to Main Menu...\n");
        delay(2000);
        return;
    }

    do {
        printf("\nAdmin Menu:");
        printf("\n1. Create Item");
        printf("\n2. Display All Items");
        printf("\n3. Query Item");
        printf("\n4. Modify Item");
        printf("\n5. Delete Item");
        printf("\n6. Back to Main Menu");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: write_to_file(); break;
            case 2: disp_all(); break;
            case 3: {
                int num;
                printf("\nEnter Item Number to Query: ");
                scanf("%d", &num);
                display_sp(num);
                break;
            }
            case 4: modify(); break;
            case 5: deleterec(); break;
            case 6: return;
            default: printf("\nInvalid Choice! Try again.\n");
        }
    } while (choice != 6);
}

// Function to create item and write it to file
void write_to_file() {
    Item item;
    buy(&item);  // Call the buy function to add an item
}

// Main menu
void menu() {
    int choice;
    do {
        printf("\nMain Menu:");
        printf("\n1. Place Order");
        printf("\n2. Admin");
        printf("\n3. Exit");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: place_order(); break;
            case 2: admin_menu(); break;
            case 3: exit(0);
            default: printf("\nInvalid Choice! Try again.\n");
        }
    } while (choice != 3);
}

// Main function
int main() {
    menu();
    return 0;
}
