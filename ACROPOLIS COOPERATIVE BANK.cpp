#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string.h>
#include<stdlib.h>
using namespace std;

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();   	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	            //function to add new data
	void dep(int);	           //function to accept amount and add to balance amount
	void draw(int);	       	   //function to accept amount and subtract from balance amount
	void report() const;	  //function to show data in tabular format
	int retacno() const;   	 //function to return account number
	int retdeposit() const;	 //function to return balance amount
	char rettype() const;    //function to return type of account
};        

void account::create_account()
{
	repeat:
	cout<<"\n\nEnter The account No. of five digits:";
	cin>>acno;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    account ac;
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==acno)
		{
            cout<<"\n\n\t\tAccount already exist, please enter a different account number..."<<endl;
            return;
		}
	}
	int count=0;
	int c=acno;
	while(c!=0)
	{
	    c=c/10;
	    count++;
	}
	if(count!=5)
	{
	    cout<<"Please enter valid account no.!! ";
	    goto repeat;
	}
	
	cout<<"\nEnter The Full Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	repeat1:
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	if(!(type=='S' || type=='C'))
	{
	    cout<<"\nInvalid Type!!";
	    goto repeat1;
	}
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}

void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	repeat1:
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	if(!(type=='S' || type=='C'))
	{
	    cout<<"\nInvalid Type!!";
	    goto repeat1;
	}
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
    int a=strlen(name);
	cout<<acno<<setw(10)<<" "<<name<<setw(20-a)<<"  "<<type<<setw(10)<<"  "<<deposit<<endl;
	
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

//    	function declaration

void write_account();
void display_sp(int);	
void modify_account(int);
void delete_account(int);	
void display_all();		
void deposit_withdraw(int, int); 
void intro();	

//    	THE MAIN FUNCTION OF PROGRAM

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("CLS");
		cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
		cout<<"\n\n\n\t\t\t\t\t\tMAIN MENU";
		cout<<"\n\n\tA. CREATE ACCOUNT";
		cout<<"\n\n\tB. DEPOSIT";
		cout<<"\n\n\tC. WITHDRAW";
		cout<<"\n\n\tD. CHECK ACCOUNT BALANCE";
		cout<<"\n\n\tE. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\tF. CLOSE AN ACCOUNT";
		cout<<"\n\n\tG. MODIFY AN ACCOUNT";
		cout<<"\n\n\tTO EXIT PRESS 'H'";
		cout<<"\n\n\tSelect Your Option (A to H): ";
	
		cin>>ch;
		system("CLS");
		ch=toupper(ch);
		switch(ch)
		{
		case 'A' :
			write_account();
			break;
		case 'B':
		  	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case 'C':
		   	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case 'D': 
		  	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			display_sp(num);
			break;
		case 'E':
			display_all();
			break;
		case 'F':
		   	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			delete_account(num);
			break;
		 case 'G':
		  	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			modify_account(num);
			break;
		 case 'H':
			cout<<"\n\n\tThanks for using ACROPOLIS COOPERATIVE BANK!!";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='H');
	return 0;
}

//    	function to write in file

void write_account()
{
  	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	bool flag=false;
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//    	function to read specific record from file

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

//    	function to modify record of file

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//    	function to delete record of file

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//    	function to display all accounts deposit list

void display_all()
{
   	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"======================================================\n";
	cout<<"A/c no.        NAME               Type        Balance   \n";
	cout<<"======================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//    	function to deposit and withdraw amounts

void deposit_withdraw(int n, int option)
{
	int amt;
	int bal;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw: ";
				cin>>amt;
			    bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"\n\tInsufficience balance!!";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		   	cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//    	INTRODUCTION FUNCTION

void intro()
{
	cout<<"\t\t\t\t\t\t  !!!!!!! ACROPOLIS COOPERATIVE BANK  !!!!!!!";
	cout<<"\n\n\n\n\t\t\t\t\t\t    WELCOME TO ACROPOLIS COOPERATIVE BANK...";
	cout<<"\n\n\n\n\tEnter any key to continue...";
	cin.get();
}
