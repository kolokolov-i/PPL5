#pragma once
#include "BaseWorker.h"
#include "Channel.h"

#include <fstream>
#include <Windows.h>

using namespace std;

DWORD WINAPI MachineThreadProc(PVOID p);

class Machine :
	public BaseWorker
{
public:
	Machine() : BaseWorker() {
		out = ofstream("log/machine.log", ofstream::out);
		out << "�������� ������" << endl;
	}

	virtual void start() {
		out << "�������� ������ ..." << endl;
		out.close();
		hThread = CreateThread(NULL, 0, MachineThreadProc, NULL, 0, NULL);
	}
};