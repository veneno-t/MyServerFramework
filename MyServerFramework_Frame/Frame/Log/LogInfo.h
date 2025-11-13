#pragma once

#include "ClassObject.h"

class MICRO_LEGEND_FRAME_API LogInfo : public ClassObject
{
	BASE(LogInfo, ClassObject);
public:
	void resetProperty() override;
public:
	llong mPlayerGUID = 0;
	llong mTime = 0;
	string mLog;
	string mStack;
	bool mError = false;
};