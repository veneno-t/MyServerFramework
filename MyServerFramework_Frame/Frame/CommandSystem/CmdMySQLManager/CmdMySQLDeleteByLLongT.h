#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLDeleteByLLongT : public GameCommand
{
	BASE(CmdMySQLDeleteByLLongT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn = T::Column::NONE;
		mValue = 0;
		mOnlyOnce = false;
	}
	void execute() override
	{
		// 第0列固定为ID
		if (mColumn == T::Column::ID)
		{
			mTable->deleteByID(mValue);
		}
		else
		{
			mTable->deleteByLLongT(mColumn, mValue, mOnlyOnce);
		}
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	llong mValue = 0;
	bool mOnlyOnce = false;
};
#endif