class AS_PlayerStatisticsPacketJsonApiStruct : JsonApiStruct
{
	string serverId;
	string apiKey;
	string sessionId;
	bool isSyncOnPlayerDisconnect;

	ref array<ref AS_PlayerStatisticsElementJsonApiStruct> playerStatistics;

	void AS_PlayerStatisticsPacketJsonApiStruct()
	{
		RegV("serverId");
		RegV("apiKey");
		RegV("sessionId");
		RegV("isSyncOnPlayerDisconnect");

		RegV("playerStatistics");
	}
	
	void SetIsSyncOnPlayerDisconnect(bool b) 
	{
		isSyncOnPlayerDisconnect = b;
	}
	

	void SetPlayerStatisticsElements(array<ref AS_PlayerStatisticsElementJsonApiStruct> playerStatisticsElements)
    {
        playerStatistics = playerStatisticsElements;
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