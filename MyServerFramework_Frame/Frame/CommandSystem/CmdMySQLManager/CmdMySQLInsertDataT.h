#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "FrameCallback.h"
#include "MySQLTableT.h"
#include "MySQLDataPool.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLInsertDataT : public GameCommand
{
	BASE(CmdMySQLInsertDataT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mData = nullptr;
		mCallback = nullptr;
	}
	void execute() override
	{
		if (mData->mID == 0)
		{
			mData->mID = mTable->generateMaxGUID();
		}
		const bool success = mTable->insertDataT(mData, false);
		mMySQLDataPool->destroyClass(mData);
		if (mCallback != nullptr)
		{
			delayCall([success, callback = mCallback]() { callback(success); });
		}
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	T* mData = nullptr;
	BoolCallback mCallback = nullptr;
};
#endif