#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int itemno;
    char iname[50];
    float price, dis;
} Item;

FILE *f;
void pass2()
{
	{

		system("cls");
		char ps[18];
		char password[25], temp;
		char correctpass[10] = "gaida"; //While running the program, type 1 if the program asks

	label:
		drawBorder(5, 3, 100, 24);
		gotoxy(40, 12);
		int f = 0;
		printf("Enter the password : ");

		while (1)
		{
			temp = getch();
			if (temp == 13)
				break;
			else if (f < 0)
			{
				printf("%d", f);
			}
			else if (temp == 8 && f)
			{
				printf("\b");
				printf(" ");
				printf("\b");
				f--;
			}
			else
			{
				password[f] = temp;
				printf("*");
				f++;
			}
		}

		password[f] = '\0';

		if ((strcmp(correctpass, password) == 0))
		{
			detailsShow();
		}

		else
		{
			int repass;
			system("cls");
			drawBorder(5, 3, 100, 24);
			gotoxy(40, 12);
			printf("Password Incorrect!!!");
			gotoxy(40, 15);
			printf("Press any key to re-enter the password.\n\t\t\t\t\tPress 'b' to go back...");
			repass = getch();
			if (repass == 'b')
			{
				menu();
			}
			else
			{
				system("cls");
				goto label;
			}
		}
	}
}

void delay(int mseconds) //for the loader to load
{
	clock_t goal = mseconds + clock();
	while (goal > clock())
		;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	//guiding gui to work like cui like on turbo C
}

void drawBorder(int a, int b, int length, int height)
{
	gotoxy(a, b); //goes to the co-ordinate provided
	int i, temp;  //temp created to increase the value of b temporarily
	for (i = 0; i < length; i++)
	{
		printf("%c", 219); //prints character 219 along the line horizontally
	}
	temp = b;
	for (i = 1; i < height; i++)
	{
		gotoxy(a, temp++); //prints a character and goes to next line <= on a loop (vertical line)
		printf("%c", 219);
	}
	for (i = 1; i < length; i++)
	{
		printf("%c", 219); //prints character 219 along the line horizontally
	}
	temp = b;
	for (i = 1; i < height; i++)
	{
		gotoxy(a + length, temp++); //goes to the end of length a and prints a charcter and goes to next line <= on a loop
		printf("%c", 219);
	}
}

void main()
{
	system("COLOR 0A"); //changes background color to black (0) and text color to green(A) color codes in the compiler
	int loader;
	system("cls");
	gotoxy(50, 25);
	printf("Developers : Gaida != Rhino");
	gotoxy(50, 15);
	printf("LOADING ");
	for (loader = 1; loader < 20; loader++)
	{
		delay(50);
		printf("%c", 219);
	}
	menu();
}

void menu()
{

	system("cls"); //Menu of the program

	char menu1;

	drawBorder(5, 3, 100, 24); //drwas border around the edge

	gotoxy(41, 6);
	printf("WELCOME TO DAFFODIL SHOP 24x7");

	gotoxy(30, 9);
	printf("1.Transaction\t\t2.View\t\t3.Exit");

	gotoxy(42, 24);
	time_t currentTime;
	time(&currentTime);
	printf("%s\n", ctime(&currentTime));

	menu1 = getch();

	switch (menu1)
	{
	case '1':
		system("cls");
		transaction();
		break;

	case '2':
		system("cls");
		showDetails();
		break;

	case '3':

		system("cls");
		drawBorder(5, 3, 100, 24);
		gotoxy(40, 13);
		printf("Press Y to exit and N to go back!");
		char character;
		character = getch();
		if (character == 'y' || character == 'Y')
		{
			gotoxy(40, 30);
			system("exit");
			break;
		}

		else
			menu();
		break;
		break;
	}
}

// Function to get item data from the user
void getdata(Item *i) {
    printf("\nEnter Item Number: ");
    scanf("%d", &i->itemno);
    getchar(); // To clear the newline character
    printf("Enter Item Name: ");
    fgets(i->iname, sizeof(i->iname), stdin);
    i->iname[strcspn(i->iname, "\n")] = '\0'; // Remove trailing newline
    printf("Enter Item Price: ");
    scanf("%f", &i->price);
    printf("Enter Discount (%%): ");
    scanf("%f", &i->dis);
}

