#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地将一个浮点数数属性写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateFloatT : public GameCommand
{
	BASE(CmdMySQLUpdateFloatT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mID = 0;
		mColumn = T::Column::NONE;
		mValue = 0.0f;
	}
	void execute() override 
	{
		mTable->updateFloatT(mID, mColumn, mValue); 
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	llong mID = 0;
	typename T::Column mColumn = T::Column::NONE;
	float mValue = 0.0f;
};
#endif