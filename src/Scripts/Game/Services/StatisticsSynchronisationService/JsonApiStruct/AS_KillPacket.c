class AS_KillPacket : JsonApiStruct
{
	ref array<ref AS_KillElementPacket> kills;
	string serverId;
	string apiKey;
	
	
	void AS_KillPacket()
	{
		// these variables will be converted to JSON or filled from JSON
		RegV("kills");
		RegV("serverId");
		RegV("apiKey");
	}
	
	void SetKillElements(array<ref AS_KillElementPacket> killElements)
	{
		kills = killElements;
	}
	
	void SetServerId(string serverIdToSet)
	{
	  	serverId = serverIdToSet;
	}
	
	void SetApiKey(string apiKeyToSet)
	{
		apiKey = apiKeyToSet;
	}
}