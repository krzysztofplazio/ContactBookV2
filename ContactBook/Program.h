#pragma once
#include "User.h"
#include "Contact.h"
#include <conio.h>
#include "helpers.h"
#include <windows.h>
#include <iostream>
#include <mysql.h>

class Program
{
	static void mainMenu(MYSQL mysql, User* user);
	static void backToMainMenu(MYSQL mysql, User* user);
	static void setNewContact(MYSQL mysql, User* user, Contact* contact);
	static void editContact(MYSQL mysql, User* user);
	static void changeContact(MYSQL mysql, User* user, Contact* contact);
	static void deleteContact(MYSQL mysql, User* user);
public:
	static void loginUser(MYSQL mysql);
};

