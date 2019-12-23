#include "Server.h"
#include "Code.h"

DWORD WINAPI MachineThreadProc(PVOID p) {
	Channel* chToMachine = new Channel(L"ToMachine");
	Channel* chToServer = new Channel(L"ToServer");
	ofstream out = ofstream("log/machine.log", ofstream::out);
	bool flag = true;
	srand(100);
	while (flag) {
		Message* msg = chToMachine->get(5000);
		if (msg == nullptr) {
			flag = false;
			out << "станок остаавливается" << endl;
			continue;
		}
		if (msg->sender == Code::Server) {
			const char* src = msg->data.c_str();
			int len = msg->data.length();
			char* res = new char[len+1];
			char dif = 'a' - 'A';
			for (int i = 0; src[i] != '\0'; i++) {
				int v = rand() % 100;
				res[i] = src[i] + (v > 90 ? 0 : 32);
			}
			res[len] = '\0';
			chToServer->put(new Message(Code::Machine, Code::STATE_SUCCESS, std::string(res)));
			out << "заказ выполнен" << endl;
		}
		Sleep(10);
	}
	out << "станок остановлен" << endl;
	out.close();
	delete chToMachine;
	delete chToServer;
	return 0;
}