#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// Function prototypes
void mainMenu();
void adminMenu();
void customerMenu();
void placeOrder();
void writeToItemFile();
void displayAllItems();
void displaySpecificItem(int);
void modifyItem();
void deleteItem();
void drawBorder(int, int, int, int);
void gotoxy(int, int);
void passwordProtection();
void profit_loss_data();
// Structure definition for Item
typedef struct {
    int itemNo;
    char name[50];
    float price, discount;
} Item,Item1[100];
int num, i, SN;
FILE *fp1, *fp2, *fp3;

struct veg //creating a structure to store the details
{
	int SN;
	char name[20];
	float quantity, rate;
} v[100], vs[100], temp[100], temp2[100];
// Global variables
FILE *file;
Item item;

// Utility functions
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBorder(int x, int y, int width, int height) {
    for (int i = 0; i < width; ++i) {
        gotoxy(x + i, y);
        printf("-");
        gotoxy(x + i, y + height);
        printf("-");
    }
    for (int i = 0; i < height; ++i) {
        gotoxy(x, y + i);
        printf("|");
        gotoxy(x + width, y + i);
        printf("|");
    }
}

void delay(int milliseconds) {
    clock_t goal = milliseconds + clock();
    while (goal > clock());
}

// Password protection
void passwordProtection() {
    system("cls");
    char password[20];
    printf("Welcome to The ALO Store\n");
    const char correctPassword[] = "DIU089";
    int attempts = 3;

    while (attempts--) {
        drawBorder(5, 3, 50, 5);
        gotoxy(10, 5);
        printf("Enter Password: ");
        int i = 0;
        char ch;
        while ((ch = getch()) != 13) { // Enter key
            if (ch == 8 && i > 0) {    // Backspace
                printf("\b \b");
                i--;
            } else if (ch != 8) {
                printf("*");
                password[i++] = ch;
            }
        }
        password[i] = '\0';

        if (strcmp(password, correctPassword) == 0) {
            printf("\nAccess Granted!\n");
            delay(1000);
            return;
        } else {
            printf("\nIncorrect Password. Attempts left: %d\n", attempts);
            delay(1000);
            system("cls");
        }
    }
    printf("Access Denied. Exiting...\n");
    exit(0);
}

// Functions to manage items
void writeToItemFile() {
    file = fopen("store.dat", "ab");
    if (!file) {
        printf("\nError opening file!");
        return;
    }
    printf("\nEnter the Item Number: ");
    scanf("%d", &item.itemNo);
    getchar();  // Consume newline after scanf
    printf("Enter the Item Name: ");
    fgets(item.name, 50, stdin);
    item.name[strcspn(item.name, "\n")] = '\0'; // Remove trailing newline
    printf("Enter the Price of the Item: ");
    scanf("%f", &item.price);
    printf("Enter the Discount (%) on the Item: ");
    scanf("%f", &item.discount);

    fwrite(&item, sizeof(Item), 1, file);
    fclose(file);
    printf("\nItem Added Successfully!\n");
}

void displayAllItems() {
    system("cls");
    printf("\n\n\tAll Items\n");
    printf("======================================\n");
    file = fopen("store.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    while (fread(&item, sizeof(Item), 1, file)) {
        printf("\nItem Number: %d\n", item.itemNo);
        printf("Item Name: %s\n", item.name);
        printf("Price: %.2f\n", item.price);
        printf("Discount: %.2f%%\n", item.discount);
        printf("--------------------------------------\n");
    }
    fclose(file);
}

