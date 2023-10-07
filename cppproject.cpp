#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
#define getch() _getch()
#define short_line "========================="
#define long_line "=================================================="
#define stricts "**********************************************"
#define thin_line "____________________________________________"
using namespace std;

int k = 7, r = 0, flag = 0;
COORD coord = { 0, 0 };

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct Date
{
    int month, day, year;
};

ofstream fout;
ifstream fin;

class Product
{
    int ProductNumber;
    char fullname[25];
    Date D1;
public:
    void add_Products()
    {
        cout << "\n\tProduct No: ";
        cin >> ProductNumber;
        cout << "\n\tName of the Product: ";
        cin >> fullname;
        cout << "\n\tManufacturing date (dd-mm-yyyy): ";
        cin >> D1.month >> D1.day >> D1.year;
    }

    void show_Products()
    {
        cout << "\n\tProduct No (ID): ";
        cout << ProductNumber;
        // place for mukhammadali, int should be entered not STR!

        cout << "\n\tName of the Product: ";
        cout << fullname;
        cout << "\n\tDate : ";
        cout << D1.month << "-" << D1.day << "-" << D1.year;    
    }

    void Products_report()
    {
        gotoxy(3, k);
        cout << ProductNumber;
        gotoxy(13, k);
        puts(fullname);
    }

    int GetProduct_No()
    {
        return ProductNumber;
    }
};

class Amount : public Product
{
    float Product_price, Product_quantity, Product_tax, Product_gross, Product_discount, Product_TotalAmount;
public:
    void add_Products();
    void show_Products();
    void Products_report();
    void calculate_Products();
    void payment_window();
    float GetTotalAmount()
    {
        return Product_TotalAmount;
    }
} Amounts;

void Amount::add_Products()
{
    Product::add_Products();
    cout << "\n\n\tPrice: ";
    cin >> Product_price;
    cout << "\n\tQuantity: ";
    cin >> Product_quantity;
    cout << "\n\tTax percent: ";
    cin >> Product_tax;
    cout << "\n\tDiscount percent: ";
    cin >> Product_discount;
    calculate_Products();
    fout.write((char*)&Amounts, sizeof(Amounts));
    fout.close();
}
void Amount::calculate_Products()
{
    Product_gross = Product_price + (Product_price * (Product_tax / 100));
    Product_TotalAmount = Product_quantity * (Product_gross - (Product_gross * (Product_discount / 100)));
}
void Amount::show_Products()
{
    fin.open("Productstore.dat", ios::binary);
    fin.read((char*)&Amounts, sizeof(Amounts));
    Product::show_Products();
    cout << "\n\n\tTotal Amount: ";
    cout << Product_TotalAmount;
    fin.close();
}

void Amount::Products_report()
{
    Product::Products_report();
    gotoxy(25, k);
    cout << Product_price;
    gotoxy(35, k);
    cout << Product_quantity;
    gotoxy(46, k);
    cout << Product_tax;
    gotoxy(54, k);
    cout << Product_discount;
    gotoxy(66, k);
    cout << Product_TotalAmount;
    k = k + 1;
    if (k == 50)
    {
        gotoxy(25, 50);
        cout << "\n\n" << long_line << endl;
        cout << "Press any key to continue..." << endl;
        getch();
        k = 7;
        system("cls");
        gotoxy(32, 3);
        cout << " Product DETAILS " << endl;
        cout << long_line << endl;
        gotoxy(3, 5);
        cout << "Number (ID)";
        gotoxy(13, 5);
        cout << "Name";
        gotoxy(25, 5);
        cout << "Price";
        gotoxy(35, 5);
        cout << "Quantity";
        gotoxy(46, 5);
        cout << "Tax";
        gotoxy(54, 5);
        cout << "Deduction";
        gotoxy(66, 5);
        cout << "Total Amount";
    }
}

void Amount::payment_window()
{
    show_Products();
    cout << "\n\n\n\t\t"<<long_line;
    cout << "\n\t\t                 DETAILS                  ";
    cout << "\n\t\t"<<long_line;
    cout << "\n\n\t\tPrice                     :" << Product_price;
    cout << "\n\n\t\tQuantity                  :" << Product_quantity;
    cout << "\n\t\tTax percentage              :" << Product_tax;
    cout << "\n\t\tDiscount percentage         :" << Product_discount;
    cout << "\n\n\n\t\tNet amount              :Rs." << Product_TotalAmount;
    cout << "\n\t\t"<<stricts;
}

