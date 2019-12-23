#include "Developer.h"
#include "Code.h"

DWORD WINAPI DeveloperThreadProc(PVOID p) {
	Channel* chToDeveloper = new Channel("ToDeveloper");
	Channel* chToClient = new Channel("ToClient");
	Channel* chToOperator = new Channel("ToOperator");
	ofstream out = ofstream("log/developer.log", ofstream::out);
	bool flag = true;
	while (flag) {
		Message* msg = chToDeveloper->get(5000);
		if (msg == nullptr) {
			flag = false;
			continue;
		}
		string order;
		order = msg->data;
		out << "������� ������� �����: " << order << endl;
		if (order.size() > 50) {
			out << "����� ��������, ������� ������� ������: " << order << endl;
			chToClient->put(new Message(Code::Developer, Code::CODE_REJECT, order));
		}
		else {
			out << "����� ������: " << order << endl;
			out << "������� ����������� ������" << endl;
			Sleep(10);
			chToClient->put(new Message(Code::Developer, Code::CODE_ACCEPT, order));
			chToOperator->put(new Message(Code::Developer, Code::CODE_DEVELOPED, order));
			out << "����� ������� ���������" << endl;
		}
	}
	out.close();
	return 0;
}