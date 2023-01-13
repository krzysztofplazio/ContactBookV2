#include "Contact.h"
#include <conio.h>

using namespace std;

Contact::Contact()
{
	_id = 0;
	_contactDbId = 0;
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

int Contact::getContactDbId()
{
	return _contactDbId;
}

int Contact::getUserId()
{
	return _userId;
}

void Contact::setFirstName(string firstName)
{
	_firstName = firstName;
}

void Contact::setLastName(string lastName)
{
	_lastName = lastName;
}

void Contact::setPhoneNumber(string phoneNumber)
{
	_phoneNumber = phoneNumber;
}

void Contact::setAddress(string address)
{
	_address = address;
}

void Contact::setEmail(string email)
{
	_email = email;
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
		contactArray[i]._contactDbId = atoi(rows[0]);
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
	if (firstName == "" || firstName.find_first_not_of(' '))
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
		contactArray[i]._contactDbId = atoi(rows[0]);
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

Contact* Contact::getContactById(MYSQL mysql, int contactId)
{
	auto contact = new Contact();
	MYSQL_ROW rows;
	auto query = "SELECT Id, FirstName, LastName, phoneNumber, address, email, userId FROM Contacts WHERE Id = " + to_string(contactId) + ";";
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
		contact->_id = i;
		contact->_contactDbId = atoi(rows[0]);
		contact->_firstName = rows[1];
		contact->_lastName = rows[2];
		contact->_phoneNumber = rows[3];
		contact->_address = rows[4];
		contact->_email = rows[5];
		contact->_userId = atoi(rows[6]);
		i++;
	}
	mysql_free_result(response);
	return contact;
}

bool Contact::createContact(MYSQL mysql, Contact* newContact)
{
	auto query = "INSERT INTO Contacts (FirstName, LastName, phoneNumber, address, email, userId) VALUES (\'"
		+ newContact->getFirstName()
		+ "\',\'" + newContact->getLastName()
		+ "\',\'" + newContact->getPhoneNumber()
		+ "\',\'" + newContact->getAddress()
		+ "\',\'" + newContact->getEmail()
		+ "\'," + to_string(newContact->getUserId())
		+  ");";

	if (mysql_query(&mysql, query.c_str()))
	{
		cout << mysql_error(&mysql);
		return false;
	}

	return true; 
}

bool Contact::updateContact(MYSQL mysql, Contact* contact)
{
	string query = "UPDATE Contacts SET firstName = \'" + contact->_firstName + "\',"
		+ "lastName = \'" + contact->_lastName + "\',"
		+ "phoneNumber = \'" +  contact->_phoneNumber + "\',"
		+ "address = \'" + contact->_address + "\',"
		+ "email = \'" + contact->_email + "\' WHERE Id = " + to_string(contact->_contactDbId) + " AND UserId = " + to_string(contact->_userId) + ";";

	if (mysql_query(&mysql, query.c_str()))
	{
		cout << mysql_error(&mysql);
		return false;
	}

	return true;
}

void Contact::showContacts(Contact* contacts, int count)
{
	cout << "Twoje kontakty:\n";
	for (auto i = 0; i < count; i++)
	{
		cout << contacts[i].getId()
			 << ". \nImie: \t\t " << contacts[i].getFirstName()
			 << "\nNazwisko: \t " << contacts[i].getLastName()
			 << "\nNumer telefonu:  " << contacts[i].getPhoneNumber()
			 << "\nAdres: \t\t " << contacts[i].getAddress()
			 << "\nEmail: \t\t " << contacts[i].getEmail()
			 << "\nIndeks: \t " << contacts[i].getContactDbId() << "\n\n";
	}
}

void Contact::writeContact(int userId)
{
	cout << "Imie: ";
	getline(cin, _firstName);

	cout << "Nazwisko: ";
	getline(cin, _lastName);

	cout << "Numer telefonu: ";
	getline(cin, _phoneNumber);

	cout << "Adres: ";
	getline(cin, _address);

	cout << "Email: ";
	getline(cin, _email);

	_userId = userId;
}
