#pragma once
#include "types.h"

class HIDCon
{
	int fd;
public:
	HIDCon();
	~HIDCon();
	bool Initialize(const char* path);
	bool Initialize();
	bool Send(const CBuffer& send_buffer,CBuffer* rec_buffer = nullptr);
};