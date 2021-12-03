//Manasvi Goyal DTU

#include <iostream>
#include<conio.h>
#include<string.h>
#include <cmath>

using namespace std;

class User;

class Display
{
    public:
        void firstScreen();
        void indexOutlook();
        void printStar(int n);
        void welcome();
};

class Menu
{
    protected:
    int id;
    char itemName[25];
    int rate;
    public:
        friend class Staff;
        friend class CustomerMain;
        void readMenu();
        void showMenu();
        int getNewId();
        bool isDuplicateItem(char[]);
};

class Customer
{
	public:
        char customerName[20];
        int tableNumber;
        int orderListId[10];
};

class CustomerMain
{
    public :
        void customerPage();
        bool isNotvalidTable(int);
        void orderFood();
        int showBill(int);
        void checkOut(int);
};

class Admin : public Display
{
    private:
        char userId[20];
        char userPass[20];
    public:
        bool isValidateAdmin();
        bool isValidateUser();
        virtual void adminPage() = 0;
};

class AdminSubclass : public Admin
{
   public:
        void adminMain(int i);
        void adminPage();
        void addStaff(User&);
        void showStaff(User&);
        void deleteStaff(User&, char*);
};

class User
{
    private:
        char uid[20];
        char password[20];

    public:
        char* getuid()
        {
            return uid;
        }
        char* getpassword()
        {
            return password;
        }
        friend void AdminSubclass::addStaff(User& u);
        friend void AdminSubclass::showStaff(User& u);
        friend void AdminSubclass::deleteStaff(User& u, char* id);
};

class Staff : public AdminSubclass
{
    public:
        void staffMain(int);
        void staffPage();
        void addFood();
        void viewFood();
        void editCost(Menu&);
};

void Menu::readMenu()
{
	FILE *fp;
	Menu m;
	AdminSubclass a;
	fp=fopen("FoodMenu.txt","a");
	if(fp==NULL)
    {
		cout<<"File cannot be opened! \n";
		cout<<"Press any key to continue\n";
		fclose(fp);
	}
	else
	{
		m.id=getNewId();
		cout<<"Enter Item Name: ";
		cin>>m.itemName;
		cout<<"Enter Item Price: ";
		cin>>m.rate;
		if(isDuplicateItem(itemName))
        {
			cout<<"\nThis item is already in the file!!!\n\n";
			cout<<"\nEnter a new item or edit the cost.\n\n";
			fclose(fp);
			cout<<"\nPress any key to continue...\n";
            getch();
            system("cls");
            fclose(fp);
            a.adminPage();
		}
		else
		{
            fwrite(&m,sizeof(Menu),1,fp);
            cout<<"\nItem successfully added\n";
            fclose(fp);
            cout<<"\nPress any key to continue...\n";
            getch();
            system("cls");
		}
    }
    fclose(fp);
}

void Menu::showMenu()
{
	Menu m;
	FILE *fp;
	fp=fopen("FoodMenu.txt","r");
	if(fp==NULL)
    {
		cout<<"File cannot be opened! \n";
		cout<<"Press any key to continue\n";
		fclose(fp);
	}
	else
	{
		cout<<"\nId:  Item Name:\t\tPrice(Rs.):\n";
		while(fread(&m,sizeof(Menu),1,fp)){
			cout<<m.id<<"    "<<m.itemName<<"\t\t"<<m.rate<<"\n";
		}
		cout<<endl;
		fclose(fp);
	}
}

int Menu::getNewId()
{
	int countId=1;
	FILE *fp;
	Menu m;
	fp=fopen("FoodMenu.txt","r");
	if(fp==NULL)
    {
		cout<<"cannot be opened file in getNewId \n";
	}
	else
	{
		while(fread(&m,sizeof(Menu),1,fp))
		{
            countId++;
		}
        fclose(fp);
	}
	fclose(fp);
	return countId;
}

bool Menu::isDuplicateItem(char item[30])
{
	bool result=false;
	FILE *fp;
	Menu m;
	fp=fopen("FoodMenu.txt","r");
	if(fp==NULL)
    {
		cout<<"Cannot open file! \n";
	}
	else
	{
		while(fread(&m,sizeof(Menu),1,fp))
		{
            if(strcmp(m.itemName,item)==0)
            {
                result=true;
            }
		}
		fclose(fp);
	}
	fclose(fp);
	return result;
}

