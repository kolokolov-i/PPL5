#pragma once
#include "BaseWorker.h"
#include "Channel.h"

#include <fstream>
#include <Windows.h>

using namespace std;

DWORD WINAPI ServerThreadProc(PVOID p);

class Server :
	public BaseWorker
{
public:
	Server() : BaseWorker() {
		out = ofstream("log/server.log", ofstream::out);
		out << "�������� ������" << endl;
	}

	virtual void start() {
		out << "�������� ������ ..." << endl;
		out.close();
		hThread = CreateThread(NULL, 0, ServerThreadProc, NULL, 0, NULL);
	}

};

