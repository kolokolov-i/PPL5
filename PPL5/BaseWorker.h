#pragma once

#include <fstream>
#include <Windows.h>

class BaseWorker
{
protected:
	std::ofstream out;
	HANDLE hThread;

public:
	virtual void start() = 0;
	//virtual void stop() = 0;

	HANDLE getThreadHandle() {
		return hThread;
	}
};

