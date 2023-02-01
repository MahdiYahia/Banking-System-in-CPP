#include<fstream>
#include<string>
#include"header.h"
#include"exceptionHandling.h"

void Bank::changeData(const string username)
{
    ifstream file(username + "data.txt");
    if (!file.is_open())
    {
        throw MissingFile();
    }

    int c;
    if (file.is_open())
    {
        do
        {
            cout << "What is the data you want to change?" << endl;
            cout << "if you want to change the first name of the user please press '1'" << endl;
            cout << "if you want to change the last name of the user please press '2'" << endl;
            cin >> c;
            if ((c == 1) || (c == 2))
            {
                break; //valid entry, break out
            }
        } while (1);
        if (c == 1)
        {
            //change  the first name
            string st, FirstName;
            cout << "Please enter the new first name";
            cin >> FirstName;
            struct Content* head = NULL;

            getline(file, st);
            head=insertFirstLine( st);
            getline(file, st);
            insertCurrentLine(head, st);
            insertCurrentLine(head, FirstName);
            getline(file, st);
            while (!file.eof())
            {
                string CurrentLine;
                getline(file, CurrentLine);
                insertCurrentLine(head, CurrentLine);
            }
            file.close();
            writeListOnUserFile(head, username);
        }
        else if (c == 2)
        {
            string st, LastName;
            cout << "Please enter the new last name";
            cin >> LastName;
            struct Content* head = NULL;

            getline(file, st);
            head = insertFirstLine(st);
            for (int i = 0; i < 2; i++)
            {
                getline(file, st);
                insertCurrentLine(head, st);
            }
            insertCurrentLine(head, LastName);
            getline(file, st);
            while (!file.eof())
            {
                string CurrentLine;
                getline(file, CurrentLine);
                insertCurrentLine(head, CurrentLine);
            }
            file.close();
            writeListOnUserFile(head, username);
        }
    }
}

void Bank::sendNotification(const string Username) const
{
    string Text;
    cin.ignore();

    cout << "Please write the content of the notification!" << endl;
    getline(cin,Text);
    ofstream file;
    file.open("notifications.txt", ios::app);
    file << Username << endl << Text << endl;
    file.close();
}