#pragma once

// 能够被其他组件中断的组件
class IComponentBreakable
{
public:
	virtual void notifyBreak() = 0;
};

// 会修改位置的组件
class IComponentModifyPosition : public IComponentBreakable {};

// 会修改旋转的组件
class IComponentModifyRotation : public IComponentBreakable {};

// 会修改缩放的组件
class IComponentModifyScale : public IComponentBreakable {};