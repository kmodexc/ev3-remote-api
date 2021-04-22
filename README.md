# Lego EV3 Linux C++ API

## Info

### General
With this API you can control your LEGO EV3 connected with USB from your Linux PC. Its main purpose is to provide a fast interface for controlling the LEGO EV3.

### LEGO EV3 Communication
The LEGO EV3 will create a HID file in /dev/. You can access this with the [HIDRAW API](https://www.kernel.org/doc/html/latest/hid/hidraw.html) by the Linux Kernal.
Lego has developed its own Protokoll. Some of it is explained in the EV3 Communication Developer Kit which can be downloaded [here](https://education.lego.com/de-de/product-resources/mindstorms-ev3/downloads/developer-kits). Definitions for commands and other protokoll related things can be downloaded from the original [EV3 sourcecode](https://github.com/mindboards/ev3sources). The availible byte codes can be seen [here](http://ev3.fantastic.computer/doxygen/index.html) as well as the details for the communication.
## Install
### General
To run this without sudo use 
```KERNEL=="hidraw*", SUBSYSTEM=="hidraw", MODE="0664", GROUP="plugdev"```
and place it in `/etc/udev/rules/99-hidraw-permissions.rules`.
Its needed to access the hidraw interface.
### Easy Interface
The library provides the an easy interface with `Brick.h`. Just link the library and start like:
```
#include "Brick.h"
int main(void)
{
	Brick brick();
	
	// initialize
	if (!brick.Initialize())
		return 1;

	// read sensor val
	int val = brick.getSensorVal(Input::Port1);

	// set power to +99%
	brick.setMotorPower(Output::A, 99);

	// stop motor
	brick.setMotorPower(Output::A, 0);

	return 0;
}
```
### More complicated Interface
If you want to handle the communication yourself you can use the class `Command` to create the an arbitrary [command](http://ev3.fantastic.computer/doxygen/bytecodes.html) and send it with the  `HIDCon` class. 
This would look like here:
```
// message counter should increment each message
int msg_cnt = 0;
// There are direct commands and system commands. Both can and can not have a reply
Command c1(DIRECT_COMMAND_REPLY, msg_cnt++);
addOpCode(opINPUT_DEVICE);
addParameter((uint8_t)GET_RAW);
addParameter((uint8_t)0);
addParameter(port);
// the return value will be stored in the global var
addGlobalVar(0);	// global var with index 0
// If the command has a reply it will be stored in binary here.
CBuffer reply;
con.Send(com.toBytes(),&reply)
// With this method you have to decode it yourself.
// Depending on the size, the global variables will be on the reply starting with byte 5
return reply[5];
```
