#include "Manager.h"
#include "Code.h"

DWORD WINAPI ManagerThreadProc(PVOID p) {
	Channel* chToManager = new Channel(L"ToManager");
	Channel* chToClient = new Channel(L"ToClient");
	Channel* chToServer = new Channel(L"ToServer");
	Channel* chForClaim = new Channel(L"ForClaim");
	ofstream out = ofstream("log/manager.log", ofstream::out);
	bool flag = true;
	while (flag) {
		Message* msg = chToManager->get(5000);
		if (msg == nullptr) {
			flag = false;
			out << "менеджер не дождался" << endl;
			continue;
		}
		switch (msg->sender) {
		case Code::Developer:
			out << "менеджер отправляет задание на сервер: " << msg->data << endl;
			chToServer->put(new Message(Code::Manager, Code::STATE_DEVELOPED, msg->data));
			break;
		case Code::Server:
			out << "менеджер отдает готовый заказ клиенту: " << msg->data << endl;
			chToClient->put(new Message(Code::Manager, Code::STATE_SUCCESS, msg->data));
			break;
		}
		Sleep(10);
		msg = chForClaim->get(100);
		if (msg != nullptr) {
			if (msg->code == Code::STATE_CLAIM) {
				out << "пришла жалоба, переделывать: " << msg->data << endl;
				chToServer->put(new Message(Code::Manager, Code::STATE_DEVELOPED, msg->data));
			}
		}

	}
	out << "менеджер ушел" << endl;
	out.close();
	delete chToManager;
	delete chToClient;
	delete chToServer;
	delete chForClaim;
	return 0;
}