#ifndef DRIVERSTATION
#define DRIVERSTATION

#include<Arduino.h>
#include<SPI.h>
#include<WiFi.h>
#include<WiFiUdp.h>
#include<string>

class DriverStation
{
public:

	enum MotorTypes { Stepper, Servo, Standard };
	//Ask if we want to separate classes or keep one for simplicity. 

private:
	char networkID[];
	char networkPassword[];
	int networkStatus = WL_IDLE_STATUS;
	int portNumber;

	char packetBuffer[255];
	WiFiUDP udpObject;
	int packetSize;
	IPAddress remoteIP;
	int packetLength;

	std::string inputCommand;
	std::string motorCommands[10];
	MotorTypes motors[10];


};

#endif DRIVERSTATION

