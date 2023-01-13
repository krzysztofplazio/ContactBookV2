#include <mysql.h>

class Host
{
	Host() {}
public:
	static MYSQL initalizeDatabaseConnection(MYSQL mysql);
};

