#pragma once

#include "ClassObject.h"
#include "FrameCallback.h"

class MICRO_LEGEND_FRAME_API Ticker : public ClassObject
{
	BASE(Ticker, ClassObject);
public:
	virtual ~Ticker() { destroy(); }
	void destroy() override { base::destroy(); }
	void update(float elapsedTime);
	void resetProperty() override;
	bool isFinish() const { return mFinish; }
	// 返回值表示是否要继续运行下去,当返回false时,此更新器将会被自动销毁
	void setCallback(BoolFunction callback) { mCallback = callback; mFinish = false; }
protected:
	BoolFunction mCallback = nullptr;
	bool mFinish = false;
};