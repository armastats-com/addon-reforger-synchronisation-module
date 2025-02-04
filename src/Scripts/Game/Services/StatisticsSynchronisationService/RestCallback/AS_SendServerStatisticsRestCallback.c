class AS_SendServerStatisticsRestCallback : RestCallback
{
	//------------------------------------------------------------------------------------------------
	override void OnError(int errorCode)
	{
		AS_LoggerService.Error("Error while trying to send server statistics: " + errorCode.ToString());
	}

	//------------------------------------------------------------------------------------------------
	override void OnTimeout()
	{
		AS_LoggerService.Error("Timeout while trying to send server statistics");
	}

	//------------------------------------------------------------------------------------------------
	override void OnSuccess(string data, int dataSize)
	{	
		AS_LoggerService.Debug("Successfully sent server statistics");
	}
}