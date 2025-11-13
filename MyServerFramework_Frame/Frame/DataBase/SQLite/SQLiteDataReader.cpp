#include "FrameHeader.h"

SQLiteDataReader::SQLiteDataReader(sqlite3* sqlite, const char* queryStr)
{
	sqlite3_prepare_v2(sqlite, queryStr, -1, &mStmt, nullptr);
}

SQLiteDataReader::~SQLiteDataReader()
{
	if (mStmt != nullptr)
	{
		sqlite3_finalize(mStmt);
		mStmt = nullptr;
	}
}