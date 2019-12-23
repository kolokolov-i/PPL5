#include "Client.h"

DWORD WINAPI ClientThreadProc(PVOID p) {
	Channel* chToDev = new Channel("ToDeveloper");
	ofstream out = ofstream("log/client.log", ofstream::out);
	string order;
	order = "aaaaaaaaaa";
	Message* newOrder = new Message(ActorClient, 0, order);
	chToDev->put(newOrder);
	out << "order was sent to developer: " + order << endl;
	return 0;
	//srand(0);
	//for (int i = 0; i < 10; i++) {
	//	int len = rand() % 60 + 1;
	//	Message* newOrder = new Message(Actor::Client, 0, );
	//}
}