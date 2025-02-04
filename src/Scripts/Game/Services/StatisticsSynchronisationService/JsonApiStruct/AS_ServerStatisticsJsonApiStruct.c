class AS_ServerStatisticsJsonApiStruct : JsonApiStruct
{
	int numberOfPlayersOnline;
	
	void AS_ServerStatisticsJsonApiStruct()
	{
		RegV("numberOfPlayersOnline");
	}
	
	void FillWithServerStatistics(AS_ServerStatistics element)
	{
	 	numberOfPlayersOnline = element.m_iNumberOfPlayersOnline;
	}
}