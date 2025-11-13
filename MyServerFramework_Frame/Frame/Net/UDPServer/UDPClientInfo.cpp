#include "FrameHeader.h"

void UDPClientInfo::clear()
{
	for (auto& item : mSendList)
	{
		DELETE_ARRAY(item.first);
	}
	mSendList.clear();
}