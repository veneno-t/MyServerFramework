#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地执行一条更新语句写入数据库,并且是全表执行
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateAllIntT : public GameCommand
{
	BASE(CmdMySQLUpdateAllIntT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn = T::Column::NONE;
		mValue = 0;
	}
	void execute() override 
	{
		mTable->updateAllIntT(mColumn, mValue); 
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	int mValue = 0;
};
#endif