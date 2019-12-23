#pragma once

#include "Actor.h"

#include <string>
#include <cstring>

class Message
{
public:
	int sender;
	int code;
	std::string data;

	Message(Actor pSender, int pCode, std::string pData) {
		sender = pSender;
		code = pCode;
		data = pData;
	}
	Message(void* buffer) {
		char* p = static_cast<char*>(buffer);
		std::memcpy(&sender, p, sizeof(int));
		p += sizeof(int);
		std::memcpy(&code, p, sizeof(int));
		p += sizeof(int);
		int len;
		std::memcpy(&len, p, sizeof(int));
		p += sizeof(int);
		char* adata = new char[len+1];
		std::memcpy(adata, p, len + 1);
		data = std::string(adata);
		delete[] adata;
	}
	~Message() {}
	void writeTo(void* buffer) {
		char* p = static_cast<char*>(buffer);
		memcpy(p, &sender, sizeof(int)); p += sizeof(int);
		memcpy(p, &code, sizeof(int)); p += sizeof(int);
		int len = data.length();
		memcpy(p, &len, sizeof(int)); p += sizeof(int);
		strcpy(p, data.c_str());
	}
};

