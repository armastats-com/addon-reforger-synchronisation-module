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
		AS_LoggerService.Error("Error while trying to send player statistics" + errorCode.ToString());
		// TODO-AS Try again after 30 Seconds
		// TODO-AS More Details depending on errorCode
	}

	//------------------------------------------------------------------------------------------------
	override void OnTimeout()
	{
		AS_LoggerService.Error("Timeout while trying to send player statistics");
		// TODO-AS Try again after 30 Seconds
	}

	//------------------------------------------------------------------------------------------------
	override void OnSuccess(string data, int dataSize)
	{	
		AS_LoggerService.Debug("Successfully sent player statistics");
	}
}