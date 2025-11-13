#pragma once

#ifdef _MYSQL
#include "ClassPool.h"
#include "MySQLCacheData.h"

class MySQLCacheDataPool : public ClassPoolThread<MySQLCacheData>
{
	BASE(MySQLCacheDataPool, ClassPoolThread<MySQLCacheData>);
};
#endif