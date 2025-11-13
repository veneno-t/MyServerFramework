#pragma once

#include "ClassTypePoolThread.h"
#include "PacketWebSocketFactoryManager.h"

class PacketWebSocketPool : public ClassTypePool<PacketWebSocket, ushort>
{
protected:
	PacketWebSocket* create(const ushort type) override
	{
		auto* factory = mPacketWebSocketFactoryManager->getFactory(type);
		if (factory == nullptr)
		{
			return nullptr;
		}
		return factory->create();
	}
};