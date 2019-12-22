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
		buffer = data;
		ReleaseSemaphore(semEmpty, 1, NULL);
	}
	Message* get() {
		Message* pMessage;
		WaitForSingleObject(semEmpty, INFINITE);
		pMessage = (Message*)buffer;
		ReleaseSemaphore(semFree, 1, NULL);
		return pMessage;
	}
	Channel(const char* name) {
		std::string chName = "ch" + std::string(name);
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
		if (fileMem != NULL) {
			buffer = MapViewOfFile(fileMem, FILE_MAP_ALL_ACCESS, 0, 0, 4096);
		}
		else {
			std::cerr << "error: FILE_MAP" << std::endl;
		}
	}
	~Channel() {}
};

