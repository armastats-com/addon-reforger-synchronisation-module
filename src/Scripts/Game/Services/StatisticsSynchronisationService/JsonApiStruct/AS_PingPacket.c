class AS_PingPacket : JsonApiStruct
{
	string serverId;
	string apiKey;
	
	void AS_PingPacket()
	{
		// these variables will be converted to JSON or filled from JSON
		RegV("serverId");
		RegV("apiKey");
	}
}