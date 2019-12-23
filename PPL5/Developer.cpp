#include "Developer.h"
#include "Code.h"

DWORD WINAPI DeveloperThreadProc(PVOID p) {
	Channel* chToDeveloper = new Channel(L"ToDeveloper");
	Channel* chToClient = new Channel(L"ToClient");
	Channel* chToManager = new Channel(L"ToManager");
	ofstream out = ofstream("log/developer.log", ofstream::out);
	bool flag = true;
	while (flag) {
		Message* msg = chToDeveloper->get(5000);
		if (msg == nullptr) {
			flag = false;
			out << "инженер не дождался" << endl;
			continue;
		}
		string order;
		order = msg->data;
		out << "инженер получил заказ: " << order << endl;
		if (order.size() > 40) {
			out << "заказ отклонен, слишком большая деталь: " << order << endl;
			chToClient->put(new Message(Code::Developer, Code::STATE_REJECT, order));
		}
		else {
			out << "заказ принят: " << order << endl;
			out << "инженер проектирует деталь" << endl;
			Sleep(10);
			chToClient->put(new Message(Code::Developer, Code::STATE_ACCEPT, order));
			chToManager->put(new Message(Code::Developer, Code::STATE_DEVELOPED, order));
			out << "заказ передан менеджеру" << endl;
		}
	}
	out << "инженер ушел" << endl;
	out.close();
	delete chToDeveloper;
	delete chToClient;
	delete chToManager;
	return 0;
}