#include "FrameHeader.h"

void ExcelManager::quit()
{
	DELETE_MAP(mTableList);
}

void ExcelManager::checkAll()
{
	for (const auto& iter : mTableList)
	{
		iter.second->checkAllData();
	}
}