class AS_ServerStatisticsPacketJsonApiStruct : JsonApiStruct
{
	string serverId;
	string apiKey;
	string sessionId;

	ref AS_ServerStatisticsJsonApiStruct serverStatistics;

	void AS_ServerStatisticsPacketJsonApiStruct()
	{
		RegV("serverId");
		RegV("apiKey");
		RegV("sessionId");

		RegV("serverStatistics");
	}

	void SetServerStatistic(AS_ServerStatisticsJsonApiStruct serverStatisticsJsonApiStruct)
    {
        serverStatistics = serverStatisticsJsonApiStruct;
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