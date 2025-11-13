#ifdef _MYSQL
#include "FrameHeader.h"

void MySQLCacheData::setTable(MySQLTable* table)
{
	mTable = table;
	mData = mTable->createPersistData();
}

void MySQLCacheData::destroy()
{
	base::destroy();
	mMySQLDataPool->destroyClass(mData);
}

void MySQLCacheData::resetProperty()
{
	base::resetProperty();
	mTable = nullptr;
	mData = nullptr;
	mValidFlag = 0;
}

bool MySQLCacheData::isColumnNamesValid(const Vector<int>& colNames) const
{
	// 不指定查询列,则表示查询所有列
	if (colNames.isEmpty())
	{
		FOR_I(mTable->getColCount())
		{
			if (!isColumnValid(i))
			{
				return false;
			}
		}
	}
	else
	{
		for (const int col : colNames)
		{
			if (col < 0 || !isColumnValid(col))
			{
				return false;
			}
		}
	}
	return true;
}
#endif