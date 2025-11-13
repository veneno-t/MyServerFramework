#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "FrameUtility.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryAllT : public GameCommand
{
	BASE(CmdMySQLQueryAllT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mCallback = nullptr;
	}
	void execute() override
	{
		auto data = mTable->queryAllT();
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, data = move(data)]() { CALL(callback, data.get()); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	QueryDataListCallbackT<T> mCallback = nullptr;
};
#endif