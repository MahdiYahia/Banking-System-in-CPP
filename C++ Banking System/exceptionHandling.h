#include<exception>


using namespace std;

class MissingFile :public exception
{
	virtual const char* what() const throw()
	{
		return "The file containing the user's data is missing!";
	}
};

class MissingNotificationsFile :public exception
{

	virtual const char* what() const throw()
	{
		return " ";
	}
};