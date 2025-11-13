#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLQueryByStringT : public GameCommand
{
	BASE(CmdMySQLQueryByStringT, GameCommand);
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
		auto data = mTable->queryByStringT(mColumn, mValue);
		// 延迟到主线程执行回调通知
		delayCall([callback = mCallback, data = move(data)]() { CALL(callback, data.get()); });
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	typename T::Column mColumn = T::Column::NONE;
	string mValue;
	QueryDataCallbackT<T> mCallback = nullptr;
};
#endif