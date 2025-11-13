#pragma once

#include "ClassTypePool.h"
#include "GameComponentFactoryManager.h"
#include "FrameBase.h"

class GameComponentPool : public ClassTypePool<GameComponent, ushort>
{
protected:
	GameComponent* create(ushort type) override
	{
		return mGameComponentFactoryManager->getFactory(type)->create();
	}
};