class AS_ServerStatisticsJsonApiStruct : JsonApiStruct
{
	int numberOfPlayersOnline;
	int numberOfPlayersOnlineXbox;
	int numberOfPlayersOnlinePS;
	int numberOfPlayersOnlinePC;
	int numberOfPlayersOnlineMax;
	
	void AS_ServerStatisticsJsonApiStruct()
	{
		RegV("numberOfPlayersOnline");
		RegV("numberOfPlayersOnlineXbox");
		RegV("numberOfPlayersOnlinePS");
		RegV("numberOfPlayersOnlinePC");
		RegV("numberOfPlayersOnlineMax");
	}
	
	void FillWithServerStatistics(AS_ServerStatistics element)
	{
	 	numberOfPlayersOnline = element.m_iNumberOfPlayersOnline;
	 	numberOfPlayersOnlineXbox = element.m_iNumberOfPlayersOnlineXbox;
	 	numberOfPlayersOnlinePS = element.m_iNumberOfPlayersOnlinePS;
	 	numberOfPlayersOnlinePC = element.m_iNumberOfPlayersOnlinePC;
	 	numberOfPlayersOnlineMax = element.m_iNumberOfPlayersOnlineMax;
	}
}