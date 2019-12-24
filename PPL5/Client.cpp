#include "Client.h"
#include "Code.h"
#include <cstdlib>

#define ORDER_COUNT 10

string generateOrder();

DWORD WINAPI ClientThreadProc(PVOID p) {
	Channel* chToClient = new Channel(L"ToClient");
	Channel* chToDeveloper = new Channel(L"ToDeveloper");
	Channel* chToManager = new Channel(L"ToManager");
	ofstream out = ofstream("log/client.log", ofstream::out);
	srand(0);
	bool flag = true;
	int orderN = 0;
	int orderF = 0;
	while (flag) {
		if (orderN < ORDER_COUNT) {
			string order = generateOrder();
			Message* newOrder = new Message(Code::Client, Code::STATE_NEW, order);
			chToDeveloper->put(newOrder);
			orderN++;
			out << "клиент сделал заказ: " << order << endl;
		}
		if (orderF == ORDER_COUNT) {
			out << "все заказы выполнены" << endl;
			flag = false;
			continue;
		}
		Message* msg = chToClient->get(5000);
		if (msg == nullptr) {
			out << "клиент не дождался" << endl;
			flag = false;
			continue;
		}
		switch (msg->sender) {
		case Code::Developer:
			switch (msg->code) {
			case Code::STATE_ACCEPT:
				out << "пришло подтверждение заказа: " << msg->data << endl;
				break;
			case Code::STATE_REJECT:
				out << "пришел отказ заказа: " << msg->data << endl;
				orderF++;
				break;
			}
			break;
		case Code::Manager:
			if (msg->code == Code::STATE_SUCCESS) {
				out << "клиент получил готовый заказ: " << msg->data << endl;
				orderF++;
				// todo check for correct result
			}
			break;
		}
		if (orderF < ORDER_COUNT) {
			out << "клиент спрашивает про готовые заказы " << endl;
			chToManager->put(new Message(Code::Client, Code::REQ_GET_RESULT, ""));
		}
		Sleep(100);
	}
	std::cout << "client exit" << endl;
	out << "клиент ушел" << endl;
	out.close();
	delete chToDeveloper;
	delete chToClient;
	delete chToManager;
	return 0;
}

string generateOrder() {
	char c = 'a' + (rand() % 26);
	int len = rand() % 60 + 1;
	char* adata = new char[len + 1];
	for (int j = 0; j < len; j++) {
		adata[j] = c;
	}
	adata[len] = 0;
	return string(adata);
}