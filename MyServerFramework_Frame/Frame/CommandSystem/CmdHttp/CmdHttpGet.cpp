#include "FrameHeader.h"

void CmdHttpGet::execute()
{
#ifdef BUILDING_LIBCURL
	const string response = mHttpManager->httpGet(mURL, mContentType);
	CALL(mCallback, response);
#endif
}