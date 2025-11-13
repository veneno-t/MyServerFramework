#pragma once

#include "FrameBase.h"

// 退出一个账号
class MICRO_LEGEND_FRAME_API CmdNetServerLogoutAccount
{
public:
	static void execute(TCPServerClient* client);
	static void execute(WebSocketServerClient* client);
public:
	static TCPServerClientCallback mLogoutAccount;								// 退出玩家账号的回调,用于通知应用层退出账号登录
	static TCPServerClientCallback mLogoutPlayer;								// 退出玩家角色的回调,用于通知应用层退出角色登录
	static TCPServerClientCallback mLogoutPlayerConnectError;					// 玩家网络断开时的回调,用于通知应用层进行准备断线重连
	static WebSocketServerClientCallback mWebSocketLogoutAccount;				// 退出玩家账号的回调,用于通知应用层退出账号登录,websocket
	static WebSocketServerClientCallback mWebSocketLogoutPlayer;				// 退出玩家角色的回调,用于通知应用层退出角色登录,websocket
	static WebSocketServerClientCallback mWebSocketLogoutPlayerConnectError;	// 玩家网络断开时的回调,用于通知应用层进行准备断线重连
};