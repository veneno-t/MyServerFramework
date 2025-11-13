#pragma once

#ifdef _MYSQL
#include "FrameCallback.h"
#include "FrameDefine.h"
#include "CmdUtility.h"
#include "MySQLTableT.h"
#include "CommandThreadPool.h"
#include "CmdMySQLQueryCountByIntT.h"
#include "CmdMySQLQueryCountByLLongT.h"
#include "CmdMySQLDeleteByLLong2AndT.h"
#include "CmdMySQLUpdateLLongT.h"
#include "CmdMySQLUpdateLLongIntT.h"
#include "CmdMySQLUpdateBoolT.h"
#include "CmdMySQLUpdateIntT.h"
#include "CmdMySQLUpdateIntFloatT.h"
#include "CmdMySQLUpdateInt2T.h"
#include "CmdMySQLUpdateFloatT.h"
#include "CmdMySQLUpdateStringT.h"
#include "CmdMySQLUpdateString2T.h"
#include "CmdMySQLUpdateLLongListT.h"
#include "CmdMySQLUpdateAllIntT.h"
#include "CmdMySQLDeleteByLLongIntAndT.h"
#include "CmdMySQLDeleteByLLongT.h"
#include "CmdMySQLDeleteByStringT.h"
#include "CmdMySQLDeleteByID.h"
#include "CmdMySQLDeleteAll.h"
#include "CmdMySQLInsertDataT.h"
#include "CmdMySQLInsertOrUpdateDataT.h"
#include "CmdMySQLUpdateDataT.h"
#include "CmdMySQLQueryByStringT.h"
#include "CmdMySQLQueryByIDT.h"
#include "CmdMySQLQueryListByStringT.h"
#include "CmdMySQLQueryExistByStringT.h"
#include "CmdMySQLQueryListByIDT.h"
#include "CmdMySQLQueryListByIntT.h"
#include "CmdMySQLQueryListByLLongT.h"
#include "CmdMySQLQueryListByStringListT.h"
#include "CmdMySQLQueryCountByLLong2OrT.h"
#include "CmdMySQLQueryAllT.h"

