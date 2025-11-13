#ifdef _MYSQL
#include "FrameHeader.h"

void CmdMySQLDeleteAll::execute()
{
	mTable->deleteAll();
}
#endif