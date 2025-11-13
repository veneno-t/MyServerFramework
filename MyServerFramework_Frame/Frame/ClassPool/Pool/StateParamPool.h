#pragma once

#include "ClassTypePool.h"
#include "StateParamFactoryManager.h"

class StateParamPool : public ClassTypePool<StateParam, ushort>
{
protected:
	StateParam* create(const ushort type) override
	{
		return mStateParamFactoryManager->getFactory(type)->create();
	}
};