#pragma once

#include "FrameMacro.h"

// 只开放部分std的内容,避免不必要的命名冲突
using std::vector;
using std::map;
using std::set;
using std::stack;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::wstring;
using std::atomic_flag;
using std::make_pair;
using std::exception;
using std::move;
using std::forward;
using std::is_same;
#ifdef WINDOWS
using std::conjunction;
#endif
using std::decay;
using std::function;
using std::atomic;
using std::enable_if_t;
using std::tuple;
using std::remove_cv;
using std::remove_reference;
using std::initializer_list;
using std::array;
using std::is_enum;
using std::to_string;
using std::ostringstream;
using std::bitset;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::duration;
using std::micro;
using std::chrono::time_point;
using std::this_thread::sleep_for;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
// 基础数据类型简化定义
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;
typedef long long llong;