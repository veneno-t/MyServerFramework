#include "GameHeader.h"

#define STATE_FACTORY(classState)																\
		mCharacterStateFactoryManager->addFactory<classState>(CHARACTER_STATE::classState);		\
		mStateParamFactoryManager->addFactory<classState##Param>(CHARACTER_STATE::classState);

void StateRegister::registeAll()
{
	// auto generate start
	// auto generate end

	// 注册所有状态组
	registeAllStateGroup();
}

void StateRegister::registeAllStateGroup()
{}