void displaySpecificItem(int itemNo) {
    int found = 0;
    file = fopen("store.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    while (fread(&item, sizeof(Item), 1, file)) {
        if (item.itemNo == itemNo) {
            system("cls");
            printf("\nItem Number: %d\n", item.itemNo);
            printf("Item Name: %s\n", item.name);
            printf("Price: %.2f\n", item.price);
            printf("Discount: %.2f%%\n", item.discount);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("\nItem Not Found!\n");
    }
}

void modifyItem() {
    int itemNo, found = 0;
    system("cls");
    printf("\nEnter the Item Number to Modify: ");
    scanf("%d", &itemNo);
    file = fopen("store.dat", "r+b");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    while (fread(&item, sizeof(Item), 1, file)) {
        if (item.itemNo == itemNo) {
            printf("\nCurrent Details:\n");
            printf("Item Number: %d\n", item.itemNo);
            printf("Item Name: %s\n", item.name);
            printf("Price: %.2f\n", item.price);
            printf("Discount: %.2f%%\n", item.discount);
            printf("\nEnter New Details:\n");

            printf("\nEnter the Item Number: ");
            scanf("%d", &item.itemNo);
            getchar();  // Consume newline after scanf
            printf("Enter the Item Name: ");
            fgets(item.name, 50, stdin);
            item.name[strcspn(item.name, "\n")] = '\0'; // Remove trailing newline
            printf("Enter the Price of the Item: ");
            scanf("%f", &item.price);
            printf("Enter the Discount (%) on the Item: ");
            scanf("%f", &item.discount);

            fseek(file, -sizeof(Item), SEEK_CUR);
            fwrite(&item, sizeof(Item), 1, file);
            printf("\nItem Modified Successfully!\n");
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("\nItem Not Found!\n");
    }
}

void deleteItem() {
    int itemNo;
    system("cls");
    printf("\nEnter the Item Number to Delete: ");
    scanf("%d", &itemNo);
    FILE *tempFile = fopen("temp.dat", "wb");
    file = fopen("store.dat", "rb");
    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }
    while (fread(&item, sizeof(Item), 1, file)) {
        if (item.itemNo != itemNo) {
            fwrite(&item, sizeof(Item), 1, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("store.dat");
    rename("temp.dat", "store.dat");
    printf("\nItem Deleted Successfully!\n");
}

// Customer menu and order processing
void placeOrder() {
    system("cls");
    int order[50], quantity[50], count = 0;
    char choice;
    float total = 0;
    do {
        displayAllItems();
        printf("\nEnter Item Number to Order: ");
        scanf("%d", &order[count]);
        printf("Enter Quantity: ");
        scanf("%d", &quantity[count]);
        count++;
        printf("Add more items? (y/n): ");
        getchar(); // Consume newline
        scanf("%c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("\n\n********** INVOICE **********\n");
    printf("Item No.\tName\tQty\tPrice\tAmount\tAfter Discount\n");
    for (int i = 0; i < count; i++) {
        file = fopen("store.dat", "rb");
        if (!file) {
            printf("Error opening file!\n");
            return;
        }
        while (fread(&item, sizeof(Item), 1, file)) {
            if (item.itemNo == order[i]) {
                float amount = item.price * quantity[i];
                float discountedAmount = amount - (amount * item.discount / 100);
                printf("%d\t\t%s\t%d\t%.2f\t%.2f\t%.2f\n", order[i], item.name, quantity[i], item.price, amount, discountedAmount);
                total += discountedAmount;
                break;
            }
        }
        fclose(file);
    }
    printf("\nTotal Amount: %.2f\n", total);
}

// Menus
void adminMenu() {
    char choice;
    do {
        system("cls");
        printf("\n\nAdmin Menu");
        printf("\n1. Add Item");
        printf("\n2. Display All Items");
        printf("\n3. Display Specific Item");
        printf("\n4. Modify Item");
        printf("\n5. Delete Item");
        printf("\n6.Profit or Loss");
        printf("\n7. Back to Main Menu");
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
        case '1':
            writeToItemFile();
            break;
        case '2':
            displayAllItems();
            break;
        case '3': {
            int itemNo;
            printf("\nEnter Item Number: ");
            scanf("%d", &itemNo);
            displaySpecificItem(itemNo);
            break;
        }
        case '4':
            modifyItem();
            break;
        case '5':
            deleteItem();
            break;
        case '6':
            profit_loss_data();
            break;    
        case '7':
            return;
        default:
            printf("\nInvalid Choice!");
        }
        system("pause");
    } while (choice != '6');
}

void mainMenu() {
    char choice;
    do {
        system("cls");
        printf("\n\nMain Menu");
        printf("\n1. Customer");
        printf("\n2. Administrator");
        printf("\n3. Exit");
        
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
        case '1':
            customerMenu();
            break;
        case '2':
            passwordProtection();
            adminMenu();
            break;
        case '3':
            exit(0);
            break;
            
        default:
            printf("\nInvalid Choice!");
        }
        system("pause");
    } while (choice != '3');
}

void profit_loss_data()
{
	system("cls");
	drawBorder(5, 3, 100, 60);
	gotoxy(0, 0);
	int i = 1, j;
	file =fopen("store.dat","rb");
	if (file == NULL)
	{
		gotoxy(20, 5);
		printf("Something went wrong :( ");
		getch();
		//customerMenu();
	}
	while (!feof(file))
	{
		fscanf(file, "%s %f %f\n", &Item1[i].name, &Item1[i].price, &Item1[i].discount);
		i++;
	}

	float total_quantity = 0, total_rate = 0;

	gotoxy(45, 5);
	printf("In buying section:\n\n\t\t\t\tItem:\t\tQuantity\tRate\n");
	for (j = 1; j < i; j++)
	{

		total_quantity = total_quantity + item[j].quantity;
		total_rate = total_rate + item[j].rate;
		printf("\t\t\t\t%s\t\t%.2f\t\t%.2f\n", Item1[j].name, Item1[j].price, Item1[j].discount);
	}
	printf("\n\n\t Total quantity : %.2f\n\n\t Total rate: %.2f\n\n\t Total cost: %.2f", total_quantity, total_rate, (total_quantity * total_rate));
	fclose(file);

	
	i = 1;
	file= fopen("store.dat", "rb");
	while (!feof(file))
	{
		fscanf(file, "%s %f %f\n", &Item1[i].name, &Item1[i].price, &Item1[i].discount);
		i++;
	}
	float total_quantityy = 0;
	float total_ratee = 0;

	printf("\n\t--------------------------------------------------------------------------------------------\n\t\t\t\t\t\tIn selling section:\n\n\t\t\t\tItem:\t\tQuantity\tRate\n");
	for (j = 1; j < i; j++)
	{

		total_quantityy = total_quantityy + Item1[j].price;
		total_ratee = total_ratee + Item1[j].discount;
		printf("\t\t\t\t%s\t\t%.2f\t\t%.2f\n", Item1[j].name, Item1[j].price, Item1[j].discount);
	}
	printf("\n\n\t Total quantity : %.2f\n\n\t Total rate: %.2f\n\n\t Total cost: %.2f", total_quantityy, total_ratee, (total_quantityy * total_ratee));
	fclose(file);

	float selling_price = (total_quantityy * total_ratee);
	float buying_price = (total_quantity * total_rate);
	float profit = selling_price - buying_price;
	float loss = buying_price - selling_price;
	if (selling_price > buying_price)
		printf("\n\t\t\t\t\tPROFIT by %.2f rupees.", profit);
	else
		printf("\n\n\t\t\t\t\tLOSS by %.2f rupees.", loss);
	gotoxy(0, 0);
}
void customerMenu() {
    char choice;
    do {
        system("cls");
        printf("\n\nCustomer Menu");
        printf("\n1. Place Order");
        printf("\n2. Back to Main Menu");
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
        case '1':
            placeOrder();
            break;
        case '2':
            return;
        default:
            printf("\nInvalid Choice!");
        }
        system("pause");
    } while (choice != '2');
}

// Main function
int main() {
    mainMenu();
    return 0;
}

