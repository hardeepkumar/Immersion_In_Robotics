#include"DriverStation.h"

DriverStation::DriverStation(string ssid, string password, int port, int key) : networkID(ssid), networkPassword(password), portNumber(port), keyIndex(key)
{

}

string DriverStation::GetNetworkID()
{
	return networkID;
}

void DriverStation::SetNetworkID(string id)
{
	networkID = id;
}

string DriverStation::GetNetworkPassword()
{
	return networkPassword;
}

void DriverStation::SetNetworkPassword(string password)
{
	networkPassword = password;
}

int DriverStation::GetPortNumber()
{
	return portNumber;
}

void DriverStation::SetPortNumber(int portNum)
{
	portNumber = portNum;
}

int DriverStation::GetKeyIndex()
{
	return keyIndex;
}

void DriverStation::SetKeyIndex(int key)
{
	keyIndex = key;
}

string DriverStation::GetWiFiID()
{
	return WiFi.SSID();
}

IPAddress DriverStation::GetIPAddress()
{
	IPAddress ip = WiFi.localIP();
	return ip;
}

long DriverStation::GetSignalStrength()
{
	return WiFi.RSSI();
}

void DriverStation::Initialize()
{
	Serial.begin(9600);

	while (networkStatus != WL_CONNECTED)
	{
		Serial.print("Connecting to network...");
		Serial.print(networkID);

		networkStatus = WiFI.begin(networkID, networkPassword);

		delay(5000);
	}

	Serial.println("Connecting...");
	Serial.println(GetWiFiID());
	Serial.println(GetIPAddress());
	Serial.println(GetSignalStrength());

	Udp.begin(localport);
}

void DriverStation::Run()
{
	packetSize = Udp.parsePacket();
	packetLength = Udp.read(packetBuffer, 255);

	if (packetLength > 0)
	{
		packetBuffer[packetLength] = 0;
	}

	inputCommand = packetBuffer;

	for (int i = 0; i < inputCommand.length(); i++)
	{
		if (inputCommand[i] != ',')
		{
			motorCommands[commandCounter] = motorCommands[commandCounter] + inputCommand[i];
		}
		else
		{
			commandCounter++;
		}
	}
}