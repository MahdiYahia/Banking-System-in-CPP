#include<fstream>
#include<string>
#include<exception>
#include"header.h"
using namespace std;

void User::writeListOnNotificationsFile(struct Content* head) const 
{
    ofstream file("notifications.txt", ofstream::trunc);
    struct Content* CH = head;
    while (CH != NULL)
    {
        file << CH->CurrentLine << endl;
        CH = CH->Next;
    }
    deleteList(head);
    file.close();
}

 Content* User::insertFirstLine(const string FirstLine)
{
     try 
     {
         Content* head = new Content;
         head->CurrentLine = FirstLine;
         head->Next = NULL;
         return head;
     }
     catch(bad_alloc&)
     {
         cout << "Bad memory allocation"<<endl;
     } 
}
void User::insertCurrentLine( Content* head , const string CurrentLine) const
{      
    try {
        Content* NewElement = head;
        for (NewElement = head; NewElement->Next != NULL; NewElement = NewElement->Next);
        NewElement->Next = new struct Content;
        NewElement->Next->CurrentLine = CurrentLine;
        NewElement->Next->Next = NULL;
    }
    catch (bad_alloc&)
    {
        cout << "Bad memory allocation" << endl;
    }
}

void User::deleteList(struct Content* head) const 
{
    struct Content* CH, * N;//CH is the current header and N is the pointer to the next node in the linked list
    CH = head;
    while (CH!=NULL) 
    {
        N = CH->Next;
        delete CH;
        CH = N;
    }
}

void User::writeListOnUserFile( Content* head,const string username)
{
    ofstream file(username + "data.txt", ofstream::trunc);
    Content* CH=head;
    file << CH->CurrentLine;
    CH = CH->Next;
    while (CH != NULL)
    {
        file <<endl;
        file << CH->CurrentLine;
        CH = CH->Next;
    }
    deleteList(head);
    file.close();
}
