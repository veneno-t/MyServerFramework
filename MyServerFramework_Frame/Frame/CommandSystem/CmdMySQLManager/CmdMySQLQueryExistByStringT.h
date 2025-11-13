#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryExistByStringT : public GameCommand
{
	BASE(CmdMySQLQueryExistByStringT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn = T::Column::NONE;
		mValue.clear();
		mCallback = nullptr;
	}
	void execute() override
	{
		const bool exist = mTable->queryExistByStringT(mColumn, mValue);
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, exist]() { CALL(callback, exist); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	string mValue;
	BoolCallback mCallback = nullptr;
};
#endif