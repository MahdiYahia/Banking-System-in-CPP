#include"header.h"
#include<fstream>
#include<string>
#include <sstream> 
#include"exceptionHandling.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
using namespace std;
//A function that deletes the notifications already received by the user
void User::updateNotificationsFile(const string username) 
{
	string CurrentLine,st;
	ifstream file("notifications.txt");
	int first = 0;//initializing the int to test if the first line is added to the list to zero 
	struct Content* head = NULL;
	
	while (first == 0)
	{
		getline(file, CurrentLine);
	    if (CurrentLine!=username)
		{
			head=insertFirstLine(CurrentLine);
			getline(file, st);
			insertCurrentLine(head, st);
			first = 1;
		}
		else
		{
			getline(file, st);
		}
	}
	while (!file.eof())
	{
		getline(file, CurrentLine);
		if (CurrentLine != username)
		{
			insertCurrentLine(head, CurrentLine);
			getline(file, CurrentLine);
			insertCurrentLine(head, CurrentLine);
		}
		else
		{
			getline(file, CurrentLine);
		}
    }
	file.close();
	writeListOnNotificationsFile(head);
}
//A function that finds the notifications sent to the user by the bank prints them and then deletes them.
void User::getNotifications(const string Username) 
{
	ifstream file("notifications.txt");
	if (!file.is_open())
	{
		throw MissingNotificationsFile();
	}
	string Receiver;
	while (!file.eof())
	{
		getline(file, Receiver);
		if (Username == Receiver)
		{
			string Notification;
			getline(file, Notification);
			cout << Notification << endl;
		}
		else
		{
			string st;
			getline(file, st);
		}
	}
	file.close();
	updateNotificationsFile(Username);
}

//A function that extracts the user's information from the file and add it to the User's class
void User::getInfo(const string username) 
{
	ifstream file(username + "data.txt");
	if (!file.is_open())
	{
		throw MissingFile();
	}
	string un, pw;
	getline(file,un);
	getline(file, pw);
	getline(file,User::FirstName);
	getline(file, User::LastName);
	getline(file, User::Currency);
	User::Username = username;
	file.close();
}
//A function that calculates the balance of the user
float User::getBalance(const string username) const 
{
	float Sum=0;
	ifstream file(username+"data.txt");
	if (!file.is_open())
	{
		throw MissingFile();
	}
	string st;
	for (int i=0;i<5;i++)
	{
		getline(file, st);
	}
	while (!file.eof())
	{
		string Name, Valuest, Date;
		float Value;
		file >> Name;
		file >> Valuest;
		file >> Date;
		Value=stof(Valuest);
		Sum = Sum + Value;
	}
	return Sum;
}
void User::makeTransaction(const string username) const
{

	ifstream file(username + "data.txt");
	if (!file.is_open())
	{
		throw MissingFile();
	}
	file.close();
	int c;
	while (1)
	{
		cout << endl << endl;
		cout << "If you want to deposit money, Please press the key '1'" << endl;
		cout << "If you want to buy something, Please press the key '2'" << endl;
		cin >> c;
		if ((c == 1) || (c == 2))
			break; //valid entry, break out
	}

	time_t CT = time(0);
	tm* CurrentTime = localtime(&CT);
	string Date;
	Date = to_string(CurrentTime->tm_year + 1900) + "/" + to_string(CurrentTime->tm_mon + 1) + "/" + to_string(CurrentTime->tm_mday);

	if (c == 1)
	{
		string Name;
		float Value;
		cout << "How much you will deposit?" << endl;
		cin >> Value;
		ofstream userdata;
		userdata.open(username + "data.txt", ios::app);

		userdata << endl << "Deposit " << Value << " " << Date;
	}
	else if (c == 2)
	{
		cin.ignore();
		string Name;
		float Value;
		cout << "Who will be the receiver?" << endl;
		getline(cin, Name);
	
		if (Name.find(' ')!=Name.npos)
		{
			do 
			{	
				cin.ignore();
				cout << endl << "The name you entered contains a space character" << endl << "Please enter a valid transaction name!" << endl;
				getline(cin, Name);
				

			} while (Name.find(' ')!=Name.npos);
		}
		cout << "How much you will transfer?" << endl;
		cin >> Value;
		ofstream userdata;
		userdata.open(username + "data.txt", ios::app);
		userdata <<endl<< Name << " -" << Value << " " << Date ;
	}
}

