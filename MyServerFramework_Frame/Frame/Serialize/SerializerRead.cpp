#include "FrameHeader.h"

SerializerRead::SerializerRead(const char* buffer, const int bufferSize):
	mBuffer(buffer),
	mBufferSize(bufferSize),
	mIndex(0)
{}

bool SerializerRead::readVector2List(Vector<Vector2>& list)
{
	int count;
	if (!read(count))
	{
		return false;
	}
	bool result = true;
	list.resize(count);
	FOR_I(count)
	{
		result = readVector2(list[i]) && result;
	}
	return result;
}
bool SerializerRead::readVector2IntList(Vector<Vector2Int>& list)
{
	int count;
	if (!read(count))
	{
		return false;
	}
	bool result = true;
	list.resize(count);
	FOR_I(count)
	{
		result = readVector2Int(list[i]) && result;
	}
	return result;
}
bool SerializerRead::readVector3List(Vector<Vector3>& list)
{
	int count;
	if (!read(count))
	{
		return false;
	}
	bool result = true;
	list.resize(count);
	FOR_I(count)
	{
		result = readVector3(list[i]) && result;
	}
	return result;
}
bool SerializerRead::readVector3IntList(Vector<Vector3Int>& list)
{
	int count;
	if (!read(count))
	{
		return false;
	}
	bool result = true;
	list.resize(count);
	FOR_I(count)
	{
		result = readVector3Int(list[i]) && result;
	}
	return result;
}

bool SerializerRead::readStringList(Vector<string>& list)
{
	int count;
	if (!read(count))
	{
		return false;
	}
	bool result = true;
	list.resize(count);
	FOR_I(count)
	{
		result = readString(list[i]) && result;
	}
	return true;
}

bool SerializerRead::readBuffer(char* buffer, const int bufferSize, const int readLen)
{
	// 如果存放数据的空间大小不足以放入当前要读取的数据,则只拷贝能容纳的长度,但是下标应该正常跳转
	bool result = BinaryUtility::readBuffer(mBuffer, mBufferSize, mIndex, buffer, bufferSize, readLen);
	if (result)
	{
		mIndex += readLen;
	}
	return result;
}

bool SerializerRead::readBufferNoCopy(const char*& destBuffer, const int readLength)
{
	if (destBuffer != nullptr)
	{
		return false;
	}
	if (mIndex + readLength > mBufferSize)
	{
		return false;
	}
	destBuffer = mBuffer + mIndex;
	mIndex += readLength;
	return true;
}

bool SerializerRead::readString(char* str, int bufferSize)
{
	// 先读入字符串长度
	int readLen = 0;
	if (!read(readLen))
	{
		return false;
	}
	str[readLen] = 0;
	return BinaryUtility::readBuffer(mBuffer, mBufferSize, mIndex, str, bufferSize, readLen);
}

bool SerializerRead::readString(string& str)
{
	// 先读入字符串长度
	int readLen = 0;
	if (!read(readLen))
	{
		return false;
	}
	str.resize(readLen);
	return BinaryUtility::readBuffer(mBuffer, mBufferSize, mIndex, (char*)str.c_str(), readLen + 1, readLen);
}