void AdminSubclass::adminPage()
{
	char choice;
	User uf;
    Menu x;
	Staff s;
	char id[20];
	printStar(40);
	cout<<"ADMIN...\n";
	cout<<"1. Add staff to the database \n";
	cout<<"2. Show staff data \n";
    cout<<"3. Delete staff data \n";
    cout<<"4. Go to Staff page \n";
    cout<<"5. Go to previous page \n";
	printStar(40);
	cout<<"Enter your choice: ";
	cin>>choice;
	switch(choice)
    {
        case '1':
            addStaff(uf);
            break;
        case '2':
            showStaff(uf);
            break;
        case '3':
            cout<<"Enter User ID to be deleted: ";
            cin>>id;
            deleteStaff(uf,id);
            break;
        case '4':
            system("cls");
            s.staffPage();
            break;
        case '5':
            system("cls");
            welcome();
            break;
        default:
        {
            cout<<"Enter a valid option! \n";
            cout<<"Enter any key to continue... \n";
            getch();
            system("cls");
            adminPage();
        }
    }
}

void AdminSubclass::adminMain(int i)
{
	system("cls");
	if(isValidateAdmin())
    {
		cout<<"\nLogin Successful!\n";
		cout<<"Press any key to continue...\n";
		getch();
		system("cls");
		adminPage();
	}
    else
    {
		cout<<"\n\nPlease Enter valid Id or Password. You have "<<3-i<<" option(s) remaining. \n";
		cout<<"Enter any key to continue...\n";
		getch();
		if(i<3)
		{
            adminMain((i+1));
		}
		else
		{
            cout<<"\nYou entered more than 3 wrong password...\n";
            cout<<"Please try again later. Thank you! \n";
            exit(0);
        }
    }
}

void AdminSubclass::addStaff(User& u)
{
    FILE *fp;
    fp=fopen("UserFile.txt","a");
    if(fp==NULL)
    {
        cout<<"File cannot be opened!!";
        cout<<"Press any key to continue\n";
        getch();
        system("cls");
        adminPage();
    }
    else
    {
        cout<<"\nEnter User ID to add: ";
        cin>>u.uid;
        cout<<"Enter User Password to add: ";
        cin>>u.password;
        fwrite(&u,sizeof(User),1,fp);
        fclose(fp);
        if(fwrite!=NULL)
        {
            cout<<"\nFile successfully written \n";
            cout<<"Press any key to continue... \n";
            getch();
            system("cls");
            adminPage();
        }
        else
        {
            cout<<"Failed to write to file!!! \n";
            cout<<"Press any key to continue... \n";
            getch();
            system("cls");
            adminPage();
        }
    }
}

void AdminSubclass::showStaff(User& u)
{
	FILE *fp;
	fp=fopen("UserFile.txt","rb");
	if(fp==NULL)
    {
		cout<<"File cannot be opened! \n";
		cout<<"Press any key to continue\n";
		fclose(fp);
	}
	else
	{
		cout<<"User Id:\tPassword:\n";
		while(fread(&u,sizeof(User),1,fp)!=NULL)
        {
			cout<<u.uid<<"\t\t"<<u.password<<"\n";
		}
		fclose(fp);
        cout<<"\nPress any key to continue... \n";
        getch();
        system("cls");
        adminPage();
	}
}

void AdminSubclass::deleteStaff(User& u, char* userid)
{
	FILE *fp;
	FILE *ftemp;
	int found=0;
    fp=fopen("UserFile.txt","rb");
    if(fp==NULL)
    {
        cout<<"File cannot be opened!!";
        cout<<"Press any key to continue\n";
        getch();
        system("cls");
        adminPage();
    }

	ftemp=fopen("temp.txt", "wb");
	if(ftemp==NULL)
    {
        cout<<"File cannot be opened!!";
        cout<<"Press any key to continue\n";
        getch();
        system("cls");
        adminPage();
    }

	while (fread(&u,sizeof(User),1,fp)!= NULL)
    {
		if (strcmp (userid, u.uid) == 0)
        {
			cout<<"\nStaff record deleted.\n";
			found=1;
		}
        else
        {
			fwrite(&u, sizeof(User), 1, ftemp);
		}
	}

	if (!found)
    {
		cout<<"\nNo record found with the requested User ID: "<<userid;
	}

	fclose(fp);
	fclose(ftemp);

	remove("UserFile.txt");
	rename("temp.txt", "UserFile.txt");
    cout<<"\nPress any key to continue... \n";
    getch();
    system("cls");
    adminPage();
}

