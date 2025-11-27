#pragma once

#include "FrameDefine.h"
#include "Vector.h"

template<typename Callback, typename... Args>
void CALL(Callback&& cb, Args&&... args)
{
	if (cb != nullptr)
	{
		forward<Callback>(cb)(forward<Args>(args)...);
	}
}

// 回调
// 通用回调定义
typedef void (*CustomThreadCallback)(CustomThread* thread);
typedef void (*KeyFrameCallback)(ComponentKeyframe* component, bool breakTrembling, void* userData);
typedef void (*TrackCallback)(ComponentTrackTarget* component, bool breakTrack, void* userData);
typedef void (*OnObjectDestroy)(MovableObject* obj, void* userData);
typedef void (*EventCallback)(GameEvent* param, IEventListener* listener);
typedef void (*SQLiteParseFunction)(void* ptr, SQLiteDataReader* reader, int index);
typedef void (*SQLiteInsertFunction)(char* str, int size, void* ptr, bool notLastOne);
typedef void (*SQLiteUpdateFunction)(char* str, int size, const char* col, void* ptr, bool notLastOne);
typedef void (*CommandCallback)(GameCommand* cmd, void* user_data);
typedef void (*ServerCheckPingCallback)(TCPServerClient* client, int index);
typedef void (*WebServerCheckPingCallback)(WebSocketServerClient* client, int index);
typedef void (*FreezeAccountCallback)(llong accountGUID, llong timeSecond, const char* reason);
#ifdef _LIBEVENT
typedef void (*HttpCallback)(evhttp_request* req, const string& uri, void* userData);
#endif
// 定义为普通的函数指针,方便进行比较,占用内存也较小
typedef void (*FrameTickCallback)(GameComponent* component, float elapsedTime);
typedef void (*SecondTickCallback)(GameComponent* component);

// 通用回调定义
typedef function<void()> VoidCallback;
typedef function<void(void* ptr)> VoidPtrCallback;
typedef function<void(bool result)> BoolCallback;
typedef function<void(int value)> IntCallback;
typedef function<void(float value)> FloatCallback;
typedef function<void(llong dataCount)> LLongCallback;
typedef function<void(const string& value)> StringCallback;
typedef function<void(MySQLData* data)> MySQLDataCallback;

typedef function<void(CharacterState* state)> CharacterStateCallback;
typedef function<void(TCPServerClient* client)> TCPServerClientCallback;
typedef function<void(WebSocketServerClient* client)> WebSocketServerClientCallback;
typedef function<void(const Vector<MySQLData*>& dataList)> QueryDataListCallback;
typedef function<void(string&& log, string&& file)> ErrorProfileEvent;
typedef function<void(llong accountGUID, llong unfreezeTime, const string& reason)> FreezeAccountEvent;

// 带返回值的回调
typedef function<bool()> BoolFunction;

template <typename T>
using QueryDataCallbackT = function<void(T* data)>;
template <typename T>
using QueryDataListCallbackT = function<void(const Vector<T*>& dataList)>;