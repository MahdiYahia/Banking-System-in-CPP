#include"header.h"
#include<fstream>
#include<string>
using namespace std;


void User::updateCurrency(const float ChangeRate, const string NewCurrency)
{
	ifstream file(User::Username + "data.txt");
	Content* head;
	string FirstLine;
	getline(file, FirstLine);
	head = insertFirstLine(FirstLine);
	string st;

	for (int i = 0; i < 3; i++)
	{
		getline(file, st);
		insertCurrentLine(head, st);
	}
	getline(file, st);
	insertCurrentLine(head, NewCurrency);
	while (!file.eof())
	{
		string CurrentLine = "";
		float Value;
		string Name, Date, ValueAsString;
		file >> Name;
		file >> Value;
		file >> Date;
		Value = Value * ChangeRate;
		ValueAsString = to_string(Value);
		CurrentLine = CurrentLine + Name + " " + ValueAsString + " " + Date;
		insertCurrentLine(head, CurrentLine);
	}
	file.close();
	User::writeListOnUserFile(head, User::Username);
}


void User::changeCurrency(const string username)
{

	cout << "Your current currency is: " << User::Currency << endl;
	string from, to;
	from = User::Currency;
	cout << "What is the new currency you want to use?" << endl;

	int c;

	cout<< "To choose HU forint, please press the number '1'"<<endl;
	cout<<"To choose euro, please press the number '2'"<<endl;
	cout <<"To choose US dollar, please press the number '3'"<<endl;
	do {
		printf("Pick a currency from the above: ");
		cin >> c;
		if ((c == 1) || (c == 2) || (c == 3)) {
			break; //valid entry, break out
		}
	} while (1);

	if (c == 1)
	{
		to = "HUF";
	}
	else if (c == 2)
	{
		to = "EUR";
	}
	else if (c == 3)
	{
		to = "USD";
	}
	//The change rate to HUF will be in the first position
	//to EUR in the second position and to USD in the thrid one
	float fromHUF[] = { 1.00F , 0.0028F , 0.0033F };
	float fromEUR[] = { 360.00F , 1.00F , 1.20F };
	float fromUSD[] = { 300.00F , 0.84F , 1.00F };
	if (from == "HUF")
	{
		updateCurrency(fromHUF[c - 1],to);
	}
	else if (from == "EUR")
	{
		updateCurrency(fromEUR[c - 1],to);
	}
	else if (from == "USD")
	{
		updateCurrency(fromUSD[c - 1],to);
	}
}
