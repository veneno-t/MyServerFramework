#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryCountByLLongT : public GameCommand
{
	BASE(CmdMySQLQueryCountByLLongT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn = T::Column::NONE;
		mValue = 0;
		mCallback = nullptr;
	}
	void execute() override
	{
		MyString<64> condition;
		sqlConditionLLong(condition, mTable->getColNameT(mColumn), mValue);
		const llong dataCount = mTable->queryCount(condition.str());

		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, dataCount]() { CALL(callback, dataCount); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	llong mValue = 0;
	LLongCallback mCallback = nullptr;
};
#endif