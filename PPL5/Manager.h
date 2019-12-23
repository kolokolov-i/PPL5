#pragma once
#include "BaseWorker.h"
#include "Channel.h"

#include <fstream>
#include <Windows.h>

using namespace std;

DWORD WINAPI ManagerThreadProc(PVOID p);

class Manager :
	public BaseWorker
{
public:
	Manager() : BaseWorker() {
		out = ofstream("log/manager.log", ofstream::out);
		out << "������ ��������" << endl;
	}

	virtual void start() {
		out << "������ ��������� ..." << endl;
		out.close();
		hThread = CreateThread(NULL, 0, ManagerThreadProc, NULL, 0, NULL);
	}

};

