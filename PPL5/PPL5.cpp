#include "Channel.h"
#include "Client.h"
#include "Developer.h"
#include "Manager.h"
#include "Server.h"
#include "Machine.h"
#include "Code.h"

#include <iostream>

int main()
{
	Client* client = new Client();
	Developer* developer = new Developer();
	Manager* manager = new Manager();
	Server* server = new Server();
	Machine* machine = new Machine();

	Channel* chToDeveloper = new Channel(L"ToDeveloper");
	Channel* chToClient = new Channel(L"ToClient");
	Channel* chToManager = new Channel(L"ToManager");
	Channel* chToServer = new Channel(L"ToServer");
	Channel* chToMachine = new Channel(L"ToMachine");

	client->start();
	developer->start();
	manager->start();
	server->start();
	machine->start();

	WaitForSingleObject(client->getThreadHandle(), INFINITE);
	WaitForSingleObject(developer->getThreadHandle(), INFINITE);
	WaitForSingleObject(manager->getThreadHandle(), INFINITE);
	WaitForSingleObject(server->getThreadHandle(), INFINITE);
	WaitForSingleObject(machine->getThreadHandle(), INFINITE);

	delete chToDeveloper;
	delete chToClient;
	delete chToManager;
	delete chToServer;
	delete chToMachine;
}
