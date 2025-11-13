#pragma once

#include "FrameComponent.h"

class MICRO_LEGEND_FRAME_API HttpManager : public FrameComponent
{
	BASE(HttpManager, FrameComponent);
public:
	void init() override;
	void quit() override;
	void requestHttpGet(const string& url, const string& contentType, const StringCallback& callback);
	void requestHttpPost(const string& url, const string& contentType, const string& postData, const StringCallback& callback);
	string httpGet(const string& url, const string& contentType, int* code = nullptr);
	string httpPost(const string& url, const string& contentType, const string& postData, int* code = nullptr);
protected:
	static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);
	static void curlThread(CustomThread* thread) {}
protected:
	CustomThread* mThread = nullptr;
};