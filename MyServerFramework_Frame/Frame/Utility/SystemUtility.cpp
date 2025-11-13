#include "FrameHeader.h"

#ifdef WINDOWS
#pragma comment(lib, "Dbghelp.lib")
#endif

namespace SystemUtility
{
	llong mIDSeedMain;
	atomic<llong> mIDSeedThread;
	llong mTimeMSecondUTC = 0;
	llong mTimeSecondUTC = 0;
	int mMainThread = 0;

	void stop()
	{
		ServerFramework::getSingleton()->stop();
	}

	void getTime(int& weekDay, int& year, int& month, int& day, int& hour, int& minute, int& second)
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		weekDay = sys.wDayOfWeek;
		year = sys.wYear;
		month = sys.wMonth;
		day = sys.wDay;
		hour = sys.wHour;
		minute = sys.wMinute;
		second = sys.wSecond;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		weekDay = date.tm_wday;
		year = date.tm_year + 1900;
		month = date.tm_mon + 1;
		day = date.tm_mday;
		hour = date.tm_hour;
		minute = date.tm_min;
		second = date.tm_sec;
#endif
	}

	int getYear()
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		return sys.wYear;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		return date.tm_year + 1900;
#endif
	}

	int getMonth()
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		return sys.wMonth;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		return date.tm_mon + 1;
#endif
	}

	void getYearMonth(int& year, int& month)
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		year = sys.wYear;
		month = sys.wMonth;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		year = date.tm_year + 1900;
		month = date.tm_mon + 1;
#endif
	}

	int getDay()
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		return sys.wDay;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		return date.tm_mday;
#endif
	}

	void getTime(int& year, int& month, int& day, int& hour, int& minute, int& second)
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		year = sys.wYear;
		month = sys.wMonth;
		day = sys.wDay;
		hour = sys.wHour;
		minute = sys.wMinute;
		second = sys.wSecond;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		year = date.tm_year + 1900;
		month = date.tm_mon + 1;
		day = date.tm_mday;
		hour = date.tm_hour;
		minute = date.tm_min;
		second = date.tm_sec;
#endif
	}

	void getTime(int& hour, int& minute, int& second)
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		hour = sys.wHour;
		minute = sys.wMinute;
		second = sys.wSecond;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		hour = date.tm_hour;
		minute = date.tm_min;
		second = date.tm_sec;
