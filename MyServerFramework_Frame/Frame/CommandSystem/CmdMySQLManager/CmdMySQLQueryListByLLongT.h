#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryListByLLongT : public GameCommand
{
	BASE(CmdMySQLQueryListByLLongT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn = T::Column::NONE;
		mMaxCount = 0;
		mValue = 0;
		mCallback = nullptr;
	}
	void execute() override
	{
		auto dataList = mTable->queryListByLLongT(mColumn, mValue, mMaxCount);
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, dataList = move(dataList)]() { CALL(callback, dataList.get()); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	int mMaxCount = 0;
	llong mValue = 0;
	QueryDataListCallbackT<T> mCallback = nullptr;
};
#endif