// Function to display item data
void showdata(Item i) {
    printf("\nItem Number: %d\nItem Name: %s\nPrice: %.2f\nDiscount: %.2f%%\n",
           i.itemno, i.iname, i.price, i.dis);
}

// Function to write an item to the file
void write_to_file() {
    f = fopen("store.dat", "ab");
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

// Function to display all records from the file
void disp_all() {
    f = fopen("store.dat", "rb");
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

// Function to display a specific record
void display_sp(int n) {
    int found = 0;
    f = fopen("store.dat", "rb");
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

// Function to modify a record
void modify() {
    int no, found = 0;
    printf("\nEnter the Item Number to Modify: ");
    scanf("%d", &no);

    f = fopen("store.dat", "rb+");
    if (!f) {
        perror("Error opening file");
        return;
    }
    Item i;
    while (fread(&i, sizeof(Item), 1, f) && !found) {
        if (i.itemno == no) {
            printf("\nCurrent Record Details:\n");
            showdata(i);

            printf("\n\nEnter New Details:\n");
            getdata(&i);

            fseek(f, -sizeof(Item), SEEK_CUR);
            fwrite(&i, sizeof(Item), 1, f);
            printf("\nRecord Updated Successfully.\n");
            found = 1;
        }
    }
    fclose(f);
    if (!found) {
        printf("\nRecord Not Found.\n");
    }
}

// Function to delete a record
void deleterec() {
    int no;
    printf("\nEnter the Item Number to Delete: ");
    scanf("%d", &no);

    f = fopen("store.dat", "rb");
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

    remove("store.dat");
    rename("temp.dat", "store.dat");
    printf("\nRecord Deleted Successfully.\n");
}

// Function to display all items in menu format
void menu() {
    f = fopen("store.dat", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    Item i;
    printf("\n\nItem Menu:\n");
    printf("====================================\n");
    printf("ITEM NO\t\tNAME\t\tPRICE\n");
    printf("====================================\n");
    while (fread(&i, sizeof(Item), 1, f)) {
        printf("%d\t\t%s\t\t%.2f\n", i.itemno, i.iname, i.price);
    }
    fclose(f);
}

// Function to place an order and generate a bill
void place_order() {
    int order_arr[50], quan[50], count = 0;
    char ch;

    menu();
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
        f = fopen("store.dat", "rb");
        if (!f) {
            perror("Error opening file");
            return;
        }
        Item i;
        while (fread(&i, sizeof(Item), 1, f)) {
            if (i.itemno == order_arr[x]) {
                float amt = i.price * quan[x];
                float damt = amt - (amt * i.dis / 100);
                printf("%d\t%s\t%d\t\t%.2f\t%.2f\t%.2f\n", order_arr[x], i.iname, quan[x], i.price, amt, damt);
                total += damt;
            }
        }
        fclose(f);
    }
    printf("\nTotal Amount: %.2f\n", total);
}

// Admin menu
void admin_menu() {
    int choice;
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

// Main function
int main() {
    int choice;
    do {
        printf("\nMain Menu:");
        printf("\n1. Customer");
        printf("\n2. Administrator");
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
    return 0;
}
void pass2()
{
	{

		system("cls");
		char ps[18];
		char password[25], temp;
		char correctpass[10] = "gaida"; //While running the program, type 1 if the program asks

	label:
		drawBorder(5, 3, 100, 24);
		gotoxy(40, 12);
		int f = 0;
		printf("Enter the password : ");

		while (1)
		{
			temp = getch();
			if (temp == 13)
				break;
			else if (f < 0)
			{
				printf("%d", f);
			}
			else if (temp == 8 && f)
			{
				printf("\b");
				printf(" ");
				printf("\b");
				f--;
			}
			else
			{
				password[f] = temp;
				printf("*");
				f++;
			}
		}

		password[f] = '\0';

		if ((strcmp(correctpass, password) == 0))
		{
			detailsShow();
		}

		else
		{
			int repass;
			system("cls");
			drawBorder(5, 3, 100, 24);
			gotoxy(40, 12);
			printf("Password Incorrect!!!");
			gotoxy(40, 15);
			printf("Press any key to re-enter the password.\n\t\t\t\t\tPress 'b' to go back...");
			repass = getch();
			if (repass == 'b')
			{
				menu();
			}
			else
			{
				system("cls");
				goto label;
			}
		}
	}
}