#endif
	}

	int getTimeHourInDay()
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		return sys.wHour;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		return date.tm_hour;
#endif
	}

	string getTime(const bool timeStamp)
	{
		MyString<128> timeBuffer;
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		if (timeStamp)
		{
			SPRINTF(timeBuffer.toBuffer(), timeBuffer.size(), "%d-%02d-%02d %02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		}
		else
		{
			SPRINTF(timeBuffer.toBuffer(), timeBuffer.size(), "%04d年%02d月%02d日%02d时%02d分%02d秒%03d毫秒", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
		}
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		if (timeStamp)
		{
			SPRINTF(timeBuffer.toBuffer(), timeBuffer.size(), "%d-%02d-%02d %02d:%02d:%02d", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min, date.tm_sec);
		}
		else
		{
			SPRINTF(timeBuffer.toBuffer(), timeBuffer.size(), "%04d年%02d月%02d日%02d时%02d分%02d秒", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min, date.tm_sec);
		}
#endif
		return timeBuffer.str();
	}

	llong getTodayEnd()
	{
		return getTodayBegin() + daysToSeconds(1);
	}

	llong getTodayBegin()
	{
		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
		int second = 0;
		getTime(year, month, day, hour, minute, second);
		return convertToTimestamp(year, month, day, 0, 0, 0);
	}

	int getDayOfWeek()
	{
#ifdef WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		return sys.wDayOfWeek;
#elif defined LINUX
		time_t tt;
		time(&tt);
		struct tm date;
		localtime_r(&tt, &date);
		return date.tm_wday;
#endif
	}

	bool isSameDay(time_t timeStamp0, time_t timeStamp1)
	{
		struct tm dateTime0 = getTimeStruct(timeStamp0);
		struct tm dateTime1 = getTimeStruct(timeStamp1);
		return dateTime0.tm_year == dateTime1.tm_year &&
			   dateTime0.tm_mon == dateTime1.tm_mon &&
			   dateTime0.tm_mday == dateTime1.tm_mday;
	}

	tm getTimeStruct(const time_t timeStamp)
	{
		struct tm dateTime;
#ifdef WINDOWS
		localtime_s(&dateTime, &timeStamp);
#elif defined LINUX
		localtime_r(&timeStamp, &dateTime);
#endif
		// 转换为绝对的年份,以及从1开始的月份
		dateTime.tm_year += 1900;
		dateTime.tm_mon += 1;
		return dateTime;
	}

	time_t convertToTimestamp(int year, int month, int day, int hour, int minute, int second)
	{
		struct tm tm_struct = {};
		tm_struct.tm_year = year - 1900; // 年份从1900开始计算
		tm_struct.tm_mon = month - 1;    // 月份0-11
		tm_struct.tm_mday = day;
		tm_struct.tm_hour = hour;
		tm_struct.tm_min = minute;
		tm_struct.tm_sec = second;
		tm_struct.tm_isdst = -1;
		return mktime(&tm_struct);
	}

	int getDaysInMonth()
	{
		int year = 0;
		int month = 0;
		getYearMonth(year, month);
		return getDaysInMonth(year, month);
	}

	int getDaysInMonth(int year, int month)
	{
		switch (month) 
		{
		case 1: 
		case 3: 
		case 5: 
		case 7: 
		case 8: 
		case 10: 
		case 12: return 31;
		case 4: 
		case 6: 
		case 9: 
		case 11: return 30;
		case 2: return isLeapYear(year) ? 29 : 28;
		default: return 0;
		}
	}

	// 获得cpu核心数
	int getCPUCoreCount()
	{
#ifdef WINDOWS
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		return si.dwNumberOfProcessors;
#elif defined LINUX
		return get_nprocs();
#endif
	}

	// 获取外网的IP
	string getInternetIP(MY_SOCKET socket)
	{
#ifdef WINDOWS
		SOCKADDR_IN addr_conn;
		int nSize = sizeof(addr_conn);
		memset((void*)&addr_conn, 0, sizeof(addr_conn));
		getpeername(socket, (SOCKADDR*)(&addr_conn), &nSize);
		return string(inet_ntoa(addr_conn.sin_addr));
#elif defined LINUX
		struct sockaddr_in addr_conn;
		int nSize = sizeof(addr_conn);
		memset((void*)&addr_conn, 0, sizeof(addr_conn));
		getpeername(socket, (struct sockaddr*)(&addr_conn), (socklen_t*)&nSize);
		return string(inet_ntoa(addr_conn.sin_addr));
#endif
	}

	string getLocalIP(MY_SOCKET socket)
	{
#ifdef WINDOWS
		SOCKADDR_IN addr_conn;
		int nSize = sizeof(addr_conn);
		memset((void*)&addr_conn, 0, sizeof(addr_conn));
		getsockname(socket, (SOCKADDR*)(&addr_conn), &nSize);
		return string(inet_ntoa(addr_conn.sin_addr));
#elif defined LINUX
		struct sockaddr_in addr_conn;
		int nSize = sizeof(addr_conn);
		memset((void*)&addr_conn, 0, sizeof(addr_conn));
		getsockname(socket, (struct sockaddr*)(&addr_conn), (socklen_t*)&nSize);
		return string(inet_ntoa(addr_conn.sin_addr));
#endif
	}

	void makeSockAddrByHost(sockaddr_in& addr, const char* host, const ushort port)
	{
		struct hostent* hptr = gethostbyname(host);
		if (hptr == nullptr || hptr->h_addr_list == nullptr)
		{
			return;
		}
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
#ifdef WINDOWS
		addr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(*(in_addr*)hptr->h_addr_list[0]));
#elif defined LINUX
		addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(in_addr*)hptr->h_addr_list[0]));
#endif
	}

	void makeSockAddrByIP(sockaddr_in& addr, const char* ip, const ushort port)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
