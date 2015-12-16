#ifndef DRIVERSTATION
#define DRIVERSTATION

#include<Arduino.h>
#include<SPI.h>
#include<WiFi.h>
#include<WiFiUdp.h>
#include<string>

using namespace std;


	class DriverStation
	{
	public:

		enum MotorTypes { Stepper, Servo, Standard };

		DriverStation(string ssid, string password, int port, int key);

		string GetNetworkID();
		void SetNetworkID(string id);
		string GetNetworkPassword();
		void SetNetworkPassword(string password);
		int GetPortNumber();
		void SetPortNumber(int portNum);
		int GetKeyIndex();
		void SetKeyIndex(int key);

		string GetWiFiID();
		IPAddress GetIPAddress();
		long GetSignalStrength();

		void Initialize();
		void Run();

		//Ask if we want to separate classes or keep one for simplicity. 

	private:
		string networkID;
		string networkPassword;
		int networkStatus = WL_IDLE_STATUS;
		int portNumber;
		int keyIndex;

		char packetBuffer[255];
		WiFiUDP udpObject;
		int packetSize;
		IPAddress remoteIP;
		int packetLength;

		string inputCommand;
		string motorCommands[10];
		int commandCounter;
		MotorTypes motors[10];


	};


#endif DRIVERSTATION

