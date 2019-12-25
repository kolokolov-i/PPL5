#include "Client.h"
#include "Code.h"
#include <cstdlib>

#define ORDER_COUNT 10

string generateOrder();
bool checkResult(string data);

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
			out << "������ ������ �����: " << order << endl;
		}
		if (orderF == ORDER_COUNT) {
			out << "��� ������ ���������" << endl;
			flag = false;
			continue;
		}
		Message* msg = chToClient->get(10000);
		if (msg == nullptr) {
			out << "������ �� ��������" << endl;
			flag = false;
			continue;
		}
		switch (msg->sender) {
		case Code::Developer:
			switch (msg->code) {
			case Code::STATE_ACCEPT:
				out << "������ ������������� ������: " << msg->data << endl;
				break;
			case Code::STATE_REJECT:
				out << "������ ����� ������: " << msg->data << endl;
				orderF++;
				break;
			}
			break;
		case Code::Manager:
			if (msg->code == Code::STATE_SUCCESS) {
				out << "������ ������� ������� �����: " << msg->data << endl;
				if (checkResult(msg->data)) {
					out << "������ ������������" << endl;
					orderF++;
				}
				else {
					out << "������ ���������, ������" << endl;
					chToManager->put(new Message(Code::Client, Code::REQ_CLAIM, msg->data));
				}
			}
			break;
		}
		if (orderF < ORDER_COUNT) {
			out << "������ ���������� ��� ������� ������ " << endl;
			chToManager->put(new Message(Code::Client, Code::REQ_GET_RESULT, ""));
		}
		Sleep(100);
	}
	std::cout << "client exit" << endl;
	out << "������ ����" << endl;
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

bool checkResult(string data) {
	const char* adata = data.c_str();
	for (const char *c = adata; *c; c++) {
		int t = *c;
		if ((t < 65) || (t > 90)) {
			return false;
		}
	}
	return true;
}