#ifdef WINDOWS
		addr.sin_addr.S_un.S_addr = inet_addr(ip);
#elif defined LINUX
		addr.sin_addr.s_addr = inet_addr(ip);
#endif
	}

	void makeSockAddr(sockaddr_in& addr, const ulong hostlong, const ushort port)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
#ifdef WINDOWS
		addr.sin_addr.S_un.S_addr = htonl(hostlong);
#elif defined LINUX
		addr.sin_addr.s_addr = htonl(hostlong);
#endif
	}

	void print(const char* str, const bool nextLine)
	{
#ifdef WINDOWS
		cout << str;
		if (nextLine)
		{
			cout << "\n";
		}
#elif defined LINUX
		printf("%s", str);
		if (nextLine)
		{
			printf("%s", "\n");
		}
#endif
	}

	void input(string& str)
	{
#ifdef WINDOWS
		cin >> str;
#elif defined LINUX
		MyString<256> i;
		if (scanf("%s", i.toBuffer()) == 1)
		{
			str = i.str();
		}
#endif
	}

	bool launchExe(const string& path, const string& fullName)
	{
#ifdef WINDOWS
		// 启动游戏程序
		SHELLEXECUTEINFO sei;
		memset(&sei, 0, sizeof(sei));
		sei.cbSize = sizeof(sei);
		sei.lpFile = fullName.c_str();
		sei.lpDirectory = path.c_str();
		sei.lpVerb = "open";
#ifndef __WXWINCE__
		sei.nShow = SW_SHOWNORMAL; // SW_SHOWDEFAULT not defined under CE (#10216)
#else
		sei.nShow = SW_SHOWDEFAULT;
#endif
		sei.fMask = SEE_MASK_FLAG_NO_UI;
		return ShellExecuteEx(&sei) == TRUE;
#elif defined LINUX
		if (vfork() == 0)
		{
			char* argv[] = { (char*)"", (char*)nullptr };
			execv(fullName.c_str(), argv);
		}
		return true;
#endif
	}

#ifdef WINDOWS
	bool isExeRunning(const string& fileName)
	{
		// 判断当前是否已经运行了该游戏,如果已经运行则直接退出
		Set<string> processList;
		getAllProcess(processList);
		return processList.contains(fileName);
	}

	void getAllProcess(Set<string>& processList)
	{
		const HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获得系统快照句柄 
		PROCESSENTRY32 info;
		info.dwSize = sizeof(PROCESSENTRY32);
		//调用一次 Process32First 函数，从快照中获取进程列表 
		Process32First(handle, &info);
		//重复调用 Process32Next，直到函数返回 FALSE 为止 
		while (Process32Next(handle, &info))
		{
			processList.insert(info.szExeFile);
		}
	}

	int getPID()
	{
		return 0;
	}

	void launchExeInScreen(const string& screenName, const string& fullPath) {}

