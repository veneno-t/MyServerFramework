#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地将一个字符串属性写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateStringT : public GameCommand
{
	BASE(CmdMySQLUpdateStringT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mID = 0;
		mColumn = T::Column::NONE;
		mValue.clear();
	}
	void execute() override
	{
		mTable->updateStringT(mID, mColumn, mValue);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	llong mID = 0;
	typename T::Column mColumn = T::Column::NONE;
	string mValue;
};
#endif