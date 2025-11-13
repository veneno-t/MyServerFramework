#include "FrameHeader.h"

void FrameStateManager::quit()
{
	DELETE_MAP(mGroupStateList);
	mStateGroupList.clear();
}