#elif defined LINUX
	int getPID()
	{
		return getpid();
	}

	void getPidFromStr(const char* str, char* pid, const int size)
	{
		int pos1 = 0;
		int pos2 = 0;
		FOR_I(strlength(str))
		{
			int tmp = 0;
			if (str[i] >= '0' && str[i] <= '9')
			{
				tmp = 1;
				pos1 = i;
			}
			if (tmp == 1 && (str[i] < '0' || str[i] > '9'))
			{
				pos2 = i;
				break;
			}
		}
		memset(pid, 0, size);
		for (int i = pos1, j = 0; i < pos2; ++i, ++j)
		{
			pid[j] = str[i];
		}
	}

	bool isExeRunning(const string& fileName)
	{
		FILE* fstream = popen((string("ps axhw -o pid,cmd | grep ") + getFileNameNoSuffix(fileName, true)).c_str(), "r");
		if (fstream == nullptr)
		{
			return false;
		}
		bool isRunning = false;
		MyString<1024> buff;
		Vector<string> temp;
		while (fgets(buff.toBuffer(), buff.size(), fstream) != nullptr)
		{
			temp.clear();
			split(buff.str(), " ", temp);
			if (temp.size() > 0 && getExePath(temp[0]) == fileName)
			{
				isRunning = true;
				break;
			}
		}
		pclose(fstream);
		return isRunning;
	}

	string getExePath(const string& pid)
	{
		MyString<256> task_absolute_path;
		if (readlink(("/proc/" + pid + "/exe").c_str(), task_absolute_path.toBuffer(), 256) < 0)
		{
			return "";
		}
		return task_absolute_path.str();
	}

	void launchExeInScreen(const string& screenName, const string& fullPath)
	{
		string path = getFilePath(fullPath);
		string cmd = "./" + getFileName(fullPath);
		system(("screen -S " + screenName + " -X stuff 'cd " + path + " && " + cmd + "\n'").c_str());
	}

	void memoryUsage(llong& vmUsageKB, llong& residentSetSizeKB)
	{
		std::ifstream stat_stream("/proc/self/stat", std::ios_base::in); //get info from proc directory
		//创建一些变量以获取信息
		string pid, comm, state, ppid, pgrp, session, tty_nr;
		string tpgid, flags, minflt, cminflt, majflt, cmajflt;
		string utime, stime, cutime, cstime, priority, nice;
		string O, itrealvalue, starttime;
		ulong vsize = 0;
		long rss = 0;
		stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
			>> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
			>> utime >> stime >> cutime >> cstime >> priority >> nice
			>> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest
		stat_stream.close();
		long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // for x86-64 is configured to use 2MB pages
		vmUsageKB = (llong)(vsize / 1024.0);
		residentSetSizeKB = rss * page_size_kb;
	}

#endif

#ifdef WINDOWS
	string getStackTrace(int depth)
	{
		constexpr int MAX_DEPTH = 20;
		depth = clampMax(depth + 1, MAX_DEPTH);
		Array<MAX_DEPTH, void*> pStack;
		HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
		if (process == nullptr)
		{
			return "";
		}
		SymInitialize(process, nullptr, TRUE);
		const WORD frames = CaptureStackBackTrace(0, depth, pStack.data(), nullptr);
		string oss = "stack traceback: \n";
		FOR_I(frames)
		{
			if (i == 0)
			{
				continue;
			}
			const DWORD64 address = (DWORD64)(pStack[i]);
			DWORD64 displacementSym = 0;
			constexpr char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)]{ 0 };
			const PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
			pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
			pSymbol->MaxNameLen = MAX_SYM_NAME;
			DWORD displacementLine = 0;
			IMAGEHLP_LINE64 line;
			line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
			if (SymFromAddr(process, address, &displacementSym, pSymbol) && SymGetLineFromAddr64(process, address, &displacementLine, &line))
			{
				oss += getFileName(line.FileName);
				oss += ":";
				// 这里不能使用IToS,容易造成死循环
				oss += to_string(line.LineNumber);
				oss += "\n";
			}
			else
			{
				oss += "error: ";
				oss += to_string(GetLastError());
				oss += "\n";
			}
		}
		SymCleanup(process);
		return oss;
	}

#elif defined LINUX
	string getStackTrace(int depth)
	{
		string stack;
		Array<512, void*> buffer;
		const int nptrs = (int)::backtrace(buffer.data(), buffer.size());
		char** strings = ::backtrace_symbols(buffer.data(), nptrs);
		if (strings == nullptr)
		{
			return stack;
		}
		FOR_I(nptrs)
		{
			stack.append(strings[i]);
			stack.push_back('\n');
			if (i >= depth + 1)
			{
				break;
			}
		}
		free(strings);
		return stack;
	}
#endif
}