int User::compareDates(const string Date1,const string Date2) const
{
	istringstream d1s,d2s;
	int year1, month1, day1, year2,month2, day2;
	char slash;
	d1s.str(Date1);
	d2s.str(Date2);
	d1s >> year1;
	d1s >> slash;
	d1s >> month1;
	d1s >> slash;
	d1s >> day1;
	d2s >> year2;
	d2s >> slash;
	d2s >> month2;
	d2s >> slash;
	d2s >> day2;

	if (year1 > year2)
		return 1;
	if (year2 > year1)
		return 2;
	if (month1 > month2)
		return 1;
	if (month1 < month2)
		return 2;
	if (day1 > day2)
		return 1;
	if (day1 < day2)
		return 2;

	return 0;
}
string User::enterDate() const 
{
	int year, month, day;
	cout << "Enter the year" << endl;
	cin >> year;
	if ((3000 < year) || (year < 2000))
	{
		do
		{
			cout << "The year you entered is not valid!" << endl << "Please choose another year!" << endl;
			cin >> year;
			if ((year <= 3000) && (year >= 2000))
				break;
		} while (true);
	}

	cout << "Enter the month" << endl;
	cin >> month;
	if ((12 < month) || (month < 1))
	{
		do
		{
			cout << "The month you entered is not valid!" << endl << "Please choose another month!" << endl;
			cin >> month;
			if (month <= 12 && month >= 1)
				break;
		} while (true);
	}
	cout << "Enter the day" << endl;
	cin >> day;
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{

		if ((1 > day) || (day > 31))
		{
			do
			{
				cout << "The day you entered is not valid" << endl << "Please enter a new day" << endl;
				cin >> day;

				if ((day <= 31) && (day >= 1))
					break;
			} while (true);
		}
	}
	else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{

		if ((1 > day) || (day > 30))
		{
			do
			{
				cout << "The day you entered is not valid" << endl << "Please enter a new day" << endl;
				cin >> day;

				if ((day <= 30) && (day >= 1))
					break;
			} while (true);
		}
	}
	else if(month==2)
	{
		if (((year % 100) != 0) && ((year % 4) == 0))
		{
			if ((day > 29) || (day < 1))
			{
				do
				{
					cout << "The day you entered is not valid" << endl << "Please enter a new day" << endl;
					cin >> day;

					if ((1 <= day) && (day <= 29))
					{
						break;
					}
				} 	
				while (true);
			} 		
		}
		else if ((day > 28) || (day < 1))
		{
			do
			{
				cout << "The day you entered is not valid" << endl << "Please enter a new day" << endl;
				cin >> day;

				if ((1 <= day) && (day <= 28))
				{
					break;
				}
			} 				
			while (true);
		}
	}
	string Date;
	Date =  to_string(year) + "/" + to_string(month) + "/" + to_string(day);
	return Date;
}

void User::getHistory(const string username) const
{
	string st;
	ifstream file(username + "data.txt");
	if (!file.is_open())
	{
		throw MissingFile();
	}
	for (int i = 0; i < 5; i++)
	{
		getline(file, st);
	}
	
	string FromDate, TillDate;
	cout << "Enter the date from which you want to get the history" << endl;
	FromDate = enterDate();
	cout << "Enter the date till which you want to get the history" << endl;
	TillDate = enterDate();

	if (User::compareDates(FromDate, TillDate) == 1)
	{
		do
		{
			cout << "The second date cannot be before the first date" << endl;
			cout << "Enter the date from which you want to get the history" << endl;
			FromDate= enterDate();
			cout << "Enter the date till which you want to get the history" << endl;
			TillDate= enterDate();
			if (User::compareDates(FromDate, TillDate) != 1)
				break;
		} while (true);
	}
	while (!file.eof())
	{
		istringstream iss;
		string History, Name, Value, Date;
		getline(file, History);
		iss.str(History);
		iss >> Name;
		iss >> Value;
		iss >> Date;
		
		if (((compareDates(FromDate, Date) == 2) || (compareDates(FromDate, Date) == 0)) && (compareDates(TillDate, Date) <= 1))
		{
			cout << History << endl;
		}
	}
}