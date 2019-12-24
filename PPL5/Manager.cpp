#include "Manager.h"
#include "Code.h"

#include <queue>

DWORD WINAPI ManagerThreadProc(PVOID p) {
	Channel* chToManager = new Channel(L"ToManager");
	Channel* chToClient = new Channel(L"ToClient");
	Channel* chToServer = new Channel(L"ToServer");
	ofstream out = ofstream("log/manager.log", ofstream::out);
	std::queue<Message*> storehouse;
	bool flag = true;
	while (flag) {
		Message* msg = chToManager->get(5000);
		if (msg == nullptr) {
			flag = false;
			out << "������ ��������� ���" << endl;
			continue;
		}
		switch (msg->sender) {
		case Code::Developer:
			out << "�������� ���������� ������� �� ������: " << msg->data << endl;
			chToServer->put(new Message(Code::Manager, Code::STATE_DEVELOPED, msg->data));
			break;
		case Code::Server:
			out << "�������� ����� ������� ����� �� �����: " << msg->data << endl;
			storehouse.push(new Message(Code::Manager, Code::STATE_SUCCESS, msg->data));
			break;
		case Code::Client:
			switch (msg->code) {
			case Code::REQ_GET_RESULT:
				if (!storehouse.empty()) {
					out << "�� ������ ����� ������� ������: " << storehouse.size() << endl;
					bool r = chToClient->putT(storehouse.front(), 10);
					if (r) {
						out << "�������� ����� ������� �����: " << storehouse.front()->data << endl;
						storehouse.pop();
					}
				}
				break;
			case Code::REQ_CLAIM:
				out << "������ ������, ������������: " << msg->data << endl;
				chToServer->put(new Message(Code::Manager, Code::STATE_DEVELOPED, msg->data));
				break;
			}
			break;
		}
		Sleep(10);
	}
	std::cout << "manager exit" << endl;
	out << "�������� ����" << endl;
	out.close();
	delete chToManager;
	delete chToClient;
	delete chToServer;
	return 0;
}