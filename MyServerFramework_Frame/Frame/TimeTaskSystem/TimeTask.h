#pragma once

#include "ClassObject.h"
#include "TimeValue.h"

class MICRO_LEGEND_FRAME_API TimeTask : public ClassObject
{
	BASE(TimeTask, ClassObject);
public:
	virtual ~TimeTask() { destroy(); }
	void destroy() override;
	virtual void init(){}
	virtual void update(const float elapsedTime){}
	void resetProperty() override;
protected:
	TimePoint* mTimePoint = nullptr;
};