#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地将两个字符串属性写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateString2T : public GameCommand
{
	BASE(CmdMySQLUpdateString2T, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mID = 0;
		mColumn0 = T::Column::NONE;
		mValue0.clear();
		mColumn1 = T::Column::NONE;
		mValue1.clear();
	}
	void execute() override
	{
		mTable->updateString2T(mID, mColumn0, mValue0, mColumn1, mValue1);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	llong mID = 0;
	typename T::Column mColumn0 = T::Column::NONE;
	string mValue0;
	typename T::Column mColumn1 = T::Column::NONE;
	string mValue1;
};
#endif