void Staff::addFood()
{
    Menu m;
    m.readMenu();
	staffPage();
}

void Staff::viewFood()
{
    Menu m;
    m.showMenu();
	cout<<"Enter any key to continue...\n\n";
	getch();
	system("cls");
	staffPage();
}

void Staff::editCost(Menu& x)
{
	FILE *fp;
	FILE *fp1;
	char foodName[20];
	fp1=fopen("temp.txt","w");
	fp=fopen("FoodMenu.txt","r");
	if(fp==NULL)
    {
		cout<<"File cannot be opened!\n";
		cout<<"Press any key to continue\n";
		getch();
		system("cls");
		staffPage();
	}
	else
    {
		cout<<"Enter food name to edit: ";
		cin>>foodName;
        int flag=0;
		while(fread(&x,sizeof(Menu),1,fp))
        {
            if(strcmp(foodName,x.itemName)!=0)
            {
                fwrite(&x,sizeof(Menu),1,fp1);
            }
            else
            {
                cout<<"Enter the price of "<<foodName<<" item: ";
                cin>>x.rate;
                flag=1;
                cout<<"Price changed sucessfully.\n";
                fwrite(&x,sizeof(Menu),1,fp1);

            }
		}

		if (flag==0)
            cout<<"No food item with this name!\n";
		fclose(fp);
		fclose(fp1);

		fp1=fopen("temp.txt","r");
        fp=fopen("FoodMenu.txt","w");

        while(fread(&x,sizeof(Menu),1,fp1))
        {
			fwrite(&x,sizeof(Menu),1,fp);
		}
		fclose(fp);
		fclose(fp1);
	}
}

bool Admin::isValidateAdmin()
{
    cout<<"Enter User Id: \n";
    cin>>userId;
    cout<<"Enter User Password: \n";
    int p=0;
    do
    {
        userPass[p]=getch();
        if(userPass[p]!='\r')
        {
            cout<<"*";
        }
        p++;
    }while(userPass[p-1]!='\r');

    userPass[p-1]='\0';
    if((strcmp(userId,"admin")==0&&strcmp(userPass,"admin")==0))
    {
        return 1;
    }
    return 0;
}

bool Admin::isValidateUser()
{
    FILE *fp;
    User u;
    fp=fopen("UserFile.txt","r");
    cout<<"Enter User Id: \n";
    cin>>userId;
    cout<<"Enter User Password: \n";
    int p=0;
    do
    {
        userPass[p]=getch();
        if(userPass[p]!='\r')
        {
            cout<<"*";
        }
        p++;
    }while(userPass[p-1]!='\r');

    userPass[p-1]='\0';

    if(fp==NULL)
    {
        if((strcmp(userId,"admin")==0&&strcmp(userPass,"admin")==0))
        {
            return 1;
        }
    }
    while(fread(&u,sizeof(User),1,fp))
    {
        if((strcmp(userId,u.getuid())==0&&strcmp(userPass,u.getpassword())==0)||(strcmp(userId,"admin")==0&&strcmp(userPass,"admin")==0))
        {
            return 1;
        }
    }
    return 0;
}

void Staff::staffMain(int i)
{
	int choice;
    system("cls");
	if(isValidateUser())
    {
        cout<<"\nLogin Successful!\n";
		cout<<"Press any key to continue...\n";
		getch();
        system("cls");
		staffPage();
	}
	else
    {
		cout<<"\n\nPlease Enter valid Id or Password. You have "<<3-i<<" option(s) remaining. \n";
		cout<<"Press any key to continue...\n";
		getch();
		if(i<3)
		{
            staffMain((i+1));
		}
		else
		{
            cout<<"\nYou entered more than 3 wrong password...\n";
            cout<<"Please try again later. Thank you! \n";
            exit(0);
        }

	}
}

void Staff::staffPage()
{
	char choice;
	User uf;
	printStar(40);
	cout<<"STAFF...\n";
	cout<<"1. Add food item to the menu \n";
	cout<<"2. Show the food item in menu \n";
	cout<<"3. Edit cost of food item \n";
	cout<<"4. Go to previous page \n";
	printStar(40);
	Menu x;
	cout<<"Enter your choice: ";
	cin>>choice;
	switch(choice)
    {
        case '1':
            addFood();
            break;
        case '2':
            viewFood();
            break;
        case '3':
            editCost(x);
            cout<<"\nEnter any key to continue...\n\n";
            getch();
            system("cls");
            staffPage();
            break;
        case '4':
            system("cls");
            welcome();
            break;
        default:
        {
            cout<<"Enter a valid option! \n";
            cout<<"\nEnter any key to continue... \n";
            getch();
            system("cls");
            staffPage();
        }
    }
}


