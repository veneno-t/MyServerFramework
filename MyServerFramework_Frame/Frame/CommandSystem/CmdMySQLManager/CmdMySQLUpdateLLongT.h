#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地将一个整数属性写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateLLongT : public GameCommand
{
	BASE(CmdMySQLUpdateLLongT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mID = 0;
		mColumn = T::Column::NONE;
		mValue = 0;
	}
	void execute() override
	{
		mTable->updateLLongT(mID, mColumn, mValue);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	llong mID = 0;
	typename T::Column mColumn = T::Column::NONE;
	llong mValue = 0;
};
#endif