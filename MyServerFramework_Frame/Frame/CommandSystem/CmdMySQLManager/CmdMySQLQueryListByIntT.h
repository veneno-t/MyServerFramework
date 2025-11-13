#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryListByIntT : public GameCommand
{
	BASE(CmdMySQLQueryListByIntT, GameCommand);
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
		auto dataList = mTable->queryListByIntT(mColumn, mValue, 0);
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, dataList = move(dataList)]() { CALL(callback, dataList.get()); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	int mValue = 0;
	QueryDataListCallbackT<T> mCallback = nullptr;
};
#endif