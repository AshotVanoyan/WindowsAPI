#include "WindowsAPI.h"


//argv[11]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\filesForProcessing\shellExecute.txt"(1)(not empty)
//argv[12]="C:\Program Files (x86)\Google\Chrome\Application\chrome.exe"(app)


int _tmain(int argc, TCHAR* argv[]) {
	const char* command = "Notepad C:\\Users\\User\\Desktop\\Operating Systems\\WindowsAPI\\filesForProcessing\\openByNotepad.txt";
	if (WindowsAPI::winExec(command) < 32) {
		WindowsAPI::messageBox("something went wrong","Fail");
	}
	else {
		WindowsAPI::messageBox("Press OK button!!!", "Success");
	}


	if (WindowsAPI::shellExecute(L"open", argv[11]) < (HANDLE)32) {
		WindowsAPI::messageBox("something went wrong", "Fail");
	}
	else {
		WindowsAPI::messageBox("Press OK button!!!", "Success");
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	if (!WindowsAPI::createProcess(argv[12],si,pi)) {
		std::cout << "Creating process was failed" << std::endl;
		WindowsAPI::errorTextOutput();
	}
	else
	{
		std::cout << "Creating process success" << std::endl;
		std::cout << "Porcess ID: " << pi.dwProcessId << std::endl;
		std::cout << "Thread ID: " << pi.dwThreadId << std::endl;

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return 0;
}





namespace main1 {
	/*working with files*/
	//argv[1]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\CreateFile.txt"(0)(empty)
	//argv[2]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\TempFile.txt"(1)(empty)
	//argv[3]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\ReadFile.txt"(1)(text)
	//argv[4]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\WriteFile.txt"(1)(empty)
	//argv[5]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\FileToCopy.txt"(1)(text)
	//argv[6]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\CopiedFile.txt"(0)(empty)
	//argv[7]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\ReadFrom.txt"(1)(text)
	//argv[8]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\WriteTo.txt"(1)(empty)

	/*working with directories*/
	//argv[9]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\CreateDirectory"(0)(empty)
	//argv[10]="C:\Users\User\Desktop\Operating Systems\WindowsAPI\FilesAndDirectories\WorkingDirectory"(1)(files(any extensions))

	/*main*/
	/*std::cout << "Count of arguments:  " << argc << "\n///////////////////////////" << std::endl;

	if (WindowsAPI::createFile(argv[1]) != INVALID_HANDLE_VALUE) {
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
	}

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
	std::wcout << "First file with extension " << extension << ":  \n";
	std::wcout << WindowsAPI::findFirstFile(extension).cFileName << "\n\n";


	std::wcout << "All files with extension " << extension << ":  \n";
	std::vector< WIN32_FIND_DATA> files = WindowsAPI::findNextFiles(extension);
	for (int i = 0; i < files.size(); ++i) {
		std::wcout << files[i].cFileName << std::endl;
	}*/
}


