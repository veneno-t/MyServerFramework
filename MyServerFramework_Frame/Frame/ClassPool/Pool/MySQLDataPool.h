#pragma once

#ifdef _MYSQL
#include "ClassBaseTypePoolThread.h"
#include "MySQLData.h"

class MySQLDataPool : public ClassBaseTypePoolThread<MySQLData>
{
	BASE(MySQLDataPool, ClassBaseTypePoolThread<MySQLData>);
};
#endif