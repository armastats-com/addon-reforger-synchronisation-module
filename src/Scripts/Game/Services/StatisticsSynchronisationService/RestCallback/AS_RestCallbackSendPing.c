class AS_RestCallbackSendPing : RestCallback
{
	ref AS_StatisticsSynchronisationService m_xSyncService;
	
	void SetSyncService(AS_StatisticsSynchronisationService service)
	{
	   m_xSyncService = service;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnError(int errorCode)
	{
		Print("[ArmaStats.com] API returned " + errorCode.ToString(), LogLevel.ERROR);
		// TODO-AS Try again after 30 Seconds
		// TODO-AS More Details depending on errorCode
	}

	//------------------------------------------------------------------------------------------------
	override void OnTimeout()
	{
		Print("[ArmaStats.com] Timeout while trying to connect to the API", LogLevel.ERROR);
		// TODO-AS Try again after 30 Seconds
	}

	//------------------------------------------------------------------------------------------------
	override void OnSuccess(string data, int dataSize)
	{	
		m_xSyncService.SetConnectedSuccessfully();
		Print("[ArmaStats.com] Connected successfully!", LogLevel.NORMAL);
	}
}