namespace FrameMySQLUtility
{
	void MICRO_LEGEND_FRAME_API pushCommandToMySQL(GameCommand* cmd);
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateLLong(MySQLTableT<T>* table, llong id, typename T::Column colName, llong value)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateLLongT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn = colName;
		cmd->mValue = value;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateLLongInt(MySQLTableT<T>* table, llong id, typename T::Column colName0, llong value0, typename T::Column colName1, int value1)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateLLongIntT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn0 = colName0;
		cmd->mColumn1 = colName1;
		cmd->mValue0 = value0;
		cmd->mValue1 = value1;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateBool(MySQLTableT<T>* table, llong id, typename T::Column colName, bool value)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateBoolT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn = colName;
		cmd->mValue = value;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateInt(MySQLTableT<T>* table, llong id, typename T::Column colName, int value)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateIntT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn = colName;
		cmd->mValue = value;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateIntFloat(MySQLTableT<T>* table, llong id, typename T::Column colName0, int value0, typename T::Column colName1, float value1)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateIntFloatT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn0 = colName0;
		cmd->mValue0 = value0;
		cmd->mColumn1 = colName1;
		cmd->mValue1 = value1;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateInt2(MySQLTableT<T>* table, llong id, typename T::Column colName0, int value0, typename T::Column colName1, int value1)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateInt2T<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn0 = colName0;
		cmd->mValue0 = value0;
		cmd->mColumn1 = colName1;
		cmd->mValue1 = value1;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateFloat(MySQLTableT<T>* table, llong id, typename T::Column colName, float value)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateFloatT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn = colName;
		cmd->mValue = value;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateString(MySQLTableT<T>* table, llong id, typename T::Column colName, const string& value, int length = -1)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateStringT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn = colName;
		cmd->mValue = value;
		if (length > 0 && length < (int)cmd->mValue.length())
		{
			cmd->mValue.erase(length);
		}
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateString2(MySQLTableT<T>* table, llong id, typename T::Column colName0, const string& value0, typename T::Column colName1, const string& value1)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateString2T<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn0 = colName0;
		cmd->mValue0 = value0;
		cmd->mColumn1 = colName1;
		cmd->mValue1 = value1;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateString(MySQLTableT<T>* table, llong id, typename T::Column colName, string&& value)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateStringT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn = colName;
		cmd->mValue = move(value);
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateLLongList(MySQLTableT<T>* table, llong id, typename T::Column colName, const Vector<llong>& value)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateLLongListT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mColumn = colName;
		value.clone(cmd->mValue);
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateAllInt(MySQLTableT<T>* table, typename T::Column colName, int value)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateAllIntT<T>>();
		cmd->mTable = table;
		cmd->mColumn = colName;
		cmd->mValue = value;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryAll(MySQLTableT<T>* table, const QueryDataListCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryAllT<T>>();
		cmd->mTable = table;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryCountByInt(MySQLTableT<T>* table, typename T::Column colName, int value, const LLongCallback& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryCountByIntT<T>>();
		cmd->mTable = table;
		cmd->mColumn = colName;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryCountByLLong(MySQLTableT<T>* table, typename T::Column colName, llong value, const LLongCallback& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryCountByLLongT<T>>();
		cmd->mTable = table;
		cmd->mColumn = colName;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void deleteByLLong2And(MySQLTableT<T>* table, typename T::Column colName0, llong value0, typename T::Column colName1, llong value1, bool onlyOnce)
	{
		auto* cmd = CMD_THREAD<CmdMySQLDeleteByLLong2AndT<T>>();
		cmd->mTable = table;
		cmd->mColumn0 = colName0;
		cmd->mColumn1 = colName1;
		cmd->mValue0 = value0;
		cmd->mValue1 = value1;
		cmd->mOnlyOnce = onlyOnce;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void deleteByLLongIntAnd(MySQLTableT<T>* table, typename T::Column colName0, llong value0, typename T::Column colName1, int value1, bool onlyOnce)
	{
		auto* cmd = CMD_THREAD<CmdMySQLDeleteByLLongIntAndT<T>>();
		cmd->mTable = table;
		cmd->mColumn0 = colName0;
		cmd->mColumn1 = colName1;
		cmd->mValue0 = value0;
		cmd->mValue1 = value1;
		cmd->mOnlyOnce = onlyOnce;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void deleteByLLong(MySQLTableT<T>* table, typename T::Column colName, llong value, bool onlyOnce)
	{
		auto* cmd = CMD_THREAD<CmdMySQLDeleteByLLongT<T>>();
		cmd->mTable = table;
		cmd->mColumn = colName;
		cmd->mValue = value;
		cmd->mOnlyOnce = onlyOnce;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void deleteByString(MySQLTableT<T>* table, typename T::Column colName, const string& value, bool onlyOnce)
	{
		auto* cmd = CMD_THREAD<CmdMySQLDeleteByStringT<T>>();
		cmd->mTable = table;
		cmd->mColumn = colName;
		cmd->mValue = value;
		cmd->mOnlyOnce = onlyOnce;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void deleteByID(MySQLTableT<T>* table, llong id)
	{
		auto* cmd = CMD_THREAD<CmdMySQLDeleteByID>();
		cmd->mTableList.push_back(table);
		cmd->mIDList.push_back(id);
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void deleteByIDList(MySQLTableT<T>* table, Vector<llong>&& idList)
	{
		if (idList.isEmpty())
		{
			return;
		}
		auto* cmd = CMD_THREAD<CmdMySQLDeleteByID>();
		cmd->mTableList.push_back(table);
		idList.clone(cmd->mIDList);
		pushCommandToMySQL(cmd);
	}
	template<typename T0, typename T1, typename TypeCheck0 = typename IsSubClassOf<MySQLData, T0>::mType, typename TypeCheck1 = typename IsSubClassOf<MySQLData, T1>::mType>
	void deleteCombineByID(MySQLTableT<T0>* table0, MySQLTableT<T1>* table1, llong id)
	{
		auto* cmd = CMD_THREAD<CmdMySQLDeleteByID>();
		cmd->mTableList.push_back(table0, table1);
		cmd->mIDList.push_back(id);
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void deleteAll(MySQLTableT<T>* table)
	{
		auto* cmd = CMD_THREAD<CmdMySQLDeleteAll>();
		cmd->mTable = table;
		pushCommandToMySQL(cmd);
	}
	// data需要是从对象池中创建的
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void insertData(MySQLTableT<T>* table, T* data)
	{
		auto* cmd = CMD_THREAD<CmdMySQLInsertDataT<T>>();
		cmd->mTable = table;
		cmd->mData = data;
		cmd->mCallback = nullptr;
		pushCommandToMySQL(cmd);
	}
	// data需要是从对象池中创建的
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void insertOrUpdate(MySQLTableT<T>* table, T* data)
	{
		auto* cmd = CMD_THREAD<CmdMySQLInsertOrUpdateDataT<T>>();
		cmd->mTable = table;
		cmd->mData = data;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void updateData(MySQLTableT<T>* table, T* data)
	{
		auto* cmd = CMD_THREAD<CmdMySQLUpdateDataT<T>>();
		cmd->mTable = table;
		cmd->mData = data;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryByString(MySQLTableT<T>* table, typename T::Column column, const string& value, const QueryDataCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryByStringT<T>>();
		cmd->mTable = table;
		cmd->mColumn = column;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryListByString(MySQLTableT<T>* table, typename T::Column column, const string& value, const QueryDataListCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryListByStringT<T>>();
		cmd->mTable = table;
		cmd->mColumn = column;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryByID(MySQLTableT<T>* table, llong id, const QueryDataCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryByIDT<T>>();
		cmd->mTable = table;
		cmd->mID = id;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryExistByString(MySQLTableT<T>* table, typename T::Column column, const string& value, const BoolCallback& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryExistByStringT<T>>();
		cmd->mTable = table;
		cmd->mColumn = column;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryListByID(MySQLTableT<T>* table, Vector<llong>&& idList, const QueryDataListCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryListByIDT<T>>();
		cmd->mTable = table;
		cmd->mValueList = move(idList);
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryListByID(MySQLTableT<T>* table, const Vector<llong>& idList, const QueryDataListCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryListByIDT<T>>();
		cmd->mTable = table;
		cmd->mValueList = idList;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryListByInt(MySQLTableT<T>* table, typename T::Column column, int value, const QueryDataListCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryListByIntT<T>>();
		cmd->mTable = table;
		cmd->mColumn = column;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryListByLLong(MySQLTableT<T>* table, typename T::Column column, int maxCount, llong value, const QueryDataListCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryListByLLongT<T>>();
		cmd->mTable = table;
		cmd->mColumn = column;
		cmd->mMaxCount = maxCount;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryListByLLong(MySQLTableT<T>* table, typename T::Column column, llong value, const QueryDataListCallbackT<T>& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryListByLLongT<T>>();
		cmd->mTable = table;
		cmd->mColumn = column;
		cmd->mValue = value;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryListByStringList(MySQLTableT<T>* table, typename T::Column column, Vector<string>&& valueList, const QueryDataListCallbackT<T>& callback)
	{
		if (valueList.isEmpty())
		{
			CALL(callback, Vector<T*>::mDefaultList);
			return;
		}
		auto* cmd = CMD_THREAD<CmdMySQLQueryListByStringListT<T>>();
		cmd->mTable = table;
		cmd->mColumn = column;
		cmd->mValueList = move(valueList);
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
	template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
	void queryCountByLLong2Or(MySQLTableT<T>* table, typename T::Column column0, typename T::Column column1, llong value0, llong value1, const LLongCallback& callback)
	{
		auto* cmd = CMD_THREAD<CmdMySQLQueryCountByLLong2OrT<T>>();
		cmd->mTable = table;
		cmd->mColumn0 = column0;
		cmd->mColumn1 = column1;
		cmd->mValue0 = value0;
		cmd->mValue1 = value1;
		cmd->mCallback = callback;
		pushCommandToMySQL(cmd);
	}
};
using namespace FrameMySQLUtility;
#endif