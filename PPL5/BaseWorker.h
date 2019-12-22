#pragma once

#include <fstream>

class BaseWorker
{
public:
	virtual void start() = 0;
	virtual void stop() = 0;
};

