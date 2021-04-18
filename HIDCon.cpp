#include "HIDCon.h"

/*
 * Hidraw Userspace Example
 *
 * Copyright (c) 2010 Alan Ott <alan@signal11.us>
 * Copyright (c) 2010 Signal 11 Software
 *
 * The code may be used by anyone for any purpose,
 * and can serve as a starting point for developing
 * applications using hidraw.
 */
/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>
/*
 * Ugly hack to work around failing compilation on systems that don't
 * yet populate new version of hidraw.h to userspace.
 */
#ifndef HIDIOCSFEATURE
#warning Please have your distro update the userspace kernel headers
#define HIDIOCSFEATURE(len) _IOC(_IOC_WRITE | _IOC_READ, 'H', 0x06, len)
#define HIDIOCGFEATURE(len) _IOC(_IOC_WRITE | _IOC_READ, 'H', 0x07, len)
#endif
/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <poll.h>

#include <filesystem>

#include <chrono>
#include <iostream>

#include <thread>

using std::cout;
using std::endl;

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

namespace fs = std::filesystem;

using namespace std::this_thread;

using std::min;

const char *
bus_str(int bus)
{
	switch (bus)
	{
	case BUS_USB:
		return "USB";
		break;
	case BUS_HIL:
		return "HIL";
		break;
	case BUS_BLUETOOTH:
		return "Bluetooth";
		break;
	case BUS_VIRTUAL:
		return "Virtual";
		break;
	default:
		return "Other";
		break;
	}
}

HIDCon::HIDCon(bool debug, int mysec_senddelay) : debug(debug),
												  fd(-1),
												  mysec_senddelay(mysec_senddelay)
{
}

HIDCon::~HIDCon()
{
	if (fd >= 0)
		close(fd);
}

bool HIDCon::Initialize(const char *path)
{
	if (path == nullptr)
	{
		return Initialize();
	}

	int i, res, desc_size = 0;
	char buf[256];
	struct hidraw_report_descriptor rpt_desc;
	struct hidraw_devinfo info;
	/* Open the Device with non-blocking reads. In real life,
	   don't use a hard coded path; use libudev instead. */
	fd = open(path, O_RDWR /*| O_NONBLOCK  */);
	if (fd < 0)
	{
		perror("Unable to open device");
		return false;
	}
	memset(&rpt_desc, 0x0, sizeof(rpt_desc));
	memset(&info, 0x0, sizeof(info));
	memset(buf, 0x0, sizeof(buf));
	/* Get Report Descriptor Size */
	res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
	if (res < 0)
	{
		perror("HIDIOCGRDESCSIZE");
		return false;
	}
	else if (debug)
		printf("Report Descriptor Size: %d\n", desc_size);
	/* Get Report Descriptor */
	rpt_desc.size = desc_size;
	res = ioctl(fd, HIDIOCGRDESC, &rpt_desc);
	if (res < 0)
	{
		perror("HIDIOCGRDESC");
		return false;
	}
	else if (debug)
	{
		printf("Report Descriptor:\n");
		for (i = 0; i < rpt_desc.size; i++)
			printf("%hhx ", rpt_desc.value[i]);
		puts("\n");
	}
	/* Get Raw Name */
	res = ioctl(fd, HIDIOCGRAWNAME(256), buf);
	if (res < 0)
	{
		perror("HIDIOCGRAWNAME");
		return false;
	}
	else if (debug)
		printf("Raw Name: %s\n", buf);
	/* Get Physical Location */
	res = ioctl(fd, HIDIOCGRAWPHYS(256), buf);
	if (res < 0)
	{
		perror("HIDIOCGRAWPHYS");
		return false;
	}
	else if (debug)
		printf("Raw Phys: %s\n", buf);
	/* Get Raw Info */
	res = ioctl(fd, HIDIOCGRAWINFO, &info);
	if (res < 0)
	{
		perror("HIDIOCGRAWINFO");
		return false;
	}
	else if (debug)
	{
		printf("Raw Info:\n");
		printf("\tbustype: %d (%s)\n",
			   info.bustype, bus_str(info.bustype));
		printf("\tvendor: 0x%04hx\n", info.vendor);
		printf("\tproduct: 0x%04hx\n", info.product);
	}

	if (info.vendor != 0x0694 || info.product != 0x0005)
	{
		printf("Wrong Vendor/Product. Exiting.\n");
		return false;
	}
	return true;
}
bool HIDCon::Send(const CBuffer &buffer, CBuffer *presp)
{
	if(mysec_senddelay > 0)
		sleep_for(microseconds(mysec_senddelay));

	auto res = write(fd, buffer.data(), buffer.size());
	if (res < 0)
	{
		printf("Error: %d\n", errno);
		perror("write");
		return false;
	}
	else if (debug)
	{
		printf("write() wrote %d bytes\n", (int32_t)res);
		for (int cnt = 0; cnt < buffer.size(); cnt++)
			printf("%02x ", buffer[cnt]);
		printf("\n");
	}

	if (presp != nullptr)
	{

		int ret;
		struct pollfd fds;

		fds.fd = fd;
		fds.events = POLLIN;
		fds.revents = 0;
		const int timeout = 1000;
		ret = poll(&fds, 1, timeout);
		if (ret == 0)
		{
			/* Timeout */
			printf("read timeout %d\n", (uint32_t)timeout);
			return false;
		}
		if (ret == -1)
		{
			/* Error */
			perror("POLL: ");
			return false;
		}

		uint8_t buf[10];

		/* Get a report from the device */
		res = read(fd, buf, sizeof(buf));
		if (res < 0)
		{
			perror("read");
		}
		else if (debug)
		{
			printf("read-size: read() read %d bytes:\n\t", (int32_t)res);
			for (int i = 0; i < sizeof(buf); i++)
				printf("%hhx ", buf[i]);
			puts("\n");
		}

		size_t msg_size = buf[0] + (buf[1] << 8);

		presp->resize(msg_size + 2);

		memcpy(presp->data(), buf, min(msg_size + 2, sizeof(buf)));
	}

	return true;
}

bool HIDCon::Initialize()
{
	std::string path = "/dev";
	for (const auto &entry : fs::directory_iterator(path))
	{
		std::string fn(entry.path().filename().c_str());
		if (fn.find("hidraw") != std::string::npos)
		{
			if (Initialize(entry.path().c_str()))
				return true;
		}
	}
	printf("no hid device found wich initialized correctly\n");
	return false;
}
