#pragma once
#include "BaseWorker.h"
#include <fstream>

using namespace std;

class Customer :
	public BaseWorker
{
private:
	ofstream out;

public:
	Customer() : BaseWorker() {
		out = ofstream("log/customer.log", ofstream::out);
		out << "instance created" << endl;
	}

	virtual void start() {
		out << "start" << endl;

	}

	virtual void stop() {
		out << "stop" << endl;
		out.close();
	}
};