void anykey()
{
    cout << "\n\n" << long_line << endl;
    cout << "Press any key to continue..." << endl;
}

int main()
{
    system("COLOR 3");
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    fstream tmp("temp.dat", ios::binary | ios::out);
menu:
    system("cls");
    gotoxy(25, 2);
    cout << " Welcome to Super Market Billing System for Resource managers by 'UHope'!!! ";
    gotoxy(25, 3);
    cout << long_line <<"==========================" << endl << endl;
    cout << "\n\t\t1 - Get bill report\n\n";

    cout << "\t\t    |- Add     -|\n";
    cout << "\t\t2 --|- Remove  -|--PRODUCT\n";
    cout << "\t\t    |- Edit    -|\n\n";

    cout << "\t\t3 - Show all available product details\n\n";
    cout << "\t\t4 - Exit\n\n";
    cout << "\t\tPlease enter required option: ";
    int ch, ff;
    float gtotal;
    cin >> ch;
    switch (ch)
    {
    case 1:
    X1:
        system("cls");
        gotoxy(25, 2);
        cout << "Here is the menu for getting bill details";
        gotoxy(25, 3);
        cout << long_line<<"\n\n";
        cout << "\n\t\t1 - See all products list\n\n";
        cout << "\t\t2 - Clear database (delete all products) {!}\n\n";
        cout << "\t\t3 - Back to Main menu\n\n";
        cout << "\t\tPlease enter required option: ";
        int cho;
        cin >> cho;
        if (cho == 1)
        {
            system("cls");
            gotoxy(30, 3);
            cout << " Bill details ";
            gotoxy(3, 5);
            cout << "Pr.ID";
            gotoxy(13, 5);
            cout << "Name";
            gotoxy(25, 5);
            cout << "Price";
            gotoxy(35, 5);
            cout << "Quantity";
            gotoxy(46, 5);
            cout << "Tax %";
            gotoxy(54, 5);
            cout << "Discount %";
            gotoxy(65, 5);
            cout << "Total Amount";
            fin.open("Productstore.dat", ios::binary);
            if (!fin)
            {
                cout << "\n\nOOPS! Storage file not found...  :'-[";
                goto menu;
            }
            fin.seekg(0);
            gtotal = 0;
            while (!fin.eof())
            {
                fin.read((char*)&Amounts, sizeof(Amounts));
                if (!fin.eof())
                {
                    Amounts.Products_report();
                    gtotal += Amounts.GetTotalAmount();
                    ff = 0;
                }
                if (ff != 0) gtotal = 0;
            }
            gotoxy(17, k);
            cout << "\n\n\n\t\t\tGrand Total=" << gtotal;
            fin.close();
            anykey();
            getch();
        }
        else if (cho == 2)
        {
            system("cls");
            cout << "\n\n\t\tAre you sure? Do you want to delete all products?" << endl;
            string choiceyn;
            cout << "\t\tY/N: ";
            while (true)
            {
                cin >> choiceyn;
                if (choiceyn == "Y" || choiceyn == "y")
                {
                    ofstream fdel;
                    fdel.open("Productstore.dat", ios::binary | ios::trunc);
                    fdel.close();
                    cout << "All products have been deleted succesfully!" << endl;
                    anykey();
                    getch();
                    break;
                }
                else if (choiceyn == "N" || choiceyn == "n")
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice!! Plese, enter only Y or N: ";
                }
               
            }
        }
        else if (cho = 3)
        {
            goto menu;
        }
        goto X1;
    case 2:
    X2:
        system("cls");
        gotoxy(25, 2);
        cout << "Bill Editor";
        gotoxy(25, 3);
        cout << long_line << "\n\n";
        cout << "\n\t\t1 - Add product\n\n";
        cout << "\t\t2 - Edit existing Product\n\n";
        cout << "\t\t3 - Delete a product\n\n";
        cout << "\t\t4 - Back to Main Menu "<<endl;
        cout << thin_line << endl;
        cout << "\tEnter the option: ";
        int apc;
        cin >> apc;
        switch (apc)
        {
        case 1:
            fout.open("Productstore.dat", ios::binary | ios::app);
            Amounts.add_Products();
            cout << "\n\t\tProduct Added Successfully!";
            anykey();
            getch();
            goto X2;

        case 2:
            int Pr_no;
            flag = 0;
            cout << "\n\n\tEnter Product Number (ID) to be Edited :";
            //Mukhammaddali should make this guy to recieve only string
            cin >> Pr_no;

            fin.open("Productstore.dat", ios::binary);
            fout.open("Productstore.dat", ios::binary | ios::app);
            if (!fin)
            {
                cout << "\n\nOOPS! Storage file not found...  :'-[";
                goto menu;
            }
            fin.seekg(0);
            r = 0;
            while (!fin.eof())
            {
                fin.read((char*)&Amounts, sizeof(Amounts));
                if (!fin.eof())
                {
                    int x = Amounts.Product::GetProduct_No();
                    if (x == Pr_no)
                    {
                        flag = 1;
                        fout.seekp(r * sizeof(Amounts));
                        system("cls");
                        cout << "\n\t\tCurrent Details are" << endl;
                        Amounts.show_Products();
                        cout << thin_line << endl;
                        cout << "\n\n\t\tEnter New Details" << endl;
                        Amounts.add_Products();
                        cout << thin_line << endl;
                        cout << "\n\t\tProduct details updated succesfully!!!" << endl;
                    }
                }
                r++;
            }
            if (flag == 0)
            {
                cout << "\n"<< stricts;
                cout << "\n\t\tThere is no product with this numeber(ID)...Please Retry!" << endl;
                anykey();
                getch();
                goto X2;
            }
            fin.close();
            anykey();
            getch();
            goto X2;

        case 3:
            flag = 0;
            cout << "\n\n\tEnter Product Number(ID) to be deleted :";
            
            //This guy also should be edited by Mukhammadali
            cin >> Pr_no;

            fin.open("Productstore.dat", ios::binary);
            if (!fin)
            {
                cout << "\n\nOOPS! Storage file not found...  :'-[";
                goto menu;
            }

            fin.seekg(0);
            while (fin.read((char*)&Amounts, sizeof(Amounts)))
            {
                int x = Amounts.Product::GetProduct_No();
                if (x != Pr_no)
                    tmp.write((char*)&Amounts, sizeof(Amounts));
                else
                {
                    flag = 1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("Productstore.dat", ios::trunc | ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat", ios::binary | ios::in);
            if (!tmp)
            {
                cout << "OOPS! Error in file reading ...   :'-[";
                goto X2;
            }
            while (tmp.read((char*)&Amounts, sizeof(Amounts)))
                fout.write((char*)&Amounts, sizeof(Amounts));
            tmp.close();
            fout.close();
            if (flag == 1)
            {
                cout << "\n\t" << thin_line << endl;
                cout << "\t\tProduct succesfully deleted!!";
            }
            
            else if (flag == 0)
            {
                cout << "\n\t" << thin_line << endl;
                cout << "\t\tProduct does not Exist! Please Retry";
            }
            anykey();
            getch();
            goto X2;
        case 4:
            goto menu;
        default:
            cout << "\n\n\t\tWrong Choice!!! Retry";
            anykey();
            getch();
            goto X2;
        }
    case 3:
        system("cls");
        flag = 0;
        int Pr_no;
        cout << "\n\n\t\tEnter Product Number(ID) :";
        cin >> Pr_no;
        fin.open("Productstore.dat", ios::binary);
        if (!fin)
        {
            cout << "\n\nOOPS! Storage file not found...  :'-[" << endl;
            goto menu;
        }
        fin.seekg(0);
        while (fin.read((char*)&Amounts, sizeof(Amounts)))
        {
            int x = Amounts.Product::GetProduct_No();
            if (x == Pr_no)
            {
                Amounts.payment_window();
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            cout << "\n\t\tProduct does not exist....Please Retry!";
        anykey();
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        cout << "\n\n\t\t ===========|Thanks for using our programm|===========" << endl;
        getch();
        exit(0);
    default:
        cout << "\n\n\t\tWrong choice....Please Retry!";
        anykey();
        getch();
        goto menu;
    }
    return 0;
}
