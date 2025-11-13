#pragma once

#include "FrameMacro.h"

class FrameStringDefine
{
public:
	// Component
	static constexpr ushort MovableObjectComponentMove = 1;
	static constexpr ushort MovableObjectComponentMoveCurve = 2;
	static constexpr ushort MovableObjectComponentTrackTarget = 3;

	static constexpr ushort COMMonsterDecisionTree = 50;
	static constexpr ushort COMCharacterStateMachine = 51;
};