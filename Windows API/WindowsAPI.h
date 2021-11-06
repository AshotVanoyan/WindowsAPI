#pragma once
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include <string>



class WindowsAPI {
public:
	static void errorTextOutput();

	static HANDLE createFile(TCHAR*);

	static HANDLE getFile(TCHAR*);

	static bool readFile(TCHAR*);

	static bool writeFile(TCHAR*, char*);

	static bool copy(TCHAR*, TCHAR*);

	static bool readWrite(TCHAR*, TCHAR*);

	static bool createDirectory(TCHAR*);

	static bool setCurrentDirectory(TCHAR*);

	static bool getCurrentDirectory();

	static WIN32_FIND_DATA findFirstFile(LPCWSTR);

	static std::vector<WIN32_FIND_DATA> findNextFiles(LPCWSTR);

	/////////////////////////////////////////////////////////////////////////

	static void messageBox(const char*, const char* = "Error");

	static UINT winExec(const char* command);

	static HANDLE shellExecute(const wchar_t*, TCHAR*);

	static bool createProcess(TCHAR* path, STARTUPINFO&, PROCESS_INFORMATION&);
};