#pragma once
#include "types.h"

class HIDCon
{
	int fd;
	bool debug;
public:
	HIDCon(bool debug=false);
	~HIDCon();
	bool Initialize(const char* path);
	bool Initialize();
	bool Send(const CBuffer& send_buffer,CBuffer* rec_buffer = nullptr);
};