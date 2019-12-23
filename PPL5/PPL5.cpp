#include "Channel.h"
#include "Client.h"
#include "Developer.h"

#include <iostream>

int main()
{
	HANDLE hClient;
	HANDLE hDeveloper;
	Client* client = new Client();
	Developer* developer = new Developer();
	client->start();
	developer->start();
	hClient = client->getThreadHandle();
	hDeveloper = developer->getThreadHandle();
	WaitForSingleObject(hClient, INFINITE);
	WaitForSingleObject(hDeveloper, INFINITE);
}
