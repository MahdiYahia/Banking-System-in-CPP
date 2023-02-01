#include<iostream>
#include<fstream>
#include<string>
#include"header.h"
using namespace std;

int main()
{
	int loop=1;
	char c;// character to store the user's choice 
	while (loop)
	{
		//The main menu the user will encounter when the program starts
		cout << endl << endl << endl;
		cout << "Welcome to smart bank!" << endl<<endl;
		cout << "If you would like to log in to an already existing account. Please press ""L""" << endl;
		cout << "If you have a special access. Please press ""B""" << endl;
		cout << "If you would like to open a new account. Please press ""R""" << endl;
		cout << "If you would like to quit the program. Please press ""Q""" << endl;
		cin >> c;
		if ((c=='L') || (c == 'l'))
		{
			logInInterface();
		}
		else if ((c == 'B') || (c == 'b'))
		{
			bankLogInInterface();
		}
		else if ((c == 'R') || (c == 'r'))
		{
			openAccount();
		}
		else if ((c == 'Q') || (c == 'q'))
		{ 
			loop = 0;
		}
	}
}