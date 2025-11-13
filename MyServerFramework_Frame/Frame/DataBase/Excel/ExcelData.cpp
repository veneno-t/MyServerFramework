#include "FrameHeader.h"

void ExcelData::clone(ExcelData* target)
{
	target->mID = mID;
}

void ExcelData::read(SerializerRead* reader)
{
	reader->read(mID);
}