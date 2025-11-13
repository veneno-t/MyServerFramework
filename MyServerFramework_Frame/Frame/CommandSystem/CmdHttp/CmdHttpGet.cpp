#include "FrameHeader.h"

void CmdHttpGet::execute()
{
	const string response = mHttpManager->httpGet(mURL, mContentType);
	CALL(mCallback, response);
}