#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryListByStringT : public GameCommand
{
	BASE(CmdMySQLQueryListByStringT, GameCommand);
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
		auto dataList = mTable->queryListByStringT(mColumn, mValue);
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, dataList0 = move(dataList)]() { CALL(callback, dataList0.get()); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	string mValue;
	QueryDataListCallbackT<T> mCallback = nullptr;
};
#endif