#include "GameHeader.h"

void Game::registeComponent()
{
	base::registeComponent();
	// auto generate start FrameSystem Register
	registeSystem<GameConfigSystem>(STR(GameConfigSystem));
	// auto generate end FrameSystem Register
}

void Game::constructDone()
{
	base::constructDone();
	constructGameDone();
	// 由于其他系统组件的初始化可能会用到列表对象池,所以需要在初始化之前就注册对象池
	GameSTLPoolRegister::registeAll();
	// SQLite和MySQL的注册只能在此处写,因为在其他系统组件的初始化里面会用到这些
	SQLiteRegister::registeAll();
	MySQLRegister::registeAll();
	// 等待所有表格都注册完毕后才能检查表格数据
	mSQLiteManager->checkAll();
}

void Game::clearSystem()
{
	base::clearSystem();
	clearGameSystem();
}

void Game::registe()
{
	base::registe();
	CharacterRegister::registeAll();
	GamePacketRegister::registeAll();
}

void Game::launch()
{
	base::launch();
	mTCPServerSystem->setServerCheckPingCallback([](TCPServerClient* client, const int index)
	{
		SCServerCheckPing::send(client, index);
	});
	// CmdNetServerLogoutAccount内部是为了支持断线重连的,但是重连的绝大部分逻辑都在应用层,底层只是针对网络连接断开时是否要去退出账号和角色
	CmdNetServerLogoutAccount::mLogoutPlayer = ([](TCPServerClient* client)
	{
		auto* player = static_cast<CharacterPlayer*>(mCharacterManager->getCharacter(client->getPlayerGUID()));
		if (player != nullptr)
		{
			LOG("玩家退出登录：" + player->getPrintName() + ", ID:" + LLToS(player->getGUID()));
			// 将角色销毁
			CmdCharacterManagerDestroyCharacter::execute(player);
		}
		// 通知网络客户端角色退出登录
		client->setPlayerGUID(0);
	});
	CmdNetServerLogoutAccount::mLogoutAccount = ([](TCPServerClient* client)
	{
		client->setAccountGUID(0);
	});
}