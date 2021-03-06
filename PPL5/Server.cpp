#include "Server.h"
#include "Code.h"

DWORD WINAPI ServerThreadProc(PVOID p) {
	Channel* chToServer = new Channel(L"ToServer");
	Channel* chToManager = new Channel(L"ToManager");
	Channel* chToMachine = new Channel(L"ToMachine");
	ofstream out = ofstream("log/server.log", ofstream::out);
	bool flag = true;
	while (flag) {
		Message* msg = chToServer->get(10000);
		if (msg == nullptr) {
			flag = false;
			out << "������ ����������" << endl;
			continue;
		}
		switch (msg->sender) {
		case Code::Manager:
			switch (msg->code) {
			case Code::STATE_DEVELOPED: {
				out << "������ ��������� �������: " << msg->data << endl;
				chToMachine->put(new Message(Code::Server, Code::STATE_DEVELOPED, msg->data));
			}break;
			case Code::MACHINE_OFF: {
				out << "������ ��������� ������" << endl;
				chToMachine->put(new Message(Code::Server, Code::MACHINE_OFF, ""));
				flag = false;
			}break;
			}
			break;
		case Code::Machine:
			out << "������ ��������� ��������� � ����������: " << msg->data << endl;
			chToManager->put(new Message(Code::Server, Code::STATE_SUCCESS, msg->data));
			break;
		}
		Sleep(1);
	}
	std::cout << "server exit" << endl;
	out << "������ ����������" << endl;
	out.close();
	delete chToServer;
	delete chToManager;
	delete chToMachine;
	return 0;
}