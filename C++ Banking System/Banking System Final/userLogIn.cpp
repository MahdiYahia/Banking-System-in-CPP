#include<iostream>
#include<fstream>
#include<string>
#include"header.h"

using namespace std;

bool existingAccount(const string username, const string password)
{
	string un, pw;
	ifstream file(username + "data.txt");
	if (file.is_open())
	{
		getline(file, un);
		getline(file, pw);
		file.close();

		if ((password == pw) && (username == un))
		{
			return true;
		}
	}
	return false;
}

void logInInterface()
{
     	char r;

		string Username, Password;
		cout << "Please enter your username!"<<endl;
		cin >> Username;
		cout << "Please enter your password!"<<endl;
		cin >> Password;
		
		if (!existingAccount(Username, Password))
		{
	
			cout << "The username or password you entered is not valid!" << endl;
			cout << "If you want to retry, press 'R'" << endl;
			cout << "Press any other key to go back to the main menu!" << endl;
			cin >> r;
			if ((r == 'R') || (r == 'r'))
			{
				logInInterface();
			}
		}
		else if (existingAccount(Username, Password))
		{
			int loop=1,c=0;//c is for the user's choice
			while (loop)
			{
				User CurrentUser;
				CurrentUser.getInfo(Username);
				cout << endl << endl << endl;
				cout << "Your current default currency is " << CurrentUser.Currency << endl;
				//exception handling in case there is no notifications file
				try
				{
					CurrentUser.getNotifications(Username);
				}
				catch (exception& ex)
				{
					cout << ex.what() << endl;
				}
				//The menu the user will get after logging in.	
				cout << "To check your balance, Please press the key '1'" << endl;
				cout << "To make a new transaction, please press the key '2'" << endl;
				cout << "To check the history of your transactions, please press the key '3'" << endl;
				cout << "To change your default currency, please press the key '4'" << endl;
				cout << "To log out, please press the key '5'" << endl << endl;
				cout << endl << endl << endl << endl;
				cin >> c;
				try
				{
					switch (c) 
					{
					case 1:
						cout << "Your current balance is: " << CurrentUser.getBalance(Username) << endl;
						break;

					case 2:
						CurrentUser.makeTransaction(Username);
						break;
					case 3:
						CurrentUser.getHistory(Username);
						break;
					case 4:
						CurrentUser.changeCurrency(Username);
						break;

					case 5:
						loop = 0;
						break;
					}
				}
				catch (exception& ex)
				{
					cout << ex.what() << endl;
					loop = 0;
				}
			}
		}
}