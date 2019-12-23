#pragma once

#include "BaseWorker.h"
#include "Channel.h"

#include <fstream>
#include <Windows.h>
#include <cstdlib>

using namespace std;

DWORD WINAPI ClientThreadProc(PVOID p);

class Client :
	public BaseWorker
{
public:
	Client() : BaseWorker() {
		out = ofstream("log/client.log", ofstream::out);
		out << "������ ������" << endl;
	}

	virtual void start() {
		out << "������ ������� ..." << endl;
		out.close();
		hThread = CreateThread(NULL, 0, ClientThreadProc, NULL, 0, NULL);
	}

};
