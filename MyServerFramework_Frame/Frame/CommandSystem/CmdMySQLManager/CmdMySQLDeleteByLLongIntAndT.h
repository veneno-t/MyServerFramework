#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLDeleteByLLongIntAndT : public GameCommand
{
	BASE(CmdMySQLDeleteByLLongIntAndT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn0 = T::Column::NONE;
		mColumn1 = T::Column::NONE;
		mValue0 = 0;
		mValue1 = 0;
		mOnlyOnce = false;
	}
	void execute() override
	{
		mTable->deleteByLLongIntAndT(mColumn0, mValue0, mColumn1, mValue1, mOnlyOnce);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn0 = T::Column::NONE;
	typename T::Column mColumn1 = T::Column::NONE;
	llong mValue0 = 0;
	int mValue1 = 0;
	bool mOnlyOnce = false;
};
#endif