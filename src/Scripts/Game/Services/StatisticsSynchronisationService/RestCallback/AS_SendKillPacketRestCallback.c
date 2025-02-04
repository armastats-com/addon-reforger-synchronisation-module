class AS_SendKillPacketRestCallback : RestCallback
{
	ref AS_StatisticsSynchronisationService m_xSyncService;
	
	void SetSyncService(AS_StatisticsSynchronisationService service)
	{
	   m_xSyncService = service;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnError(int errorCode)
	{
		Print("[ArmaStats.com] Error while trying to send kill, API returned " + errorCode.ToString(), LogLevel.ERROR);
		// TODO-AS Try again after 30 Seconds
		// TODO-AS More Details depending on errorCode
	}

	//------------------------------------------------------------------------------------------------
	override void OnTimeout()
	{
		Print("[ArmaStats.com] Timeout while trying to send kill", LogLevel.ERROR);
		// TODO-AS Try again after 30 Seconds
	}

	//------------------------------------------------------------------------------------------------
	override void OnSuccess(string data, int dataSize)
	{	
		Print("[ArmaStats.com] Kill sent successfully!", LogLevel.DEBUG);
	}
}