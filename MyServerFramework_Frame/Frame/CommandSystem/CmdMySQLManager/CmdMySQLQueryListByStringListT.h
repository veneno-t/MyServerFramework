#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryListByStringListT : public GameCommand
{
	BASE(CmdMySQLQueryListByStringListT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mColumn = T::Column::NONE;
		mValueList.clear();
		mCallback = nullptr;
	}
	void execute() override
	{
		auto dataList = mTable->queryListByStringListT(mColumn, mValueList);
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, dataList = move(dataList)]() { CALL(callback, dataList.get()); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	Vector<string> mValueList;
	QueryDataListCallbackT<T> mCallback = nullptr;
};
#endif