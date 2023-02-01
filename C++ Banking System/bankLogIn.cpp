#include<iostream>
#include<fstream>
#include<string>
#include"header.h"
using namespace std;

void bankLogInInterface()
{
	char r;

	string AccessCode="WF72QQ", EnteredAccessCode;
	cout << "Please enter the access code!" << endl;
	cin >> EnteredAccessCode;
	
	if (AccessCode != EnteredAccessCode)
	{

		cout << "The Access Code you entered is not valid!" << endl;
		cout << "If you want to retry, press 'R'" << endl;
		cout << "Press any other key to go back to the main menu!" << endl;
		cin >> r;
		if ((r == 'R') || (r == 'r'))
		{
			bankLogInInterface();
		}
	}

	else if (AccessCode == EnteredAccessCode)
	{
		string Username;
		cout << "Please enter the required username." << endl;
		cin >> Username;
		ifstream file(Username + "data.txt");
		if (file.is_open())
		{
			file.close();
			int loop = 1, c = 0;//c is for the user's choice
			while (loop)
			{
				Bank CurrentUser;
				try
				{
					CurrentUser.getInfo(Username);
				}
				catch (exception& ex)
				{
					cout << ex.what() << endl;
				}
				//The menu the user with special access will get after logging in.	
				cout << endl << endl << endl;
				cout << "The user's default currency is " << CurrentUser.Currency << endl;
				cout << "To check  the user's balance, Please press the key '1'" << endl;
				cout << "To make a new transaction, please press the key '2'" << endl;
				cout << "To check the the user's history of transactions, please press the key '3'" << endl;
				cout << "To send a notification to the user, please press the key '4'" << endl;
				cout << "To change the default currency, please press the key '5'" << endl;
				cout << "to change the user's data, please press the key '6'" << endl;
				cout << "To log out, please press the key '7'" << endl << endl;
				cout << endl << endl << endl << endl;
				cin >> c;
				try 
				{
					switch (c)
					{
					case 1:
						cout << "The user's current balance is: " << CurrentUser.getBalance(Username) << endl;
						break;
					case 2:
						CurrentUser.makeTransaction(Username);
						break;
					case 3:
						CurrentUser.getHistory(Username);
						break;
					case 4:
						CurrentUser.sendNotification(Username);
						break;
					case 5:
						CurrentUser.changeCurrency(Username);
						break;
					case 6:
						CurrentUser.changeData(Username);
						break;
					case 7:
						loop = 0;
						break;
					}
				}			
				catch (exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
		}
		else if (!file.is_open())
		{
			cout << "The Username you enetered does not exist." << endl << "You will be redirected to the main menu!" << endl << endl;
		}
	}
}
