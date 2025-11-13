#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

// 删除多个数据库中满足指定条件的数据
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLDeleteByStringT : public GameCommand
{
	BASE(CmdMySQLDeleteByStringT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn = T::Column::NONE;
		mValue.clear();
		mOnlyOnce = false;
	}
	void execute() override
	{
		mTable->deleteByStringT(mColumn, mValue, mOnlyOnce);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	string mValue;
	bool mOnlyOnce = false;
};
#endif