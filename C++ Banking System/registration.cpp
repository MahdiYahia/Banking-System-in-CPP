#include<iostream>
#include<fstream>
using namespace std;
string chooseCurrency()
{
	int c;
	cout << endl << endl<<endl;
	cout << "Please choose your default currency!"<<endl;
	cout << "To choose euro, please press the number '1'" << endl;
	cout << "To choose US dollar, please press the number '2'" << endl;
	cout << "To choose HU forint, please press the number '3'" << endl;
	
	do 
	{
		cout<<"Pick a currency from the above: "<<endl;
		cin >> c;
		if ((c == 1) || (c == 2) || (c == 3))
		{
			break; //valid entry, break out
		}
	} while (1);
	if (c == 1)
	{
		return "EUR";
	}
	else if (c == 2)
	{
		return "USD";
	}
	else if (c == 3)
	{
		return "HUF";
	}
}
string enterUsername()
{
	string username;
	bool valid = true;
	do
	{
		valid = true;
		cout << "Please enter your username!"<<endl;
		cin >> username;
		ifstream file(username + "data.txt");
		if (file.is_open())
		{
			cout << "The user name you entered is already used!"<<endl<<"Please choose a new one."<<endl<<endl<<endl;
			valid = false;
			file.close();
		}
	} while (!valid);
	return username;
}
string enterPassword()
{
	string password;
	cout << "Please enter your password!"<<endl;
	cin >> password;
	return password;
}
void openAccount()
{
	string username, password, firstname, lastname, currency;

	cout << "Thank you for trusting our bank!"<<endl<<" we Will guide you through the registration process!" << endl;
	username = enterUsername();
	password = enterPassword();
	cout << "Please enter your first name!"<<endl;
	cin >> firstname;
	cout << "Please enter your last name!"<<endl;
	cin >> lastname;
	currency = chooseCurrency();
	ofstream file(username + "data.txt");
	file << username<<endl;
	file << password << endl;
	file << firstname << endl;
	file << lastname << endl;
	file << currency ;
	file.close();
}
