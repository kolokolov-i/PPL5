#include "Developer.h"

DWORD WINAPI DeveloperThreadProc(PVOID p) {
	Channel* chToDev = new Channel("ToDeveloper");
	ofstream out = ofstream("log/developer.log", ofstream::out);
	Message* msg = chToDev->get();
	string order;
	order = msg->data;
	out << "developer recieved order: " + order << endl;
	return 0;
}