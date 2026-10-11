#include<iostream>
#include<stdio.h>
#include<process.h>
#include<fstream>

using namespace std;

class item//class used
{
    int itemno;
    char iname[50];
    float price,qnt,tax,dis;
    public:
    void getdata(){
        system("cls");
        printf("\n Please Enter The Item NO. of The Item--> \t");
        cin>>itemno;
        cout<<"\n Please Enter The Name of The Item-->\t";
        cin>>iname;
        cout<<"\n Please Enter The Price of The Item-->\t";
        cin>>price;
        cout<<"\n please Enter The Discount (%) -->\t";
        cin>>dis;
    }
    void showdata(){
        system("cls");
        cout<<"\n The Item No. of The Item: "<<itemno;
        cout<<"\n The Name of The Item: "<<iname;
        cout<<"\n The Price of The Item : "<<price;
        cout<<"\n Discount : "<<dis;
    }
    int retitemno(){
        return itemno;
    }
    float retprice(){
        return price;
    }
    char* retiname(){
        return iname;
    }
    int retdis(){
        return dis;
    }

};
fstream f;//global declaration for stream object 
item i;

//function to write file
void write_to_file(){
    f.open("store.dat",ios::out|ios::app);
    i.getdata();
    f.write((char*)&i,sizeof(i));
    f.close();
    cout<<"\n The Item Has Been Created ";
}

//fintion to read all records from file
void disp_all(){
    system("cls");
    cout<<"\n\n\n\t Display all Records !!!\n\n";
    f.open("store.dat",ios::in);
    while(f.read((char*)&i,sizeof(i))){
        i.showdata();
        cout<<"\n\n ===================================\n";

    }
    f.close();
}

//function to read specific records from file
void display_sp(int n){
    int flag=0;
    f.open("store.dat",ios::in);
    while(f.read((char*)&i,sizeof(i))){

        if(i.retitemno()==n){

            system("cls");
            i.showdata();
            flag=1;
        }
    }
    f.close();
    if(flag==0){
        cout<<"\n\n Record does not Exist";
    }
}


    //function to modify record of file
void modify(){
        int no,found=0;
        system("cls");
        cout<<"\n\n\t To Modify";
        cout<<"\n\n\t Please Enter the Item No. of the Item";
        cin>>no;
        f.open("store.dat",ios::in|ios::out);
        while(f.read((char*)&i,sizeof(i)) && found==0){
            if(i.retitemno()==no){
                i.showdata();
                system("cls");

                cout<<"\n Please Enter The Details of The Item "<<endl;
                i.getdata();
                int pos=-1*((int)sizeof(i));
                f.seekp(pos,ios::cur);
                f.write((char*)&i,sizeof(i));
                cout<<"\n\n\t Record Updated";
                found=1;

            }
        }
        f.close();
        if(found==0){
            cout<<"\n\n Record Not Found \n";
        }
    }



//UFnction to delete record of file
void deleterec(){
    int no;
    system("cls");
    cout<<"\n\n\n\t Delete REcord";
    cout<<"\n\n Please Enter The Item No. of The Item You want To Delete";
    cin>>no;
    f.open("store.dat",ios::in|ios::out);
    fstream f2;
    f2.open("temp.dat",ios::out);
    f.seekg(0,ios::beg);
    while(f.read((char*)&i,sizeof(i))){
        if(i.retitemno()!=no){
            f2.write((char*)&i,sizeof(i));
        }
    }
    f2.close();
    f.close();
    remove("store.dat");
    rename("temp.dat","store.dat");
    cout<<"\n\n\t Record Deleted..";

}
//function to display all products price list
void menu(){
    system("cls");
    f.open("store.dat",ios::in);
    if(!f){
        cout<<"ERROR !!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
        cout<<"\n\n\n Program is Closing.....";
        exit(0);
    }

    cout<<"\n\n\t\t Item Menu\n\n";
    cout<<"======================================\n";
    cout<<"ITEM.NO.\t\t NAME\t\t PRICE\n";
    cout<<"=======================================\n";

    while(f.read((char*)&i,sizeof(i))){
        cout<<i.retitemno()<<"\t\t"<<i.retiname()<<"\t\t"<<i.retprice()<<endl;
    }
    f.close();
}

//function to place order and genarate bill
void place_order(){
    system("cls");
    int order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n=============================";
    cout<<"\n          Place Your ORDER";
    cout<<"\n=============================\n";
    do{
        cout<<"\n\n Enter The Item No. of The Item : \n";
        cin>>order_arr[c];
        cout<<"\nQuantity in number : \n";
        cin>>quan[c];
        c++;
        cout<<"\n DO You Want To Order Another Item ?(y/n)\t";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    cout<<"\n\n Thank You For Placing The Order";
    system("cls");
    cout<<"\n\n *****************INVOICE*************\n";
    cout<<"\nItem No. \tName\tQuantity \tPrice\tAmount\tAmount after discount\n";
    for(int x=0;x<=c;x++){
        f.open("store.dat",ios::in);
        f.read((char*)&i,sizeof(i));
        while(!f.eof()){
            if(i.retitemno()==order_arr[x]){
                amt=i.retprice()*quan[x];
                damt=amt-(amt*i.retdis()/100);
                cout<<"\n"<<order_arr[x]<<"\t"<<i.retiname()<<"\t"<<quan[x]<<"\t\t"<<i.retprice()<<"\t"<<amt<<"\t\t"<<damt;
                total+=damt;
            }
            f.read((char*)&i,sizeof(i));
        }
        f.close();
    }
    cout<<"\n\t\t\t Total= "<<total;

}

void admin_menu(){
    system("cls");
    char ch2;
    cout<<"\n\n\t Admin Menu:";
    cout<<"\n\t1.CREATE ITEM:";
    cout<<"\n\t2.DISPLAY ALL ITEMS";
    cout<<"\n\t3.QUERY";
    cout<<"\n\t4.MODIFY ITEM";
    cout<<"\n\t5.DELETE ITEM";
    cout<<"\n\t6.BACK TO MAIN MENU";
    cout<<"\n\n\t Please Enter Your Choice(1-6) \t";
    cin>>ch2;
    switch(ch2){
        case '1':system("cls");
        write_to_file();
        break;
        case '2':
        disp_all();
        break;
        case '3':
        int num;
        system("cls");
        cout<<"\n\n\t Please Enter The Item NO. ";
        cin>>num;
        display_sp(num);
        break;
        case '4':
        modify();
        break;
        case '5':
        deleterec();
        break;
        case '6':
        menu();
        break;
        default:
        cout<<"\a";admin_menu();
    }
}
int main(){
    //the main function to the program
    char ch;
    do{
        system("cls");
        cout<<"\n\n\n\t MAIN MENU";
        cout<<"\n\n\t 1.CUSTOMER";
        cout<<"\n\n\t 2.ADMINISTRATOR";
        cout<<"\n\n\t 3.EXIT";
        cout<<"\n\n\t Please Select Your Option (1-3)\t";
        cin>>ch;
        switch(ch){
            case '1':
            system("cls");
            place_order();
            break;
            case '2':
            admin_menu();
            break;
            case '3':
            exit(0);
            break;
            default:
            cout<<"\a";
        }
    }while(ch!='3');
    return 0;
}