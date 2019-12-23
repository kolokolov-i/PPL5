#pragma once

#include "BaseWorker.h"
#include "Actor.h"
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
		out << "instance created" << endl;
	}

	virtual void start() {
		out << "starting" << endl;
		hThread = CreateThread(NULL, 0, ClientThreadProc, NULL, 0, NULL);
	}

};
