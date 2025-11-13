#ifdef _MYSQL
#include "FrameHeader.h"

MySQLCacheTable::MySQLCacheTable(MySQLTable* table) :
	mTable(table)
{}

void MySQLCacheTable::destroy()
{
	deleteAllData();
}

ullong MySQLCacheTable::columnToFlag(const int colName) const
{
	ullong flag = 0;
	setBitOne(flag, colName);
	return flag;
}

ullong MySQLCacheTable::columnsToFlag(const Vector<int>& colNames) const
{
	ullong flag = 0;
	for (const int col : colNames)
	{
		setBitOne(flag, col);
	}
	return flag;
}

MySQLData* MySQLCacheTable::getDataByLLong2Or(const int column0, const llong value0, const int column1, const llong value1)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasLLong(column0, value0) || item.second->hasLLong(column1, value1))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

MySQLData* MySQLCacheTable::getDataByLLong2And(const int column0, const llong value0, const int column1, const llong value1)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasLLong(column0, value0) && item.second->hasLLong(column1, value1))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

MySQLData* MySQLCacheTable::getDataByInt(const int column, const int value)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasInt(column, value))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

MySQLData* MySQLCacheTable::getDataByLLong(const int column, const llong value)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasLLong(column, value))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

MySQLData* MySQLCacheTable::getDataByString(const int column, const string& value)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasString(column, value))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

MySQLData* MySQLCacheTable::getDataByString2And(const int column0, const string& value0, const int column1, const string& value1)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasString(column0, value0) && item.second->hasString(column1, value1))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

MySQLData* MySQLCacheTable::getDataByLLongIntAnd(const int column0, const llong value0, const int column1, const int value1)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasLLong(column0, value0) && item.second->hasInt(column1, value1))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

MySQLData* MySQLCacheTable::getDataByLLongStringAnd(const int column0, const llong value0, const int column1, const string& value1)
{
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasLLong(column0, value0) && item.second->hasString(column1, value1))
		{
			return item.second->getData();
		}
	}
	return nullptr;
}

void MySQLCacheTable::getCacheDataListByInt(const int column0, int value0, Vector<MySQLData*>& dataList)
{
	dataList.clear();
	for (const auto& item : mCacheDataList)
	{
		if (item.second->hasInt(column0, value0))
		{
			dataList.push_back(item.second->getData());
		}
	}
}

void MySQLCacheTable::updateInt(const llong id, const int value, const int colName) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateInt(colName, value);
	}
}

void MySQLCacheTable::updateBool(const llong id, const bool value, const int colName) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateBool(colName, value);
	}
}

void MySQLCacheTable::updateInt2(const llong id, const int value0, const int colName0, const int value1, const int colName1) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateInt(colName0, value0);
		curData->updateInt(colName1, value1);
	}
}

void MySQLCacheTable::updateFloat(const llong id, const float value, const int colName) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateFloat(colName, value);
	}
}

void MySQLCacheTable::updateLLong(const llong id, const llong value, const int colName) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateLLong(colName, value);
	}
}

void MySQLCacheTable::updateLLongInt(const llong id, const llong value0, const int colName0, const int value1, const int column1) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateLLong(colName0, value0);
		curData->updateInt(column1, value1);
	}
}

void MySQLCacheTable::updateLLongBool(const llong id, const llong value0, const int colName0, const bool value1, const int column1) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateLLong(colName0, value0);
		curData->updateBool(column1, value1);
	}
}

void MySQLCacheTable::updateString(const llong id, const string& value, const int colName) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateString(colName, value);
	}
}

void MySQLCacheTable::updateString2(const llong id, const string& value0, const int colName0, const string& value1, const int colName1) const
{
	if (MySQLCacheData* curData = mCacheDataList.tryGet(id))
	{
		curData->updateString(colName0, value0);
		curData->updateString(colName1, value1);
	}
}

void MySQLCacheTable::updateAllString(const int colName, const string& value) const
{
	for (const auto& item : mCacheDataList)
	{
		item.second->updateString(colName, value);
	}
}

