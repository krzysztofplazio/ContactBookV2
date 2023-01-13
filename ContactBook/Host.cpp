#include "Host.h"
#include <iostream>
#include <string.h>

using namespace std;

MYSQL Host::initalizeDatabaseConnection(MYSQL mysql)
{
	// Localhost
	const string server = "localhost";
	const unsigned int port = 6969;
	const string user = "root";
	const string password = "root";
	const string database = "PhoneBook";

	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES 'utf8mb4';");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET CHARACTER SET utf8mb4;");
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, server.c_str(), user.c_str(), password.c_str(), database.c_str(), port, 0, NULL))
	{
		cout << mysql_error(&mysql);
		return mysql;
	}
}
