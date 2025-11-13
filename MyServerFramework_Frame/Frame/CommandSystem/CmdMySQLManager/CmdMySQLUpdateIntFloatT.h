#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地将一个整数属性和一个浮点属性写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateIntFloatT : public GameCommand
{
	BASE(CmdMySQLUpdateIntFloatT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mID = 0;
		mColumn0 = T::Column::NONE;
		mValue0 = 0;
		mColumn1 = T::Column::NONE;
		mValue1 = 0.0f;
	}
	void execute() override
	{
		mTable->updateIntFloatT(mID, mColumn0, mValue0, mColumn1, mValue1);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	llong mID = 0;
	typename T::Column mColumn0 = T::Column::NONE;
	int mValue0 = 0;
	typename T::Column mColumn1 = T::Column::NONE;
	float mValue1 = 0.0f;
};
#endif