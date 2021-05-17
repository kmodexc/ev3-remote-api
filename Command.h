#pragma once
#include <vector>
#include <stdint.h>
#include "types.h"

#include "bytecode.h"
#include "c_com.h"

class Command{
	CBuffer data;
	uint16_t msg_id;
	uint8_t type;
protected:
	Command();
public:
	Command(uint8_t type, uint16_t msg_id, uint8_t cnt_glob, uint8_t cnt_loc);
	~Command();

	// internal stuff
	void addOpCode(uint8_t code);
	void addParameter(bool b);
	void addParameter(uint8_t b);
	void addParameter(int8_t b) { addParameter((uint8_t)b); }
	void addParameter(uint32_t b);
	void addParameter(int32_t b) { addParameter((uint32_t)b); }
	void addGlobalVar(uint8_t id);
	void addHandle(uint16_t id);
	void addLocalVar(uint8_t id);

	
	// commands
	void startMotor(uint8_t port);
	void stopMotor(uint8_t port);
	void turnMotorAtPowerForTime(uint8_t ports, int8_t power, uint32_t msRampUp, uint32_t msConstant, uint32_t msRampDown, bool brake);
	void turnMotorAtSpeedForAngle(uint8_t ports, int8_t speed, uint32_t stepRampUp, uint32_t stepConstant, uint32_t stepRampDown, bool brake);
	void startMotorPower(uint8_t port, int8_t power);
	void readSensor(uint8_t port);
	void arrayCreate8(uint8_t lv_id,uint32_t length);
	void arrayWrite(uint8_t lv_id, uint32_t index, uint8_t val);
	void arrayRead(uint8_t lv_id, uint32_t index, uint8_t gv_ind = 0);
	void arrayMultiRead(uint8_t lv_id, uint32_t index,uint8_t length);
	void inputDeviceSetup(uint8_t port, uint8_t repeat, uint16_t time, uint8_t write_size, uint8_t writearr, uint8_t readsize, uint8_t readarr);
	
	// response handlers
	static int responseReadSensor(CBuffer& data);
	static CBuffer responseArrayMultiRead(CBuffer &data, uint8_t length);
	static uint16_t responseArrayCreate(CBuffer &data);
	
	// general
	CBuffer& toBytes();
	uint8_t getType() {return data[4];}
};