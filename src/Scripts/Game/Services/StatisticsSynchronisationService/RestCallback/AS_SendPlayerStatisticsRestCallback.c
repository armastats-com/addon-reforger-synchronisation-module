class AS_SendPlayerStatisticsRestCallback : RestCallback
{
	ref AS_StatisticsSynchronisationService m_xSyncService;
	
	void SetSyncService(AS_StatisticsSynchronisationService service)
	{
	   m_xSyncService = service;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnError(int errorCode)
	{
		Print("[ArmaStats.com] Error while trying to send player statistics" + errorCode.ToString(), LogLevel.ERROR);
		// TODO-AS Try again after 30 Seconds
		// TODO-AS More Details depending on errorCode
	}

	//------------------------------------------------------------------------------------------------
	override void OnTimeout()
	{
		Print("[ArmaStats.com] Timeout while trying to send player statistics", LogLevel.ERROR);
		// TODO-AS Try again after 30 Seconds
	}

	//------------------------------------------------------------------------------------------------
	override void OnSuccess(string data, int dataSize)
	{	
		Print("[ArmaStats.com] Successfully sent player statistics", LogLevel.NORMAL);
	}
}