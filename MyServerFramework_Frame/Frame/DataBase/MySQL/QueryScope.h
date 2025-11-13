#pragma once

#ifdef _MYSQL
#include "FrameBase.h"

class QueryScope
{
protected:
	const MySQLTable* mTable = nullptr;
public:
	MYSQL_RES* mResult = nullptr;
public:
	QueryScope(const MySQLTable* table, const char* queryStr);
	~QueryScope();
};

#endif