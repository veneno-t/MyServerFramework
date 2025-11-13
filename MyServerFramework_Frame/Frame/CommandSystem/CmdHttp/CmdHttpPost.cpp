#include "FrameHeader.h"

void CmdHttpPost::execute()
{
	const string response = mHttpManager->httpPost(mURL, mContentType, mPostData);
	CALL(mCallback, response);
}