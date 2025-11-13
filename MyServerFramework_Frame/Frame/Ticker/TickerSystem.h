#pragma once

#include "FrameComponent.h"
#include "FrameCallback.h"

class MICRO_LEGEND_FRAME_API TickerSystem : public FrameComponent
{
	BASE(TickerSystem, FrameComponent);
public:
	void quit() override;
	void update(const float elapsedTime) override;
	// 回调的返回值表示是否继续执行这个更新器
	void createTicker(BoolFunction callback);
protected:
	SafeVector<Ticker*> mTickerList;
};