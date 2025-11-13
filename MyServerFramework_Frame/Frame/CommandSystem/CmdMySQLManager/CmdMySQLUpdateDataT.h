#pragma once

#ifdef _MYSQL
#include "GameCommand.h"
#include "MySQLTableT.h"
#include "MySQLDataPool.h"

// 简单地执行一条更新语句写入数据库
template<typename T, typename TypeCheck = typename IsSubClassOf<MySQLData, T>::mType>
class CmdMySQLUpdateDataT : public GameCommand
{
	BASE(CmdMySQLUpdateDataT, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
		mData = nullptr;
	}
	void execute() override 
	{
		mTable->updateDataT(mData, FrameDefine::FULL_MYSQL_FLAG);
		mMySQLDataPool->destroyClass(mData);
	}
public:
	MySQLTableT<T>* mTable = nullptr;
	T* mData = nullptr;
};
#endif