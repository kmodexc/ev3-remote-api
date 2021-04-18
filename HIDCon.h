#pragma once
#include "types.h"

class HIDCon
{
	int fd;
	bool debug;
	int mysec_senddelay;

protected:
	bool Initialize(const char* path);
public:
	HIDCon(bool debug=false,int mysec_senddelay=0);
	~HIDCon();
	bool Initialize();
	bool Send(const CBuffer& send_buffer,CBuffer* rec_buffer = nullptr);
};