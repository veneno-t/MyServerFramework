#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryCountByLLong2OrT : public GameCommand
{
	BASE(CmdMySQLQueryCountByLLong2OrT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn0 = T::Column::NONE;
		mColumn1 = T::Column::NONE;
		mValue0 = 0;
		mValue1 = 0;
		mCallback = nullptr;
	}
	void execute() override
	{
		MyString<128> condition;
		sqlConditionLLong(condition, mTable->getColNameT(mColumn0), mValue0, "=", "||");
		sqlConditionLLong(condition, mTable->getColNameT(mColumn1), mValue1);
		const llong dataCount = mTable->queryCount(condition.str());

		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, dataCount]() { CALL(callback, dataCount); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn0 = T::Column::NONE;
	typename T::Column mColumn1 = T::Column::NONE;
	llong mValue0 = 0;
	llong mValue1 = 0;
	LLongCallback mCallback = nullptr;
};
#endif