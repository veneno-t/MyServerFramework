#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLDataPool.h"
#include "MySQLTableT.h"

template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLInsertOrUpdateDataT : public GameCommand
{
	BASE(CmdMySQLInsertOrUpdateDataT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mData = nullptr;
	}
	void execute() override
	{
		if (mData == nullptr || mTable == nullptr)
		{
			ERROR("Data或者Table为空!");
			return;
		}
		if (mData->isDestroy())
		{
			ERROR_PROFILE(("0数据已经被销毁,type:" + string(typeid(*mData).name())).c_str());
			return;
		}
		if (mTable->queryExistByID(mData->mID))
		{
			mTable->updateDataT(mData, FrameDefine::FULL_MYSQL_FLAG);
		}
		else
		{
			mTable->insertDataT(mData);
		}
		mMySQLDataPool->destroyClass(mData);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	T* mData = nullptr;
};
#endif