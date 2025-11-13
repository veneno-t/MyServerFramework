#include "FrameHeader.h"

void SQLiteManager::lateQuit()
{
	// 由于其他系统的quit对SQLiteData有依赖,所以在lateQuit中才去销毁Data
	DELETE_MAP(mSQLiteList);
}

void SQLiteManager::checkAll()
{
	for (const auto& iter : mSQLiteList)
	{
		iter.second->checkAllData();
		iter.second->checkDataAllColName();
	}
}