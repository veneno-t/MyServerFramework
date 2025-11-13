#pragma once

#include "FrameComponent.h"
#include "HttpListenInfo.h"

class MICRO_LEGEND_FRAME_API HttpServerSystem : public FrameComponent
{
	BASE(HttpServerSystem, FrameComponent);
public:
#ifdef _LIBEVENT
	virtual ~HttpServerSystem() { destroy(); }
	void init() override;
	void destroy();
	void update(float elapsedTime) override;
	void listenHttp(const string& uri, HttpCallback callback, void* userData);
	void doResponse(evhttp_request* req, const string& response, int code = HTTP_OK, const string& contentType = FrameDefine::EMPTY);
	// 按照库中提供的函数来写的
	static char* findHttpHeader(struct evhttp_request* req, struct evkeyvalq* params, const char* query_char);
	static char* findHttpQuery(struct evhttp_request* req);
	// 自己实现的带有缓存的方法
	const string& getHttpHeader(struct evhttp_request* req, const string& key);
	static string getPostParam(struct evhttp_request* req);
protected:
	static void httpResponse(evhttp_request* req, void* arg);
protected:
	static constexpr int mBufferSize = 1024 * 32;
	HashMap<string, HttpListenInfo*> mCallbackList;
	HashMap<evhttp_request*, HashMap<string, string>> mRequestHeaders;		// 缓存的每个请求的header参数列表
	event_base* mEventBase = nullptr;
	SSL_CTX* mSSLContext = nullptr;
	evhttp* mHttpServer = nullptr;
	int mPort = 0;
#endif
};