#pragma once
#include<iostream>
using namespace std;

//A User class that encapsulates all the attributes and methods that the normal user can have access to.
class User
{
protected:
	struct Content* insertFirstLine(const string FirstLine);
	void insertCurrentLine(struct Content* head, const string CurrenttLine)const;
	void deleteList(struct Content* head)const;
	void writeListOnUserFile(struct Content* head, string username);
private:
	void updateCurrency(const float ChangeRate,const string NewCurrency);
	void updateNotificationsFile(const string username);
	void writeListOnNotificationsFile(struct Content* head)const;
	string enterDate()const ;
	int compareDates(const string Date1, const string Date2)const;
	string Username;
	string FirstName;
	string LastName;
	double Balance=0;
public:
	string Currency;
	void getInfo(string username);
	float getBalance(const string username)const;
	void changeCurrency(const string username);
	void makeTransaction(const string username)const ;
	void getHistory(const string username)const ;
	void getNotifications(const string Username);
	
};
//A class bank that inherits the attributes and methods from the User class and has some new methods that only the bank can use
class Bank :public User
{
public:
	void changeData(const string Username);
	void sendNotification(const string Username)const ;
};

void openAccount();
string enterPassword();
string enterUsername();
string chooseCurrency();
void logInInterface();
void bankLogInInterface();

struct Content
{
	string CurrentLine;
	struct Content* Next;
};
