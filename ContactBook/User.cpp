#include "User.h"
#include <iostream>

User::User()
{
	_id = 0;
}

User::User(int id, string firstName, string lastName, string login) :
	_id(id),
	_firstName(firstName),
	_lastName(lastName),
	_login(login)
{
}

User::User(string firstName, string lastName, string login, string password) :
	_firstName(firstName),
	_lastName(lastName),
	_login(login),
	_password(password)
{
}

int User::getId() const
{
	return _id;
}

string User::getFirstName() const
{
	return _firstName;
}

string User::getLastName() const
{
	return _lastName;
}

User* User::getUserByLogin(MYSQL mysql, string& login)
{
	auto user = new User();
	MYSQL_ROW rows;
	auto query = "SELECT Id, FirstName, LastName, Login FROM Users WHERE Login = \'" + login + "\';";
	if (mysql_query(&mysql, query.c_str()))
	{
		cout << mysql_error(&mysql);
		return NULL;
	}

	auto response = mysql_store_result(&mysql);
	auto i = 1;

	if (mysql_num_rows(response) != 1)
	{
		return NULL;
	}

	while ((rows = mysql_fetch_row(response)) != NULL)
	{
		if (i > 1)
		{
			break;
		}
		user->_id = atoi(rows[0]);
		user->_firstName = rows[1];
		user->_lastName = rows[2];
		user->_login = rows[3];
		i++;
	}
	mysql_free_result(response);
	return user;
}

bool User::isPasswordCorrect(MYSQL mysql, int id, string password)
{
	auto query = "SELECT Id FROM Users WHERE Id = " + to_string(id) + " AND BINARY Password = \'" + password + "\';";
	if (mysql_query(&mysql, query.c_str()))
	{
		cout << mysql_error(&mysql);
		return NULL;
	}

	auto response = mysql_store_result(&mysql);
	if (mysql_num_rows(response) != 1)
	{
		return false;
	}

	mysql_free_result(response);
	return true;
}

void User::setShownUserData(int id, char* firstName, char* lastName, char* login)
{
	//_id = id;
	_firstName.assign(firstName);
	_lastName.assign(lastName);
	_login.assign(login);
}

void User::setFirstName(string firstName)
{
	_firstName = firstName;
}

void User::setLastName(string lastName)
{
	_lastName = lastName;
}

void User::setPassword(string password)
{
	_password = password;
}
