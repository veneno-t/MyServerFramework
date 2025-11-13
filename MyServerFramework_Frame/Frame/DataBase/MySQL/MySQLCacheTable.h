#pragma once

#ifdef _MYSQL
#include "FrameBase.h"
#include "MySQLCacheData.h"

class MICRO_LEGEND_FRAME_API MySQLCacheTable
{
public:
	MySQLCacheTable(MySQLTable* table);
	void destroy();
	ullong columnToFlag(int colName) const;
	ullong columnsToFlag(const Vector<int>& colNames) const;
	MySQLData* getCacheData(const llong id) const
	{
		MySQLCacheData* cacheData = mCacheDataList.tryGet(id);
		return cacheData != nullptr ? cacheData->getData() : nullptr;
	}
	MySQLData* getDataByLLong2Or(int column0, llong value0, int column1, llong value1);
	MySQLData* getDataByLLong2And(int column0, llong value0, int column1, llong value1);
	MySQLData* getDataByInt(int column, int value);
	MySQLData* getDataByLLong(int column, llong value);
	MySQLData* getDataByString(int column, const string& value);
	MySQLData* getDataByString2And(int column0, const string& value0, int column1, const string& value1);
	MySQLData* getDataByLLongIntAnd(int column0, llong value0, int column1, int value1);
	MySQLData* getDataByLLongStringAnd(int column0, llong value0, int column1, const string& value1);
	void getCacheDataListByInt(int column0, int value0, Vector<MySQLData*>& dataList);
	void updateBool(llong id, bool value, int colName) const;
	void updateInt(llong id, int value, int colName) const;
	void updateInt2(llong id, int value0, int colName0, int value1, int colName1) const;
	void updateFloat(llong id, float value, int colName) const;
	void updateLLong(llong id, llong value, int colName) const;
	void updateLLongInt(llong id, llong value0, int colName0, int value1, int column1) const;
	void updateLLongBool(llong id, llong value0, int colName0, bool value1, int column1) const;
	void updateString(llong id, const string& value, int colName) const;
	void updateString2(llong id, const string& value0, int colName0, const string& value1, int colName1) const;
	void updateAllString(int colName, const string& value) const;
	void updateAllInt(int colName, int value) const;
	void updateAllLLong(int colName, llong value) const;
	void updateAllFloat(int colName, float value) const;
	void updateAllBool(int colName, bool value) const;
	void addOrUpdateData(const MySQLData* data, ullong validFlag = FrameDefine::FULL_MYSQL_FLAG);
	void addOrUpdateDataList(const Vector<MySQLData*>& dataList, ullong validFlag = FrameDefine::FULL_MYSQL_FLAG);
	void deleteAllData();
	void deleteData(llong id);
	void deleteDataInIDRange(llong minID, llong maxID);
	// 因为需要支持根据部分字段的值来删除数据,所以在查询时需要查询所有字段的数据,否则可能会删除失败,导致缓存跟数据库不一致
	void deleteDataByColumnBool(int column, bool value, bool onlyOnce);
	void deleteDataByColumnInt(int column, int value, bool onlyOnce);
	void deleteDataByColumnFloat(int column, float value, bool onlyOnce);
	void deleteDataByColumnLLong(int column, llong value, bool onlyOnce);
	void deleteDataByColumnString(int column, const string& value, bool onlyOnce);
	void deleteDataByColumnLLong2And(int column0, llong value0, int column1, llong value1, bool onlyOnce);
	void deleteDataByColumnLLongIntAnd(int column0, llong value0, int column1, int value1, bool onlyOnce);
	void deleteDataByColumnLLong2Or(int column0, llong value0, int column1, llong value1, bool onlyOnce);
protected:
	HashMap<llong, MySQLCacheData*> mCacheDataList;
	MySQLTable* mTable = nullptr;		// 需要在子类进行赋值
};

#endif