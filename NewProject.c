#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void menu();
void place_order();
void admin_menu();
void password();
void pass2();
void write_to_file();
void deleterec();
void disp_all();
void modify();
void display_sp(int n);

int itemno, num, i;
FILE *f, *file1, *file2, *file3;

// Struct to store the details
struct Item {
    int itemno;
    char iname[50];
    float price, dis;
} item;

// Delay function
void delayTime(int mseconds) {
    clock_t aim = mseconds + clock();
    while (aim > clock());
}

// Position cursor
void gotoxy(int x, int y) {
    COORD g;
    g.X = x;
    g.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), g);
}

// Draw border
void drawBorder(int a, int b, int length, int height) {
    gotoxy(a, b);
    int i, temp;
    for (i = 0; i < length; i++) {
        printf("%c", 200); // horizontal line
    }
    temp = b;
    for (i = 1; i < height; i++) {
        gotoxy(a, temp++); // vertical line
        printf("%c", 200);
    }
    for (i = 1; i < length; i++) {
        printf("%c", 200); // horizontal line
    }
    temp = b;
    for (i = 1; i < height; i++) {
        gotoxy(a, temp++); // vertical line
        printf("%c", 200);
    }
}

// Main function
int main() {
    system("COLOR 1A");
    int load;
    system("cls");
    gotoxy(50, 25);
    printf("WELCOME TEAM RIO");
    gotoxy(50, 15);
    printf("Loading......");
    for (load = 1; load < 20; load++) {
        delayTime(45);
        printf("%c", 200);
    }
    menu();
    return 0;
}

// Menu function
void menu() {
    system("cls");
    char menu1;

    drawBorder(5, 3, 100, 24);

    gotoxy(41, 6);
    printf("WELCOME TO ALO STORE 24x7:");

    gotoxy(30, 9);
    printf("\t\t1. Place Order\t\t2. Admin Menu\t\t3. Exit");
    gotoxy(42, 24);
    time_t currentTime;
    time(&currentTime);
    printf("%s\n", ctime(&currentTime));

    menu1 = getch();
    switch (menu1) {
    case '1':
        system("cls");
        place_order();
        break;
    case '2':
        system("cls");
        admin_menu();
        break;
    case '3':
        system("cls");
        drawBorder(5, 3, 100, 24);
        gotoxy(40, 13);
        printf("Press Y to exit and N to go back!");
        char character;
        character = getch();
        if (character == 'y' || character == 'Y') {
            gotoxy(40, 30);
            exit(0);
            break;
        } else {
            menu();
        }
        break;
    default:
        printf("\a");
        menu();
    }
}

// Function to get item data
void getdata(struct Item *item) {
    system("cls");
    printf("\n Please Enter The Item NO. of The Item --> \t");
    scanf("%d", &item->itemno);
    printf("\n Please Enter The Name of The Item --> \t");
    scanf("%s", item->iname);
    printf("\n Please Enter The Price of The Item --> \t");
    scanf("%f", &item->price);
    printf("\n Please Enter The Discount (%%) --> \t");
    scanf("%f", &item->dis);
}

// Function to show item data
void showdata(const struct Item *item) {
    system("cls");
    printf("\n The Item No. of The Item: %d", item->itemno);
    printf("\n The Name of The Item: %s", item->iname);
    printf("\n The Price of The Item : %.2f", item->price);
    printf("\n Discount : %.2f", item->dis);
}

// Function to write to file
void write_to_file() {
    f = fopen("store.dat", "ab");
    getdata(&item);
    fwrite(&item, sizeof(item), 1, f);
    fclose(f);
    printf("\n The Item Has Been Created ");
}

// Function to display all records from file
void disp_all() {
    system("cls");
    printf("\n\n\n\t Display all Records !!!\n\n");
    f = fopen("store.dat", "rb");
    while (fread(&item, sizeof(item), 1, f)) {
        showdata(&item);
        printf("\n\n ===================================\n");
    }
    fclose(f);
}

