#include <mysql.h>
#include "Host.h"
#include <iostream>
#include "Program.h"
using namespace std;

MYSQL mysql;

int main()
{
	mysql = Host::initalizeDatabaseConnection(mysql);

	cout << "Twoja prywatna kasiazka telefoniczna!\n";
	Program::loginUser(mysql);
	return 0;
}