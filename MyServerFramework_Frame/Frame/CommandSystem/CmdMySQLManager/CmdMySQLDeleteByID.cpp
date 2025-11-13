#ifdef _MYSQL
#include "FrameHeader.h"

void CmdMySQLDeleteByID::execute()
{
	// id去重
	removeDumplicate(mIDList);
	for (const MySQLTable* table : mTableList)
	{
		table->deleteByIDList(mIDList);
	}
}
#endif