#pragma once

#include "ClassObject.h"

class Counter : public ClassObject
{
	BASE(Counter, ClassObject);
protected:
    atomic<int> mCount;
public:
    Counter() : mCount(0) {}
    int increase() { return ++mCount; }
    int decrease() { return --mCount; }
    bool isZero() { return mCount == 0; }
    void resetProperty() override
    {
        base::resetProperty();
        mCount = 0;
    }
};