#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

class Contacts;

class Contact
{
	int _id;
	string _firstName;
	string _lastName;
	string _phoneNumber;
	string _address;
	string _email;
	int _contactDbId;
	int _userId;

public:
	Contact();
	
	int getId();
	string getFirstName();
	string getLastName();
	string getPhoneNumber();
	string getAddress();
	string getEmail();
	int getContactDbId();
	int getUserId();

	void setId(int id);
	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setPhoneNumber(string phoneNumber);
	void setAddress(string address);
	void setEmail(string email);
	void setContactDbId(int contactDbId);
	void setUserId(int userId);

	Contacts getAllContactsByUserId(MYSQL mysql, int userId);
	Contacts getContactsByFirstNameAndUserId(MYSQL mysql, string firstName, int userId);
	Contact* getContactById(MYSQL mysql, int contactId);
	bool createContact(MYSQL mysql, Contact* newContact);
	bool updateContact(MYSQL mysql, Contact* contact);
	bool deleteContact(MYSQL mysql, int contactDbId, int userId);
	
	void showContacts(Contact* contacts, int count);
	void writeContact(int userId);
};

class Contacts
{
	Contact* _contacts;
	int _count;
public:
	Contacts(Contact* contacts = NULL, int count = 0);
	~Contacts();
	Contact* getContacts();
	int getCount();

	void setContacts(Contact* contacts);
	void setCount(int count);
};