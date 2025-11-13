#include "FrameHeader.h"

void HttpManager::init()
{
    curl_global_init(CURL_GLOBAL_ALL);

    // 创建curl线程,该线程只需要执行命令即可
    mThread = mThreadManager->createThread("curl", curlThread, this);
    mThread->setBackground(false);
    mThread->setCmdDebug(true);
    mThread->setTime(50);
}

void HttpManager::quit()
{
    mThreadManager->destroyThread(mThread);
    mThread = nullptr;
    curl_global_cleanup();
}

void HttpManager::requestHttpGet(const string& url, const string& contentType, const StringCallback& callback)
{
    auto* cmd = CMD_THREAD<CmdHttpGet>();
    cmd->mURL = url;
    cmd->mCallback = callback;
    mCommandSystem->pushCommandThread(cmd, this, mThread);
}

void HttpManager::requestHttpPost(const string& url, const string& contentType, const string& postData, const StringCallback& callback)
{
    auto* cmd = CMD_THREAD<CmdHttpPost>();
    cmd->mURL = url;
    cmd->mContentType = contentType;
    cmd->mPostData = postData;
    cmd->mCallback = callback;
    mCommandSystem->pushCommandThread(cmd, this, mThread);
}

string HttpManager::httpGet(const string& url, const string& contentType, int* code)
{
    CURL* curl = curl_easy_init();    // 初始化
    if (curl == nullptr)
    {
        ERROR("无法创建curl");
        return "";
    }
    curl_slist* headers = nullptr;
    if (contentType.empty())
    {
        headers = curl_slist_append(headers, "Content-Type: application/json");
    }
    else
    {
        headers = curl_slist_append(headers, ("Content-Type: " + contentType).c_str());
    }
    headers = curl_slist_append(headers, "Charset: UTF-8");
    string response;
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);// 改协议头
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, string* data)
    {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //将返回的http头输出到fp指向的文件
    // 执行
    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK)
    {
        LOG("请求失败:" + url + ", code:" + IToS(result));
    }
    if (code != nullptr)
    {
        *code = result;
    }
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return response;
}

size_t HttpManager::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    static_cast<string*>(userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

string HttpManager::httpPost(const string& url, const string& contentType, const string& postData, int* code)
{
    CURL* curl = curl_easy_init();
    if (curl == nullptr)
    {
        ERROR("无法创建curl");
        return "";
    }
    // 设置 URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    // 10秒超时
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    // 构建 JSON 数据
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postData.size());
    // 设置 JSON 头
    curl_slist* headers = nullptr;
    if (!contentType.empty())
    {
        headers = curl_slist_append(headers, ("Content-Type: " + contentType).c_str());
    }
    else
    {
        headers = curl_slist_append(headers, "Content-Type: application/json");
    }
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Charset: UTF-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // 捕获响应
    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    // 执行请求
    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK)
    {
        LOG("请求失败:" + url + ", code:" + IToS(result));
    }
    if (code != nullptr)
    {
        *code = result;
    }
    // 清理资源
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return response;
}