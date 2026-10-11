#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

typedef struct {
    int itemno;
    char iname[50];
    float price, dis;
} Item;

FILE *f;

// Delay function
void delay(int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// Gotoxy function for console cursor positioning
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Draw border function
void drawBorder(int a, int b, int length, int height) {
    gotoxy(a, b);
    for (int i = 0; i < length; i++) printf("%c", 219);
    for (int i = 1; i < height; i++) {
        gotoxy(a, b + i);
        printf("%c", 219);
    }
    for (int i = 0; i < length; i++) {
        gotoxy(a, b + height);
        printf("%c", 219);
    }
    for (int i = 1; i < height; i++) {
        gotoxy(a + length, b + i);
        printf("%c", 219);
    }
}

// Get item data from user
void getdata(Item *i) {
    printf("\nEnter Item Number: ");
    scanf("%d", &i->itemno);
    getchar();
    printf("Enter Item Name: ");
    fgets(i->iname, sizeof(i->iname), stdin);
    i->iname[strcspn(i->iname, "\n")] = '\0';
    printf("Enter Item Price: ");
    scanf("%f", &i->price);
    printf("Enter Discount (%%): ");
    scanf("%f", &i->dis);
}

// Display item data
void showdata(Item i) {
    printf("\nItem Number: %d\nItem Name: %s\nPrice: %.2f\nDiscount: %.2f%%\n", i.itemno, i.iname, i.price, i.dis);
}

// Write item to file
void write_to_file() {
    f = fopen("store1.dat", "ab");
    if (!f) {
        perror("Error opening file");
        return;
    }
    Item i;
    getdata(&i);
    fwrite(&i, sizeof(Item), 1, f);
    fclose(f);
    printf("\nItem has been created.\n");
}

// Display all records
void disp_all() {
    f = fopen("store1.dat", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    Item i;
    printf("\n\nDisplaying All Records:\n");
    while (fread(&i, sizeof(Item), 1, f)) {
        showdata(i);
        printf("-------------------------------\n");
    }
    fclose(f);
}

// Display specific record
void display_sp(int n) {
    int found = 0;
    f = fopen("store1.dat", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    Item i;
    while (fread(&i, sizeof(Item), 1, f)) {
        if (i.itemno == n) {
            showdata(i);
            found = 1;
            break;
        }
    }
    fclose(f);
    if (!found) {
        printf("\nRecord does not exist.\n");
    }
}

// Modify a record
void modify() {
    int no, found = 0;
    printf("\nEnter the Item Number to Modify: ");
    scanf("%d", &no);
    f = fopen("store1.dat", "rb+");
    if (!f) {
        perror("Error opening file");
        return;
    }
    Item i;
    while (fread(&i, sizeof(Item), 1, f)) {
        if (i.itemno == no) {
            printf("\nCurrent Record Details:\n");
            showdata(i);
            printf("\nEnter New Details:\n");
            getdata(&i);
            fseek(f, -sizeof(Item), SEEK_CUR);
            fwrite(&i, sizeof(Item), 1, f);
            printf("\nRecord Updated Successfully.\n");
            found = 1;
            break;
        }
    }
    fclose(f);
    if (!found) {
        printf("\nRecord Not Found.\n");
    }
}

// Delete a record
void deleterec() {
    int no;
    printf("\nEnter the Item Number to Delete: ");
    scanf("%d", &no);
    f = fopen("store1.dat", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Error creating temporary file");
        fclose(f);
        return;
    }
    Item i;
    while (fread(&i, sizeof(Item), 1, f)) {
        if (i.itemno != no) {
            fwrite(&i, sizeof(Item), 1, temp);
        }
    }
    fclose(f);
    fclose(temp);
    remove("store1.dat");
    rename("temp.dat", "store1.dat");
    printf("\nRecord Deleted Successfully.\n");
}

// Password check for admin
int pass2() {
    char password[25], temp;
    const char correctpass[] = "DIU089";
    int f = 0;
    drawBorder(5, 3, 100, 24);
    gotoxy(40, 12);
    printf("Enter the password: ");
    while (1) {
        temp = getch();
        if (temp == 13) break; // Enter key
        if (temp == 8 && f > 0) { // Backspace
            printf("\b \b");
            f--;
        } else {
            password[f++] = temp;
            printf("*");
        }
    }
    password[f] = '\0';
    return strcmp(correctpass, password) == 0;
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
            case 1:
                write_to_file();
                break;
            case 2:
                disp_all();
                break;
            case 3: {
                int num;
                printf("\nEnter Item Number to Query: ");
                scanf("%d", &num);
                display_sp(num);
                break;
            }
            case 4:
                modify();
                break;
            case 5:
                deleterec();
                break;
            case 6:
                return;
            default:
                printf("\nInvalid Choice! Try again.\n");
        }
    } while (choice != 6);
}

// Place an order
void place_order() {
    int order_arr[50], quan[50], count = 0;
    char ch;
    disp_all();
    printf("\nPlace Your Order:\n");
    do {
        printf("\nEnter Item Number: ");
        scanf("%d", &order_arr[count]);
        printf("Enter Quantity: ");
        scanf("%d", &quan[count]);
        count++;
        printf("Do you want to order another item? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
    printf("\nGenerating Invoice...\n");
    float total = 0;
    printf("Item No\tName\tQuantity\tPrice\tAmount\tAmount after Discount\n");
    for (int x = 0; x < count; x++) {
        f = fopen("store1.dat", "rb");
        if (!f) {
            perror("Error opening file");
            return;
        }
        Item i;
        while (fread(&i, sizeof(Item), 1, f)) {
            if (i.itemno == order_arr[x]) {
                float amt = i.price * quan[x];
                float damt = amt - (amt * i.dis / 100);
                total += damt;
                printf("%d\t%s\t%d\t%.2f\t%.2f\t%.2f\n", i.itemno, i.iname, quan[x], i.price, amt, damt);
            }
        }
        fclose(f);
    }
    printf("\nTotal: %.2f\n", total);
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
            case 1:
                place_order();
                break;
            case 2:
                admin_menu();
                break;
            case 3:
                exit(0);
            default:
                printf("\nInvalid Choice! Try again.\n");
        }
    } while (choice != 3);
}

// Main function
int main() {
    menu();
    return 0;
}
