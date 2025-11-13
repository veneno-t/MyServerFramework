#ifdef _MYSQL
#include "FrameHeader.h"

namespace FrameMySQLUtility
{
	void pushCommandToMySQL(GameCommand* cmd)
	{
		if (mMySQLManager->getThread() == nullptr)
		{
			ERROR("数据库线程还未创建,无法执行数据库命令");
		}
		mCommandSystem->pushCommandThread(cmd, mMySQLManager, mMySQLManager->getThread());
	}
}
#endif