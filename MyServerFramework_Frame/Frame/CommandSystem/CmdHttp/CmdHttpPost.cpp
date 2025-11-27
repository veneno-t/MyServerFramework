#include "FrameHeader.h"

void CmdHttpPost::execute()
{
#ifdef BUILDING_LIBCURL
	const string response = mHttpManager->httpPost(mURL, mContentType, mPostData);
	CALL(mCallback, response);
#endif
}