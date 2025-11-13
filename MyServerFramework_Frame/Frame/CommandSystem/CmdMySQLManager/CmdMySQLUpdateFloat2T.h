#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 简单地将两个浮点数属性写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateFloat2T : public GameCommand
{
	BASE(CmdMySQLUpdateFloat2T, GameCommand);
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
		if (mColumn0 != T::Column::NONE)
		{
			mTable->updateFloatT(mID, mColumn0, mValue0);
		}
		if (mColumn1 != T::Column::NONE)
		{
			mTable->updateFloatT(mID, mColumn1, mValue1);
		}
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	llong mID = 0;
	typename T::Column mColumn0 = T::Column::NONE;
	typename T::Column mColumn1 = T::Column::NONE;
	float mValue0 = 0.0f;
	float mValue1 = 0.0f;
};
#endif