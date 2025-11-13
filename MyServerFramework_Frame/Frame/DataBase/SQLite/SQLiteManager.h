#pragma once

#include "FrameComponent.h"

// 一个sqlite文件只允许有一个表格,且名字与文件名相同
class MICRO_LEGEND_FRAME_API SQLiteManager : public FrameComponent
{
	BASE(SQLiteManager, FrameComponent);
public:
	void lateQuit() override;
	SQLiteTableBase* getSQLite(const string& name) { return mSQLiteList.tryGet(name); }
	template<typename T, typename TypeCheck = typename IsSubClassOf<SQLiteTableBase, T>::mType>
	T* registerTable(const char* tableName)
	{
		T* table = new T();
		table->setTableName(tableName);
		table->init(FrameDefine::SQLITE_PATH + tableName + ".db");
		mSQLiteList.insert(table->getTableName(), table);
		return table;
	}
	void checkAll();
public:
	HashMap<string, SQLiteTableBase*> mSQLiteList;
};