#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>

#include <winbase.h>



class WindowsAPI {
public:
	static void errorTextOutput() {
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

	static HANDLE createFile(TCHAR* path) {
		return CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	static HANDLE getFile(TCHAR* path) {
		return CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	static bool readFile(TCHAR* path) {
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

	static bool writeFile(TCHAR* path, char* text) {
		HANDLE handle = getFile(path);
		if (handle != INVALID_HANDLE_VALUE) {
			DWORD bytesToWrite = std::strlen(text);
			DWORD writtenBytes = 0;
			return WriteFile(handle, text, bytesToWrite, &writtenBytes, NULL);
		}
		return false;
	}

	static bool copy(TCHAR* from, TCHAR* to) {
		return CopyFile(from, to, FALSE);
	}

	static bool readWrite(TCHAR* from, TCHAR* to) {
		HANDLE h1 = CreateFile(from, GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		HANDLE h2 = CreateFile(to, GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (h1 && h2) {
			DWORD z1, z2;
			char a;
			bool read = ReadFile(h1, &a, 1, &z2, NULL);
			while (read && z2 != 0) {
				WriteFile(h2, &a, z2, &z1, NULL);
				read = ReadFile(h1, &a, 1, &z2, NULL);
			}
			return true;
		}
		return false;
	}

	static bool createDirectory(TCHAR* path) {
		return CreateDirectory(path, NULL);
	}

	static bool setCurrentDirectory(TCHAR* path) {
		return SetCurrentDirectory(path);
	}

	static bool getCurrentDirectory() {
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

	static WIN32_FIND_DATA findFirstFile(LPCWSTR extension) {
		WIN32_FIND_DATA fileData;
		if (FindFirstFile(extension, &fileData) == INVALID_HANDLE_VALUE) {
			std::cout << "Something went wrong\n";
		}
		return fileData;
	}

	static std::vector<WIN32_FIND_DATA> findNextFiles(LPCWSTR extension) {
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
};


//argv[1]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\CreateFile.txt"(0)(empty)
//argv[2]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\TempFile.txt"(1)(empty)
//argv[3]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\ReadFile.txt"(1)(text)
//argv[4]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\WriteFile.txt"(1)(empty)
//argv[5]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\FileToCopy.txt"(1)(text)
//argv[6]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\CopiedFile.txt"(0)(empty)
//argv[7]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\ReadFrom.txt"(1)(text)
//argv[8]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\WriteTo.txt"(1)(empty)

//argv[9]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\CreateDirectory"(0)(empty)
//argv[10]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\WorkingDirectory"(1)(files(any extensions))





int _tmain(int argc, TCHAR* argv[]) {

	std::cout << "Count of arguments:  " << argc << "\n///////////////////////////" << std::endl;

	/*if (WindowsAPI::createFile(argv[1]) != INVALID_HANDLE_VALUE) {
		std::cout << "File was created\n\n";
	}
	else {
		std::cout << "File wasn't created\n\n";
	}

	if (WindowsAPI::getFile(argv[2])) {
		std::cout << "File was got\n\n";
	}
	else {
		std::cout << "File wasn't got\n\n";
	}

	if (WindowsAPI::readFile(argv[3])) {
		std::cout << "Data from file was read\n\n";
	}
	else {
		std::cout << "Something went wrong\n\n";
	}

	char text[] = "Writes data to the specified file or input/output (I/O) device.";
	if (WindowsAPI::writeFile(argv[4], text)) {
		std::cout << "Text was written in file\n\n";
	}
	else {
		std::cout << "Something went wrong\n\n";
	}

	if (WindowsAPI::copy(argv[5], argv[6])) {
		std::cout << "File was copied\n\n";
	}
	else {
		std::cout << "File was't copied\n\n";
	}


	if (WindowsAPI::readWrite(argv[7], argv[8])) {
		std::cout << "Text was read and written\n\n";
	}
	else {
		std::cout << "Something went wrong\n\n";
	}*/




	if (WindowsAPI::createDirectory(argv[9])) {
		std::cout << "Directory was created\n\n";
	}
	else {
		std::cout << "Directory was't created\n\n";
	}

	if (WindowsAPI::setCurrentDirectory(argv[10])) {
		std::cout << "Directory was set\n\n";
	}
	else {
		std::cout << "Directory wasn't set\n\n";
	}


	if (!WindowsAPI::getCurrentDirectory()) {
		std::cout << "Something went wrong\n\n";
	}
	else {
		std::cout << "Everythig was correct\n\n";
	}

	LPCWSTR extension = L"*.txt";
	std::wcout << "First file with extension " << extension<<":  \n";
	std::wcout << WindowsAPI::findFirstFile(extension).cFileName << "\n\n";


	std::wcout << "All files with extension " << extension << ":  \n";
	std::vector< WIN32_FIND_DATA> files = WindowsAPI::findNextFiles(extension);
	for (int i = 0; i < files.size(); ++i) {
		std::wcout << files[i].cFileName << std::endl;
	}
	return 0;
}