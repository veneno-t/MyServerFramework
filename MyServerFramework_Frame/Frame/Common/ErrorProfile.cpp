#pragma once

namespace ErrorProfile
{
	ErrorProfileEvent mOnErrorProfileEvent;

	void errorProfile(string&& log, string&& file)
	{
		CALL(mOnErrorProfileEvent, move(log), move(file));
		// windows下发生错误就直接暂停运行
#ifdef WINDOWS
		system("pause");
#endif
	}
};