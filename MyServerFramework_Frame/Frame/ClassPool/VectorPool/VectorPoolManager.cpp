#include "FrameHeader.h"

HashMap<llong, VectorPoolBase*> VectorPoolManager::mVectorPoolThreadList;

VectorPoolManager::~VectorPoolManager()
{
	DELETE_MAP(mVectorPoolThreadList);
}