#include "Channel.h"
#include "Client.h"
#include "Developer.h"

#include <iostream>

int main()
{
	Client* client = new Client();
	Developer* developer = new Developer();

	Channel* chToDeveloper = new Channel(L"ToDeveloper");
	Channel* chToClient = new Channel(L"ToClient");
	Channel* chToOperator = new Channel(L"ToOperator");

	client->start();
	developer->start();

	WaitForSingleObject(client->getThreadHandle(), INFINITE);
	WaitForSingleObject(developer->getThreadHandle(), INFINITE);

	delete chToDeveloper;
	delete chToClient;
	delete chToOperator;
}
