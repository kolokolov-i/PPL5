#pragma once

#include "Message.h"

#include <Windows.h>
#include <string>
#include <iostream>

class Channel
{
private:
	HANDLE semFree;
	HANDLE semEmpty;
	HANDLE fileMem;
	void* buffer;
public:
	void put(Message* data) {
		WaitForSingleObject(semFree, INFINITE);
		data->writeTo(buffer);
		ReleaseSemaphore(semEmpty, 1, NULL);
	}
	Message* get() {
		Message* pMessage;
		WaitForSingleObject(semEmpty, INFINITE);
		pMessage = new Message(buffer);
		ReleaseSemaphore(semFree, 1, NULL);
		return pMessage;
	}
	Message* get(int timeout) {
		Message* pMessage;
		BOOL r = WaitForSingleObject(semEmpty, timeout);
		pMessage = new Message(buffer);
		ReleaseSemaphore(semFree, 1, NULL);
		return r == FALSE ? pMessage : nullptr;
	}
	Channel(std::string name) {
		std::string chName = "ch" + name;
		std::string semFName = chName + "semF";
		std::string semEName = chName + "semE";
		std::string fileName = chName + "file";
		semFree = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, (LPCWSTR)semFName.c_str());
		if (semFree == NULL) {
			semFree = CreateSemaphore(NULL, 1, 1, (LPCWSTR)semFName.c_str());
		}
		semEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, (LPCWSTR)semEName.c_str());
		if (semEmpty == NULL) {
			semEmpty = CreateSemaphore(NULL, 1, 1, (LPCWSTR)semEName.c_str());
		}
		fileMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, (LPCWSTR)fileName.c_str());
		if (fileMem == NULL) {
			fileMem = CreateFileMapping(
				INVALID_HANDLE_VALUE,
				NULL,
				PAGE_READWRITE,
				0, 4096,
				(LPCWSTR)fileName.c_str());
		}
		if (fileMem != NULL) {
			buffer = MapViewOfFile(fileMem, FILE_MAP_ALL_ACCESS, 0, 0, 4096);
		}
		else {
			DWORD debugCode = GetLastError();
			std::cerr << "error: FILE_MAP" << std::endl;
			buffer = nullptr;
		}
	}
	~Channel() {}
};

