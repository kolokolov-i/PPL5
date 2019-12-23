#include "Client.h"
#include "Code.h"
#include <cstdlib>

#define ORDER_COUNT 10

string generateOrder();

DWORD WINAPI ClientThreadProc(PVOID p) {
	Channel* chToClient = new Channel(L"ToClient");
	Channel* chToDeveloper = new Channel(L"ToDeveloper");
	ofstream out = ofstream("log/client.log", ofstream::out);
	srand(0);
	for (int i = 0; i < ORDER_COUNT; i++) {
		string order = generateOrder();
		Message* newOrder = new Message(Code::Client, Code::STATE_NEW, order);
		chToDeveloper->put(newOrder);
		out << "клиент сделал заказ: " << order << endl;
		out << "клиент ждет ..." << endl;
		Message* msg = chToClient->get(15000);
		if (msg == nullptr) {
			out << "клиент не дождался" << endl;
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
				break;
			}
			break;
		case Code::Manager:
			if (msg->code == Code::STATE_SUCCESS) {
				out << "клиент получил готовый заказ: " << msg->data << endl;
				// todo check for correct result
			}
			break;
		}
		Sleep(100);
	}
	out << "клиент ушел" << endl;
	out.close();
	delete chToDeveloper;
	delete chToClient;
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