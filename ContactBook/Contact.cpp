#include "Contact.h"

using namespace std;

Contact::Contact()
{
	_id = 0;
	_userId = 0;
}

int Contact::getId()
{
	return _id;
}

string Contact::getFirstName()
{
	return _firstName;
}

string Contact::getLastName()
{
	return _lastName;
}

string Contact::getPhoneNumber()
{
	return _phoneNumber;
}

string Contact::getAddress()
{
	return _address;
}

string Contact::getEmail()
{
	return _email;
}

map<Contact*, int> Contact::getAllContactsByUserId(MYSQL mysql, int userId)
{
	MYSQL_ROW rows;
	map<Contact*, int> contacts;
	//contacts.emplace(NULL, 0);
	auto query = "SELECT Id, FirstName, LastName, phoneNumber, address, email, userId FROM Contacts WHERE UserId = " + to_string(userId) + ";";
	if (mysql_query(&mysql, query.c_str()))
	{
		cout << mysql_error(&mysql);
		contacts[NULL] = 0;
		return contacts;
	}

	auto response = mysql_store_result(&mysql);
	auto rowsNum = mysql_num_rows(response);
	if (mysql_num_rows(response) == 0)
	{
		contacts[NULL] = 0;
		return contacts;
	}
	
	auto contactArray = new Contact[rowsNum];
	auto i = 0;
	while ((rows = mysql_fetch_row(response)) != NULL || i < rowsNum)
	{
		contactArray[i]._id = i + 1;
		contactArray[i]._firstName = rows[1];
		contactArray[i]._lastName = rows[2];
		contactArray[i]._phoneNumber = rows[3];
		contactArray[i]._address = rows[4];
		contactArray[i]._email = rows[5];
		i++;
	}
	mysql_free_result(response);
	contacts[contactArray] = rowsNum;
	return contacts;
}

map<Contact*, int> Contact::getContactsByFirstNameAndUserId(MYSQL mysql, string firstName, int userId)
{
	MYSQL_ROW rows;
	map<Contact*, int> contacts;
	if (firstName == "" || !firstName.find_first_not_of(' '))
	{
		contacts[NULL] = 0;
		return contacts;
	}

	auto query = "SELECT Id, FirstName, LastName, phoneNumber, address, email, userId FROM Contacts WHERE UserId = " + to_string(userId) + " AND firstName LIKE \'%" + firstName + "%\';";
	if (mysql_query(&mysql, query.c_str()))
	{
		cout << mysql_error(&mysql);
		contacts[NULL] = 0;
		return contacts;
	}

	auto response = mysql_store_result(&mysql);
	auto rowsNum = mysql_num_rows(response);
	if (mysql_num_rows(response) == 0)
	{
		contacts[NULL] = 0;
		return contacts;
	}

	auto contactArray = new Contact[rowsNum];
	auto i = 0;
	while ((rows = mysql_fetch_row(response)) != NULL || i < rowsNum)
	{
		contactArray[i]._id = i + 1;
		contactArray[i]._firstName = rows[1];
		contactArray[i]._lastName = rows[2];
		contactArray[i]._phoneNumber = rows[3];
		contactArray[i]._address = rows[4];
		contactArray[i]._email = rows[5];
		i++;
	}
	mysql_free_result(response);
	contacts[contactArray] = rowsNum;
	return contacts;
}

void Contact::showContacts(Contact* contacts, int count)
{
	cout << "Twoje kontakty:\n";
	for (auto i = 0; i < count; i++)
	{
		cout << contacts[i].getId()
			 << ". \nName: \t\t " << contacts[i].getFirstName()
			 << "\nSurname: \t " << contacts[i].getLastName()
			 << "\nPhoneNumber: \t " << contacts[i].getPhoneNumber()
			 << "\nAddress: \t " << contacts[i].getAddress()
			 << "\nEmail: \t\t " << contacts[i].getEmail() << "\n\n";
	}
}
