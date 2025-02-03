class AS_KillPacketJsonApiStruct : JsonApiStruct
{
	ref array<ref AS_KillElementJsonApiStruct> kills;
	string serverId;
	string apiKey;
	string sessionId;
	
	
	void AS_KillPacketJsonApiStruct()
	{
		// these variables will be converted to JSON or filled from JSON
		RegV("kills");
		RegV("serverId");
		RegV("apiKey");
		RegV("sessionId");
	}
	
	void SetKillElements(array<ref AS_KillElementJsonApiStruct> elements)
	{
		kills = elements;
	}
	
	void SetServerId(string s)
	{
	  	serverId = s;
	}
	
	void SetApiKey(string s)
	{
		apiKey = s;
	}
	
	void SetSessionId(string s)
	{
		sessionId = s;
	}
}