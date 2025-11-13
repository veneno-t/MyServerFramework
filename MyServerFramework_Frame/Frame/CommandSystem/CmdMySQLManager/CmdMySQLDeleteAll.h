#pragma once

#ifdef _MYSQL
#include "GameCommand.h"

// 删除数据库中所有数据
class MICRO_LEGEND_FRAME_API CmdMySQLDeleteAll : public GameCommand
{
	BASE(CmdMySQLDeleteAll, GameCommand);
public:
	void reset() override
	{
		mTable = nullptr;
	}
	void execute() override;
public:
	MySQLTable* mTable = nullptr;
};
#endif