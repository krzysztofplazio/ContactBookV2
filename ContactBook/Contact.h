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
	int _userId;

public:
	Contact();
	
	int getId();
	string getFirstName();
	string getLastName();
	string getPhoneNumber();
	string getAddress();
	string getEmail();

	map<Contact*, int> getAllContactsByUserId(MYSQL mysql, int userId);
	map<Contact*, int> getContactsByFirstNameAndUserId(MYSQL mysql, string firstName, int userId);
	
	void showContacts(Contact* contacts, int count);
};

