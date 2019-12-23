#include "Client.h"
#include "Code.h"

#define ORDER_COUNT 10

DWORD WINAPI ClientThreadProc(PVOID p) {
	Channel* chToDeveloper = new Channel("ToDeveloper");
	Channel* chToClient = new Channel("ToClient");
	ofstream out = ofstream("log/client.log", ofstream::out);
	srand(0);
	for (int i = 0; i < ORDER_COUNT; i++) {
		char c = 'a' + (rand() % 26);
		int len = rand() % 60 + 1;
		char* adata = new char[len+1];
		for (int j = 0; j < len; j++) {
			adata[j] = c;
		}
		adata[len] = 0;
		string order(adata);
		Message* newOrder = new Message(Code::Client, 0, order);
		chToDeveloper->put(newOrder);
		out << "клиент сделал заказ: " << order << endl;
		out << "клиент ждет ..." << endl;
		Message* msg = chToClient->get();
		switch (msg->sender) {
		case Code::Developer:
			switch (msg->code) {
			case Code::CODE_ACCEPT:
				out << "инженер принял заказ: " << msg->data << endl;
				break;
			case Code::CODE_REJECT:
				out << "инженер отклонил заказ: " << msg->data << endl;
				break;
			}
			break;
		case Code::Operator:
			if (msg->code == Code::CODE_SUCCESS) {
				out << "клиенту принесли готовый заказ: " << msg->data << endl;
				// todo check for correct result
			}
			break;
		}
		Sleep(100);
	}
	out.close();
	return 0;
}