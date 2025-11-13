#pragma once

#include "FrameBase.h"

class MICRO_LEGEND_FRAME_API SQLiteDataReader
{
public:
	SQLiteDataReader(sqlite3* sqlite, const char* queryStr);
	virtual ~SQLiteDataReader();
public:	
	void setSQLite3STMT(sqlite3_stmt* stmt) { mStmt = stmt; }
	// 读取一行数据,需要循环调用来读取多行数据
	bool read() const								{ return mStmt != nullptr && sqlite3_step(mStmt) == SQLITE_ROW; }
	int getColumnCount() const						{ return sqlite3_column_count(mStmt); }
	const char* getColumnName(int col) const		{ return sqlite3_column_name(mStmt, col); }
	SQLITE_DATATYPE getDataType(int col) const		{ return (SQLITE_DATATYPE)sqlite3_column_type(mStmt, col); }
	int getInt(int col) const						{ return sqlite3_column_int(mStmt, col); }
	llong getLLong(int col) const					{ return sqlite3_column_int64(mStmt, col); }
	float getFloat(int col) const					{ return (float)sqlite3_column_double(mStmt, col); }
	string getString(int col, bool toANSI = true) const
	{
		if (toANSI)
		{
			return UTF8ToANSI((char*)sqlite3_column_text(mStmt, col));
		}
		else
		{
			return (char*)sqlite3_column_text(mStmt, col);
		}
	}
	const char* getBlob(int col, int& length) const
	{
		length = sqlite3_column_bytes(mStmt, col);
		return (const char*)sqlite3_column_blob(mStmt, col);
	}
	template<typename Table>
	bool parseReader(Table& data)
	{
		const bool result = read();
		if (result)
		{
			data.parse(this);
		}
		return result;
	}
	template<typename Table>
	void parseReader(Vector<Table*>& dataList)
	{
		while (read())
		{
			Table* data = new Table();
			data->parse(this);
			dataList.push_back(data);
		}
	}
protected:
	sqlite3_stmt* mStmt = nullptr;
};