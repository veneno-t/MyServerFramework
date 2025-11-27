#pragma once

#include "Set.h"
#include "SafeSet.h"

// 需要通过SAFE_SET_SCOPE宏来使用
template<typename T>
class SafeSetScope
{
protected:
	SafeSet<T>* mList = nullptr;
	const Set<T>* mReadList = nullptr;
public:
	SafeSetScope(SafeSet<T>& list)
	{
		mList = &list;
		mReadList = &(mList->startForeach());
	}
	const Set<T>& getReadList() const { return *mReadList; }
	~SafeSetScope()
	{
		mList->endForeach();
	}
};