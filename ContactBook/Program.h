#pragma once
#include "User.h"
class Program
{
	static void mainMenu(MYSQL mysql, User* user);

public:
	static void loginUser(MYSQL mysql);
};

