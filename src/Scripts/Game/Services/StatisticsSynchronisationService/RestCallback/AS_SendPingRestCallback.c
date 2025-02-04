class AS_SendPingRestCallback : RestCallback
{
	ref AS_StatisticsSynchronisationService m_xSyncService;
	
	void SetSyncService(AS_StatisticsSynchronisationService service)
	{
	   m_xSyncService = service;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnError(int errorCode)
	{
		AS_LoggerService.Error("Ping failed, API returned: " + errorCode.ToString());
		// TODO-AS Try again after 30 Seconds
		// TODO-AS More Details depending on errorCode
	}

	//------------------------------------------------------------------------------------------------
	override void OnTimeout()
	{
		AS_LoggerService.Error("Ping failed, Timeout while trying to connect to the API.");
		// TODO-AS Try again after 30 Seconds
	}

	//------------------------------------------------------------------------------------------------
	override void OnSuccess(string data, int dataSize)
	{	
		m_xSyncService.SetConnectedSuccessfully();
		AS_LoggerService.Log("Connected successfully!");
	}
}