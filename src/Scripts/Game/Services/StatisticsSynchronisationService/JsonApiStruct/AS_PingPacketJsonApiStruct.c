class AS_PingPacketJsonApiStruct : JsonApiStruct
{
	string serverId;
	string apiKey;
	
	void AS_PingPacketJsonApiStruct()
	{
		RegV("serverId");
		RegV("apiKey");
	}
}