#include <iostream>
#include <mysql.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

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

	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setPhoneNumber(string phoneNumber);
	void setAddress(string address);
	void setEmail(string email);

	map<Contact*, int> getAllContactsByUserId(MYSQL mysql, int userId);
	map<Contact*, int> getContactsByFirstNameAndUserId(MYSQL mysql, string firstName, int userId);
	Contact* getContactById(MYSQL mysql, int contactId);
	bool createContact(MYSQL mysql, Contact* newContact);
	bool updateContact(MYSQL mysql, Contact* contact);
	
	void showContacts(Contact* contacts, int count);
	void writeContact(int userId);
};

