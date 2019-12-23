#pragma once

#include "BaseWorker.h"
#include "Channel.h"

#include <fstream>
#include <Windows.h>
#include <cstdlib>

using namespace std;

DWORD WINAPI DeveloperThreadProc(PVOID p);

class Developer :
	public BaseWorker
{
public:
	Developer() : BaseWorker() {
		out = ofstream("log/developer.log", ofstream::out);
		out << "создан инженер" << endl;
	}

	virtual void start() {
		out << "запуск инженера ..." << endl;
		out.close();
		hThread = CreateThread(NULL, 0, DeveloperThreadProc, NULL, 0, NULL);
	}

};

