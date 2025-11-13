#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryListByLLongListT : public GameCommand
{
	BASE(CmdMySQLQueryListByLLongListT, GameCommand);
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
		// 去重
		removeDumplicate(mValueList);
		auto dataList = mTable->queryListByLLongListT(mColumn, mValueList);
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, dataList = move(dataList)]() { CALL(callback, dataList.get()); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	Vector<llong> mValueList;
	QueryDataListCallbackT<T> mCallback = nullptr;
};
#endif