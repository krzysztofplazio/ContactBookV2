#pragma once
#include <string>
#include <mysql.h>

using namespace std;

class User
{
	int _id;
	string _firstName;
	string _lastName;
	string _login;
	string _password;


public:
	User();

	User(int id,
		string firstName,
		string lastName,
		string login);

	User(string firstName,
		string lastName,
		string login,
		string password);

	int getId() const;
	string getFirstName() const;
	string getLastName() const;

	User* getUserByLogin(MYSQL mysql, string& login);
	bool isPasswordCorrect(MYSQL mysql, int id, string password);
	
	void setShownUserData(int id, 
						 char* firstName, 
						 char* lastName,
						 char* login);
	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setPassword(string password);

	
};

