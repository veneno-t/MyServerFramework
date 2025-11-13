#pragma once

#include "ClassTypePool.h"
#include "CharacterFactoryManager.h"
#include "FrameBase.h"

class CharacterPool : public ClassTypePool<Character, byte>
{
protected:
	Character* create(const byte type) override
	{
		return mCharacterFactoryManager->getFactory(type)->create();
	}
};