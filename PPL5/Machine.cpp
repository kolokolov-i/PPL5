#include "Server.h"
#include "Code.h"

DWORD WINAPI MachineThreadProc(PVOID p) {
	Channel* chToMachine = new Channel(L"ToMachine");
	Channel* chToServer = new Channel(L"ToServer");
	ofstream out = ofstream("log/machine.log", ofstream::out);
	bool flag = true;
	while (flag) {
		Message* msg = chToMachine->get(10000);
		if (msg == nullptr) {
			flag = false;
			out << "станок останавливается" << endl;
			continue;
		}
		if (msg->sender == Code::Server) {
			switch (msg->code) {
			case Code::STATE_DEVELOPED: {
				const char* src = msg->data.c_str();
				int len = msg->data.length();
				char* res = new char[len + 1];
				char dif = 'a' - 'A';
				for (int i = 0; src[i] != '\0'; i++) {
					res[i] = src[i] - dif;
				}
				res[len] = '\0';
		Sleep(10);
				chToServer->put(new Message(Code::Machine, Code::STATE_SUCCESS, std::string(res)));
				out << "деталь изготовлена: " << res << endl;
			}break;
			case Code::MACHINE_OFF: {
				out << "принят сигнал о выключении" << endl;
				flag = false;
			}break;
			}
		}
	}
	std::cout << "machine exit" << endl;
	out << "станок остановлен" << endl;
	out.close();
	delete chToMachine;
	delete chToServer;
	return 0;
}