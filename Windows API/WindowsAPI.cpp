#include "WindowsAPI.h"

void WindowsAPI::errorTextOutput() {
	LPVOID ipMsBuf;
	DWORD dw = GetLastError();
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&ipMsBuf,
		0,
		NULL
	);
	_tprintf(_T("Error is: %d - %s"), dw, (LPTSTR)ipMsBuf);
	LocalFree(ipMsBuf);
}

HANDLE WindowsAPI::createFile(TCHAR* path) {
	return CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

HANDLE WindowsAPI::getFile(TCHAR* path) {
	return CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

bool WindowsAPI::readFile(TCHAR* path) {
	HANDLE handle = getFile(path);

	if (handle == INVALID_HANDLE_VALUE) {
		return false;
	}
	DWORD z1;
	char a;
	bool read = ReadFile(handle, &a, 1, &z1, NULL);

	std::cout << "Data from file:  ";
	while (read && z1 != 0) {
		std::cout << a;
		read = ReadFile(handle, &a, 1, &z1, NULL);
	}
	return true;
}

bool WindowsAPI::writeFile(TCHAR* path, char* text) {
	HANDLE handle = getFile(path);
	if (handle != INVALID_HANDLE_VALUE) {
		DWORD bytesToWrite = std::strlen(text);
		DWORD writtenBytes = 0;
		return WriteFile(handle, text, bytesToWrite, &writtenBytes, NULL);
	}
	return false;
}

bool WindowsAPI::copy(TCHAR* from, TCHAR* to) {
	return CopyFile(from, to, FALSE);
}

bool WindowsAPI::readWrite(TCHAR* from, TCHAR* to) {
	HANDLE h1 = CreateFile(from, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE h2 = CreateFile(to, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h1 && h2) {
		DWORD z1, z2;
		char a;
		bool read = ReadFile(h1, &a, 1, &z2, NULL);
		while (read && z2 != 0) {
			std::cout << a << " ";
			WriteFile(h2, &a, z2, &z1, NULL);
			read = ReadFile(h1, &a, 1, &z2, NULL);
		}
		std::cout << std::endl;
		return true;
	}
	return false;
}

bool WindowsAPI::createDirectory(TCHAR* path) {
	return CreateDirectory(path, NULL);
}

bool WindowsAPI::setCurrentDirectory(TCHAR* path) {
	return SetCurrentDirectory(path);
}

bool WindowsAPI::getCurrentDirectory() {
	TCHAR path[MAX_PATH];
	DWORD length = MAX_PATH;

	bool got = GetCurrentDirectory(length, (LPWSTR)path);
	if (!got) {
		return false;
	}
	else {
		std::cout << "Directory path is:  ";
		for (int i = 0; path[i] != '\0'; i++) {
			std::cout << char(path[i]);
		}
		std::cout << std::endl;
		return true;
	}
}

WIN32_FIND_DATA WindowsAPI::findFirstFile(LPCWSTR extension) {
	WIN32_FIND_DATA fileData;
	if (FindFirstFile(extension, &fileData) == INVALID_HANDLE_VALUE) {
		std::cout << "Something went wrong\n";
	}
	return fileData;
}

std::vector<WIN32_FIND_DATA> WindowsAPI::findNextFiles(LPCWSTR extension) {
	WIN32_FIND_DATA fileData;
	HANDLE handler = FindFirstFile(extension, &fileData);
	std::wcout << fileData.cFileName << std::endl;
	std::vector< WIN32_FIND_DATA> files;
	while (FindNextFile(handler, &fileData))
	{
		files.push_back(fileData);
	}
	return files;
}


////////////////////////////////////////

void WindowsAPI::messageBox(const char* innerText, const char* captionText) {

	wchar_t* inner = new wchar_t[strlen(innerText) + 1];
	wchar_t* caption = new wchar_t[strlen(captionText) + 1];

	size_t innterSize = strlen(innerText);
	size_t captionSize = strlen(captionText);

	size_t outSize;
	mbstowcs_s(&outSize, inner, innterSize + 1, innerText, innterSize);
	outSize = 0;
	mbstowcs_s(&outSize, caption, captionSize + 1, captionText, captionSize);


	LPWSTR _inner = inner;
	LPWSTR _caption = caption;
	MessageBox(NULL, _inner, _caption, MB_OK);
}

UINT WindowsAPI::winExec(const char* command) {
	return WinExec(command, SW_SHOW);
}

HANDLE WindowsAPI::shellExecute(const wchar_t* command, TCHAR* path) {
	return ShellExecute(NULL, command, path, NULL, NULL, SW_SHOW);
}

bool WindowsAPI::createProcess(TCHAR* path, STARTUPINFO& si, PROCESS_INFORMATION& pi) {
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	return CreateProcess(path, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
}