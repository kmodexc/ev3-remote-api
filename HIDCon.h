#pragma once
#include "types.h"
#include <thread>

class HIDCon
{
	int fd;
	bool debug;
	int mysec_senddelay;

	// receiving data loop
	CBuffer _int_recv_buffer;
	int _int_recv_msg_count;
	bool _int_continue_recv_loop;	
	std::thread _int_recv_thread;
	static void func_recv_loop(CBuffer* pbuffer, int* precv_buffer_msg_count, bool* pcont_loop, bool debug, int fd);

protected:
	bool Initialize(const char* path);
public:
	HIDCon(bool debug=false,int mysec_senddelay=0);
	~HIDCon();
	bool Initialize();
	bool Send(const CBuffer& send_buffer,CBuffer* rec_buffer = nullptr);
};