#pragma once

#include "SQLiteTableBase.h"
#include "SelectCount.h"
#include "VectorPoolManager.h"

template<class T, typename TypeCheck = typename IsSubClassOf<SQLiteData, T>::mType>
class SQLiteTable : public SQLiteTableBase
{
	BASE(SQLiteTable, SQLiteTableBase);
public:
	~SQLiteTable() override
	{
		DELETE_MAP(mDataMap);
	}
	T* query(const int id, const bool showError = true)
	{
		if (mDataMap.isEmpty())
		{
			queryAll();
		}
		if (id > 0 && mDataList.size() > id)
		{
			return mDataList[id];
		}
		return mDataMap.tryGet(id);
	}
	const HashMap<int, T*>& queryAll()
	{
		// 如果没有查询过,或者数据的数量与已查询数量不一致才会查询全部
		THREAD_LOCK(mThreadLock);
		if (mDataMap.isEmpty() || doQueryCount() != mDataMap.size())
		{
			Vector<T*> list;
			queryAllData(list);
			int maxID = 0;
			for(T*& value : list)
			{
				// 没有查询过的数据才插入列表,已经查询过的则不再需要,直接释放
				if (!mDataMap.insert(value->mID, value))
				{
					DELETE(value);
					continue;
				}
				maxID = getMax(maxID, value->mID);
				mDataList.resize(maxID + 1);
				for (const auto& item : mDataMap)
				{
					mDataList[item.first] = item.second;
				}
			}
		}
		return mDataMap;
	}
	const Vector<T*>& getDataVector()
	{
		if (mDataList.isEmpty())
		{
			queryAll();
		}
		return mDataList;
	}
	void checkEnumResult(bool result, const char* varName, int dataID)
	{
		if (!result)
		{
			ERROR(string("enum value error,name:") + varName + " in " + mTableName + ", ID:" + IToS(dataID) + ", Table:" + getTableName());
		}
	}
	void checkData(const int checkID, const int dataID, SQLiteTableBase* refTable)
	{
		if (checkID > 0 && query(checkID, false) == nullptr)
		{
			ERROR("can not find item id:" + IToS(checkID) + " in " + mTableName + ", ref ID:" + IToS(dataID) + ", ref Table:" + refTable->getTableName());
		}
	}
	template<typename T0>
	void checkData(const Vector<T0>& checkIDList, const int dataID, SQLiteTableBase* refTable)
	{
		for (const T0 id : checkIDList)
		{
			if (query(id, false) == nullptr)
			{
				ERROR("can not find item id:" + IToS(id) + " in " + mTableName + ", ref ID:" + IToS(dataID) + ", ref Table:" + refTable->getTableName());
			}
		}
	}
	template<typename T0, int Length>
	void checkData(const ArrayList<Length, T0>& checkIDList, const int dataID, SQLiteTableBase* refTable)
	{
		for (const T0 id : checkIDList)
		{
			if (query(id, false) == nullptr)
			{
				ERROR("can not find item id:" + IToS(id) + " in " + mTableName + ", ref ID:" + IToS(dataID) + ", ref Table:" + refTable->getTableName());
			}
		}
	}
	template<typename T0, typename T1>
	void checkListPair(const Vector<T0>& list0, const Vector<T1>& list1, const int dataID)
	{
		if (list0.size() != list1.size())
		{
			ERROR(string("list pair size not match, table:") + mTableName + ", ref ID:" + IToS(dataID));
		}
	}
	void checkDataAllColName() override
	{
		T().checkAllColName(this);
	}
protected:
	void queryAllData(Vector<T*>& dataList)
	{
		doSelect(dataList);
	}
	bool queryData(const int id, T& data)
	{
		MyString<128> conditionString;
		sqlConditionInt(conditionString, "ID", id);
		return doSelect(data, conditionString.str());
	}
	int doQueryCount()
	{
		MyString<256> queryStr;
		strcat_t(queryStr, "SELECT count(ID) FROM ", mTableName, " WHERE ID > 0");
		SelectCount selectCount;
		SQLiteDataReader(mSQLite3, queryStr.str()).parseReader(selectCount);
		return selectCount.mRowCount;
	}
	void doSelect(Vector<T*>& dataList, const char* conditionString = nullptr)
	{
		MyString<256> queryStr;
		if (conditionString != nullptr)
		{
			strcat_t(queryStr, "SELECT * FROM ", mTableName, " WHERE ", conditionString);
		}
		else
		{
			strcat_t(queryStr, "SELECT * FROM ", mTableName);
		}
		SQLiteDataReader(mSQLite3, queryStr.str()).parseReader(dataList);
	}
	bool doSelect(T& data, const char* conditionString = nullptr)
	{
		MyString<256> queryStr;
		if (conditionString != nullptr)
		{
			strcat_t(queryStr, "SELECT * FROM ", mTableName, " WHERE ", conditionString, " LIMIT 1");
		}
		else
		{
			strcat_t(queryStr, "SELECT * FROM ", mTableName, " LIMIT 1");
		}
		return SQLiteDataReader(mSQLite3, queryStr.str()).parseReader(data);
	}
protected:
	HashMap<int, T*> mDataMap;
	Vector<T*> mDataList;			// 由于使用map进行查询仍然不够快速,而ID恰好适合作为下标,所以直接根据ID进行下标定位最快
};