// Function to read specific records from file
void display_sp(int n) {
    int flag = 0;
    f = fopen("store.dat", "rb");
    while (fread(&item, sizeof(item), 1, f)) {
        if (item.itemno == n) {
            system("cls");
            showdata(&item);
            flag = 1;
        }
    }
    fclose(f);
    if (flag == 0) {
        printf("\n\n Record does not Exist");
    }
}

// Function to modify record of file
void modify() {
    int no, found = 0;
    system("cls");
    printf("\n\n\t To Modify");
    printf("\n\n\t Please Enter the Item No. of the Item: ");
    scanf("%d", &no);
    f = fopen("store.dat", "rb+");
    while (fread(&item, sizeof(item), 1, f) && found == 0) {
        if (item.itemno == no) {
            showdata(&item);
            system("cls");
            printf("\n Please Enter The Details of The Item \n");
            getdata(&item);
            fseek(f, -sizeof(item), SEEK_CUR);
            fwrite(&item, sizeof(item), 1, f);
            printf("\n\n\t Record Updated");
            found = 1;
        }
    }
    fclose(f);
    if (found == 0) {
        printf("\n\n Record Not Found \n");
    }
}

// Function to delete record of file
void deleterec() {
    int no;
    system("cls");
    drawBorder(5, 3, 100, 60);
    gotoxy(0, 0);
    gotoxy(45, 5);
    printf("\n\n\n\t Delete Record");
    printf("\n\n Please Enter The Item No. of The Item You want To Delete: ");
    scanf("%d", &no);
    f = fopen("store.dat", "rb");
    FILE* f2 = fopen("temp.dat", "wb");
    while (fread(&item, sizeof(item), 1, f)) {
        if (item.itemno != no) {
            fwrite(&item, sizeof(item), 1, f2);
        }
    }
    fclose(f2);
    fclose(f);
    remove("store.dat");
    rename("temp.dat", "store.dat");
    printf("\n\n\t Record Deleted..");
}

// Function to display all products price list
void menu() {
    system("cls");
    f = fopen("store.dat", "rb");
    if (!f) {
        printf("ERROR !!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File");
        printf("\n\n\n Program is Closing.....");
        exit(0);
    }

    printf("\n\n\t\t Item Menu\n\n");
    printf("======================================\n");
    printf("ITEM.NO.\t\t NAME\t\t PRICE\n");
    printf("=======================================\n");

    while (fread(&item, sizeof(item), 1, f)) {
        printf("%d\t\t%s\t\t%.2f\n", item.itemno, item.iname, item.price);
    }
    fclose(f);
}

// Function to place order and generate bill
void place_order() {
    system("cls");
    drawBorder(5, 3, 100, 60);
    gotoxy(0, 0);
    gotoxy(45, 5);

    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    printf("\n=============================");
    printf("\n Place Your ORDER");
    printf("\n=============================\n");
    do {
        printf("\n\n Enter The Item No. of The Item : \n");
        scanf("%d", &order_arr[c]);
        printf("\nQuantity in number : \n");
        scanf("%d", &quan[c]);
        c++;
        printf("\n DO You Want To Order Another Item ?(y/n)\t");
        getchar(); // To consume the newline character left by[_{{{CITATION{{{_1{](https://github.com/rsnpj/Inventory-Managment-System-in-C/tree/eee6dc8fd7d5cab79e1cfc051d37ae96bb4d0956/VeggieAid.c)
    }while (ch == 'y' || ch == 'Y');
    printf("\n\n Thank You For Placing The Order"); 
    system("cls");
    printf("\n\n *****************INVOICE*************\n");
    printf("\nItem No. \tName\tQuantity \tPrice\tAmount\tAmount after discount\n");
    for (int x = 0; x < c; x++) {
         f = fopen("store.dat", "rb"); 
         while (fread(&item, sizeof(item), 1, f)) { 
            if (item.itemno == order_arr[x]) { 
                amt = item.price * quan[x];
                damt = amt - (amt * item.dis / 100);
                printf("\n%d\t%s\t%d\t\t%.2f\t%.2f\t\t%.2f", order_arr[x], item.iname, quan[x], item.price, amt, damt); 
                total += damt; 
                }
            }
                fclose(f); 
     } printf("\n\t\t\t Total= %.2f\n", total);
}