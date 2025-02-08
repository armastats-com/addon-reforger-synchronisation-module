class AS_ServerStatisticsJsonApiStruct : JsonApiStruct
{
	int numberOfPlayersOnline;
	int numberOfPlayersOnlineXbox;
	int numberOfPlayersOnlinePS;
	int numberOfPlayersOnlinePC;
	
	void AS_ServerStatisticsJsonApiStruct()
	{
		RegV("numberOfPlayersOnline");
		RegV("numberOfPlayersOnlineXbox");
		RegV("numberOfPlayersOnlinePS");
		RegV("numberOfPlayersOnlinePC");
	}
	
	void FillWithServerStatistics(AS_ServerStatistics element)
	{
	 	numberOfPlayersOnline = element.m_iNumberOfPlayersOnline;
	 	numberOfPlayersOnlineXbox = element.m_iNumberOfPlayersOnlineXbox;
	 	numberOfPlayersOnlinePS = element.m_iNumberOfPlayersOnlinePS;
	 	numberOfPlayersOnlinePC = element.m_iNumberOfPlayersOnlinePC;
	}
}