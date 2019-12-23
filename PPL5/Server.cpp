#include "Server.h"
#include "Code.h"

DWORD WINAPI ServerThreadProc(PVOID p) {
	Channel* chToServer = new Channel(L"ToServer");
	Channel* chToManager = new Channel(L"ToManager");
	Channel* chToMachine = new Channel(L"ToMachine");
	ofstream out = ofstream("log/server.log", ofstream::out);
	bool flag = true;
	while (flag) {
		Message* msg = chToServer->get(5000);
		if (msg == nullptr) {
			flag = false;
			out << "сервер отключили" << endl;
			continue;
		}
		switch (msg->sender) {
		case Code::Manager:
			out << "сервер принимает задание: " << msg->data << endl;
			//chToMachine->put(new Message(Code::Server, Code::STATE_DEVELOPED, msg->data));
			break;
		case Code::Machine:
			out << "сервер оповещает менеджера о готовности: " << msg->data << endl;
			chToManager->put(new Message(Code::Server, Code::STATE_SUCCESS, msg->data));
			break;
		}
		Sleep(1);
	}
	out << "сервер отключили" << endl;
	out.close();
	delete chToServer;
	delete chToManager;
	delete chToMachine;
	return 0;
}