void CustomerMain::customerPage()
{
    system("cls");
	Menu m;
	Display d;
	char choice;
	int tableno;
	d.printStar(40);
	cout<<"CUSTOMER...\n";
	cout<<"1. View Menu \n";
	cout<<"2. Order Food \n";
	cout<<"3. Show Bill \n";
	cout<<"4. Pay bill and checkout \n";
    cout<<"5. Go to previous menu \n";
	d.printStar(40);
    cout<<"Enter your choice: ";
	cin>>choice;
    switch(choice)
    {
        case '1':
        {
            m.showMenu();
            cout<<"\nPress any key to continue...\n\n";
            getch();
            customerPage();
        }
            break;
        case '2':
            orderFood();
            break;
        case '3':
            cout<<"Enter table number: ";
            cin>>tableno;
            while(!isNotvalidTable(tableno))
            {
                cout<<"\nTable Not Occupied! No Bill Record!\nEnter Valid table Number: ";
                cin>>tableno;
            }
            showBill(tableno);
            cout<<"Press any key to continue... \n";
            getch();
            customerPage();
            break;
        case '4':
            cout<<"Enter table number: ";
            cin>>tableno;
            while(!isNotvalidTable(tableno))
            {
                cout<<"\nTable Not Occupied! No Bill Record!\nEnter Valid table Number: ";
                cin>>tableno;
            }
            checkOut(tableno);
            break;
        case '5':
            system("cls");
            d.welcome();
            break;
        default:
        {
            cout<<"Enter valid option!\n";
			cout<<"Press any key to continue...\n";
            getch();
            customerPage();
        }
    }
}

void CustomerMain::orderFood()
{
    int itemId;
    char ch;
    Menu m;
    Customer c;
    cout<<"Enter your name: ";
    cin>>c.customerName;
    cout<<"Enter your table number: ";
    cin>>c.tableNumber;
    while(isNotvalidTable(c.tableNumber))
    {
        cout<<"\nTable Already Occupied!\nEnter Another table Number: ";
        cin>>c.tableNumber;
    }
    cout<<"\n\n Today's Menu \n\n";
    m.showMenu();
    int i=0;
    do
    {
        cout<<"\nEnter the food id to order: ";
        cin>>c.orderListId[i];
        i++;
        cout<<"Do you want to add another item to your order? [Y/N]: ";
        cin>>ch;
    }while(ch=='Y'|| ch=='y');

    FILE *fp;
    fp=fopen("orderList.txt","ab");
    if(fp==NULL)
    {
        cout<<"File cannot be opened!!\n";
    }
    else
    {
        fwrite(&c,sizeof(Customer),1,fp);
        fclose(fp);
    }
    cout<<"Enter any key to continue...\n";
    getch();
    customerPage();
}

int CustomerMain::showBill(int tn)
{
    Customer c;
    FILE *fp,*fp1;
    Menu m;
    float totalcost=0,gst=0,bill=0;
    int billamount;
    fp=fopen("orderList.txt","rb");
	if(fp==NULL)
    {
        cout<<"File cannot be opened!!\n";
    }
    else
    {
        while(fread(&c,sizeof(Customer),1,fp))
        {
            if(c.tableNumber==tn)
            {
                cout<<"\nYour name : "<<c.customerName;
                cout<<"\nTable Number: "<<tn<<"\n";
                int k=0;
                cout<<"\n\t\tBill: \n\n";
                cout<<"\t------------------------------------------------\n";
                cout<<"\t|\tItem Name\t\tPrice(Rs.)\t|\n";
                cout<<"\t------------------------------------------------\n";
                while(c.orderListId[k])
                {
                    fp1=fopen("FoodMenu.txt","r");
                    while(fread(&m,sizeof(Menu),1,fp1))
                    if(c.orderListId[k]==m.id)
                    {
                        cout<<"\t|\t"<<m.itemName<<"\t\t\t"<<m.rate<<"\t\t|\n";
                        totalcost+=m.rate;
                        gst=totalcost*18/100;
                        bill=totalcost+gst;
                        billamount=round(bill);
                    }
                    fclose(fp1);
                    k++;
                }
                cout<<"\t|\tOrder Total\t\t"<<totalcost<<"\t\t|";
                cout<<"\n\t|\tGST(18%)\t\t"<<gst<<"\t\t|";
                cout<<"\n\t------------------------------------------------";
                cout<<"\n\t|\tBill Amount\t\t"<<bill<<"\t\t|\n";
                cout<<"\t------------------------------------------------\n\n";

            }
        }
        fclose(fp);
        fclose(fp1);
    }
    return billamount;
}

