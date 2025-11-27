#pragma once

#include "Vector.h"
#include "SafeVector.h"

// 需要通过SAFE_VECTOR_SCOPE宏来使用
template<typename T>
class SafeVectorScope
{
protected:
	SafeVector<T>* mList = nullptr;
	const Vector<T>* mReadList = nullptr;
public:
	SafeVectorScope(SafeVector<T>& list)
	{
		mList = &list;
		mReadList = &(mList->startForeach());
	}
	const Vector<T>& getReadList() const { return *mReadList; }
	~SafeVectorScope()
	{
		mList->endForeach();
	}
};