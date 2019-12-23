#include "Channel.h"
#include "Client.h"
#include "Developer.h"

#include <iostream>

int main()
{
	Client* client = new Client();
	Developer* developer = new Developer();

	Channel* chToDeveloper = new Channel("ToDeveloper");
	Channel* chToClient = new Channel("ToClient");
	Channel* chToOperator = new Channel("ToOperator");

	client->start();
	developer->start();

	WaitForSingleObject(client->getThreadHandle(), INFINITE);
	WaitForSingleObject(developer->getThreadHandle(), INFINITE);
}