void CustomerMain::checkOut(int tableno)
{
	FILE *fp;
	FILE *ftemp;
	int found=0;
	float change=0, bill, billpaid;
	Customer c;
    fp=fopen("orderList.txt","rb");
    if(fp==NULL)
    {
        cout<<"File cannot be opened!!";
    }
	ftemp=fopen("templist.txt", "wb");
	if(ftemp==NULL)
    {
        cout<<"File cannot be opened!!";
    }
	while (fread(&c,sizeof(Customer),1,fp)!= NULL)
    {
		if (tableno == c.tableNumber)
        {
			bill=showBill(tableno);
            do
            {
                cout<<"\n\nThe amount to be paid is Rs. "<<bill;
                cout<<"\nPay the bill amount: ";
                cin>>billpaid;
                if (billpaid>bill)
                {
                    change=billpaid-bill;
                    cout<<"\nRs. "<<bill<<" paid. Thank you! Here is Rs."<<change<<" change";
                    billpaid=bill;
                }
                else if (billpaid<bill)
                {
                    change=bill-billpaid;
                    cout<<"\nRs. "<<bill<<" paid. Please pay Rs."<<change<<" more";
                    bill=change;
                }
                else
                {
                    cout<<"\nRs. "<<bill<<" paid. Thank you!";
                }
			} while (billpaid!=bill);
            found=1;
		}
        else
        {
			fwrite(&c, sizeof(Customer), 1, ftemp);
		}
	}

	if (!found)
    {
		cout<<"\nNo table found with the requested Table no.: "<<tableno;
	}

	fclose(fp);
	fclose(ftemp);

	remove("orderList.txt");
	rename("templist.txt", "orderList.txt");
	if (found==1)
    {
        cout<<"\n\nThank you for visiting. Have a nice day!\n\n";
        exit(0);
    }
    cout<<"\nPress any key to continue... \n";
    getch();
    system("cls");
    customerPage();
}

bool CustomerMain::isNotvalidTable(int a)
{
	FILE *fp;
	bool result=false;
    Customer c;
	fp=fopen("orderList.txt","r");
    if(fp==NULL)
    {
        cout<<"File cannot be opened!!!\n";
    }
    else
    {
        while(fread(&c,sizeof(Customer),1,fp))
        {
			if(c.tableNumber==a)
			{
				result=true;
			}
        }
		fclose(fp);
		return result;
    }
}



void Display::firstScreen()
{
    system("cls");
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t\t******************************************************** \n";
    cout<<"\t\t\t\t\t\t Welcome to MG Restaurant \n";
    cout<<"\t\t\t\t******************************************************** \n";
    cout<<"\n\n\n\t\t\t\t\t\tPress any key to continue\n";
    getch();
    system("cls");
}

void Display::indexOutlook()
    {
	cout<<"Select User \n";
	cout<<"1. Customer \n";
	cout<<"2. Admin \n";
	cout<<"3. Staff \n";
	cout<<"4. Exit \n";
    }

void Display::printStar(int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<"*";
    }
    cout<<"\n";
}

void Display::welcome()
{
    char choice;
    AdminSubclass as;
    CustomerMain cm;
    Staff s;
    printStar(20);
    indexOutlook();
    printStar(20);
    cout<<"Enter your choice: ";
    cin>>choice;

    switch(choice)
    {
        case '1':
            cm.customerPage();
            break;
        case '2':
            as.adminMain(1);
            break;
        case '3':
            s.staffMain(1);
            break;
        case '4':
            cout<<"\n\nThank you for visiting. Have a nice day!\n\n";
            exit(0);
            break;
        default:
        {
            cout<<"Invalid choice!\n";
            cout<<"Press any key to continue...\n";
            getch();
            system("cls");
            welcome();
        }
    }
}

int main()
{
	Display d;
	d.firstScreen();
	d.welcome();
	getch();
	return 0;
}