void MySQLCacheTable::updateAllInt(const int colName, const int value) const
{
	for (const auto& item : mCacheDataList)
	{
		item.second->updateInt(colName, value);
	}
}

void MySQLCacheTable::updateAllLLong(const int colName, const llong value) const
{
	for (const auto& item : mCacheDataList)
	{
		item.second->updateLLong(colName, value);
	}
}

void MySQLCacheTable::updateAllFloat(const int colName, const float value) const
{
	for (const auto& item : mCacheDataList)
	{
		item.second->updateFloat(colName, value);
	}
}

void MySQLCacheTable::updateAllBool(const int colName, const bool value) const
{
	for (const auto& item : mCacheDataList)
	{
		item.second->updateBool(colName, value);
	}
}

void MySQLCacheTable::addOrUpdateData(const MySQLData* data, const ullong validFlag)
{
	if (data == nullptr)
	{
		return;
	}
	// 数据已经有了,则更新数据
	if (MySQLCacheData* curData = mCacheDataList.tryGet(data->mID))
	{
		data->cloneWithFlag(curData->getData(), validFlag);
		curData->addValidFlag(validFlag);
	}
	// 插入新的数据
	else
	{
		MySQLCacheData* cacheData = mMySQLCacheDataPool->newClass();
		cacheData->setTable(mTable);
		data->clone(cacheData->getData());
		cacheData->addValidFlag(validFlag);
		mCacheDataList.insert(cacheData->getID(), cacheData);
	}
}

void MySQLCacheTable::addOrUpdateDataList(const Vector<MySQLData*>& dataList, const ullong validFlag)
{
	for (const MySQLData* data : dataList)
	{
		if (data == nullptr)
		{
			continue;
		}
		// 数据已经有了,则更新数据
		if (MySQLCacheData* curData = mCacheDataList.tryGet(data->mID))
		{
			data->cloneWithFlag(curData->getData(), validFlag);
			curData->addValidFlag(validFlag);
		}
		// 插入新的数据
		else
		{
			MySQLCacheData* cacheData = mMySQLCacheDataPool->newClass();
			cacheData->setTable(mTable);
			data->clone(cacheData->getData());
			cacheData->addValidFlag(validFlag);
			mCacheDataList.insert(cacheData->getID(), cacheData);
		}
	}
}

void MySQLCacheTable::deleteAllData()
{
	mMySQLCacheDataPool->destroyClassList(mCacheDataList);
}

void MySQLCacheTable::deleteData(const llong id)
{
	MySQLCacheData* data = nullptr;
	if (mCacheDataList.erase(id, data))
	{
		mMySQLCacheDataPool->destroyClass(data);
	}
}

void MySQLCacheTable::deleteDataInIDRange(const llong minID, const llong maxID)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		if (iter->first >= minID && iter->first <= maxID)
		{
			mMySQLCacheDataPool->destroyClass(iter->second);
			iter = mCacheDataList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnBool(const int column, const bool value, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasBool(column, value))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnInt(const int column, const int value, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasInt(column, value))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnFloat(const int column, const float value, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasFloat(column, value))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnLLong(const int column, const llong value, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasLLong(column, value))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnString(const int column, const string& value, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasString(column, value))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnLLong2And(const int column0, const llong value0, const int column1, const llong value1, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasLLong(column0, value0) && cacheData->hasLLong(column1, value1))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnLLongIntAnd(const int column0, const llong value0, const int column1, const int value1, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasLLong(column0, value0) && cacheData->hasInt(column1, value1))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}

void MySQLCacheTable::deleteDataByColumnLLong2Or(const int column0, const llong value0, const int column1, const llong value1, bool onlyOnce)
{
	for (auto iter = mCacheDataList.begin(); iter != mCacheDataList.end(); )
	{
		MySQLCacheData* cacheData = iter->second;
		if (cacheData->hasLLong(column0, value0) || cacheData->hasLLong(column1, value1))
		{
			mMySQLCacheDataPool->destroyClass(cacheData);
			iter = mCacheDataList.erase(iter);
			if (onlyOnce)
			{
				break;
			}
		}
		else
		{
			++iter;
		}
	}
}
#endif