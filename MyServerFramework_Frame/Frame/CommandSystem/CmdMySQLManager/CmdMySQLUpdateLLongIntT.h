#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地将一个llong和int属性写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateLLongIntT : public GameCommand
{
	BASE(CmdMySQLUpdateLLongIntT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mID = 0;
		mColumn0 = T::Column::NONE;
		mColumn1 = T::Column::NONE;
		mValue0 = 0;
		mValue1 = 0;
	}
	void execute() override
	{
		mTable->updateLLongIntT(mID, mColumn0, mValue0, mColumn1, mValue1);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	llong mID = 0;
	typename T::Column mColumn0 = T::Column::NONE;
	typename T::Column mColumn1 = T::Column::NONE;
	llong mValue0 = 0;
	int mValue1 = 0;
};
#endif