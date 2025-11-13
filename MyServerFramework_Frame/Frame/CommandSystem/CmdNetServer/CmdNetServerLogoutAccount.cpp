#include "FrameHeader.h"

TCPServerClientCallback CmdNetServerLogoutAccount::mLogoutAccount;
TCPServerClientCallback CmdNetServerLogoutAccount::mLogoutPlayer;
TCPServerClientCallback CmdNetServerLogoutAccount::mLogoutPlayerConnectError;
WebSocketServerClientCallback CmdNetServerLogoutAccount::mWebSocketLogoutAccount;
WebSocketServerClientCallback CmdNetServerLogoutAccount::mWebSocketLogoutPlayer;
WebSocketServerClientCallback CmdNetServerLogoutAccount::mWebSocketLogoutPlayerConnectError;

void CmdNetServerLogoutAccount::execute(TCPServerClient* client)
{
	if (client == nullptr)
	{
		return;
	}

	// 如果是网络原因导致断开,会等待角色进行重连
	if (client->getDeadType() == DEAD_TYPE::NET_ERROR)
	{
		// 如果玩家在线,则给玩家角色标记即将销毁,设置销毁倒计时,以及重连凭证
		if (client->getPlayerGUID() > 0)
		{
			CALL(mLogoutPlayerConnectError, client);
		}
		// 如果玩家不在线,就直接退出账号登录
		else
		{
			if (client->getAccountGUID() > 0)
			{
				CALL(mLogoutAccount, client);
				client->setAccountGUID(0);
			}
		}
	}
	// 如果是客户端主动断开,或者是服务器踢下线的,就需要退出账号和角色
	else
	{
		if (client->getPlayerGUID() > 0)
		{
			mUDPServerSystem->getClient()->removeClientToken(client->getPlayerGUID());
			CALL(mLogoutPlayer, client);
		}
		if (client->getAccountGUID() > 0)
		{
			CALL(mLogoutAccount, client);
			client->setAccountGUID(0);
		}
	}
}

void CmdNetServerLogoutAccount::execute(WebSocketServerClient* client)
{
	if (client == nullptr)
	{
		return;
	}

	// 强制退出角色和账号
	if (client->getDeadType() == DEAD_TYPE::NET_ERROR)
	{
		// 如果玩家在线,则给玩家角色标记即将销毁,设置销毁倒计时,以及重连凭证
		if (client->getPlayerGUID() > 0)
		{
			CALL(mWebSocketLogoutPlayerConnectError, client);
		}
		// 如果玩家不在线,就直接退出账号登录
		else
		{
			if (client->getAccountGUID() > 0)
			{
				CALL(mWebSocketLogoutAccount, client);
				client->setAccountGUID(0);
			}
		}
	}
	else
	{
		if (client->getPlayerGUID() > 0)
		{
			mUDPServerSystem->getClient()->removeClientToken(client->getPlayerGUID());
			CALL(mWebSocketLogoutPlayer, client);
		}
		if (client->getAccountGUID() > 0)
		{
			CALL(mWebSocketLogoutAccount, client);
			client->setAccountGUID(0);
		}
	}
}