class AS_StatisticsSynchronisationService
{
	//
	protected static ref AS_StatisticsSynchronisationService s_Instance;
	
	//
	string m_sApi;
	string m_sApiKey;
	string m_sServerId;
	
	//
	bool m_bInitSuccessfully = false;
	bool m_bConnectedSuccessfully = false;
	
	ref AS_RestCallbackSendPing m_xRestCallbackSendPing;
	ref AS_RestCallbackSendKillPacket m_xRestCallbackSendKillPacket;
	ref AS_SendPlayerStatisticsRestCallback m_xSendPlayerStatisticsRestCallback;
	
	
	//------------------------------------------------------------------------------------------------
	//! Main Method to access the Synchronisation Service Instance.
	//! Attention: This is a Singleton! Call AS_StatisticsSynchronisationService.getInstance() only!
	static ref AS_StatisticsSynchronisationService GetInstance()
	{
		//
	    if (s_Instance)
		{
			return s_Instance;
		}
		
		//
		s_Instance = new AS_StatisticsSynchronisationService();
		
		//
		return s_Instance;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Performs a basic initialization check if the API is reachable
	void PerformInitializationCheck()
	{
		//
		if (!s_Instance)
		{
			Print("[ArmaStats.com] Initialization failed: No instance available.", LogLevel.ERROR);
			return;
		}
		
		#ifdef WORKBENCH
		m_sApi = "https://api-reforger.armastats.com/";
		m_sServerId = "67a0f0130ca5886d8f1306e1";
		m_sApiKey = "rofldiekatz";
		m_bInitSuccessfully = true;
		#endif
		
		//
		if (!System.IsCLIParam("armastats-api"))
		{
			AS_LoggerService.Error("Please add the CLI Parameter \"armastats-api\" to your server start script.");
			return;
		}

		//
		System.GetCLIParam("armastats-api", m_sApi);
		
		
		
		//
		if (!System.IsCLIParam("armastats-api-key"))
		{
			AS_LoggerService.Error("Please add the CLI Parameter \"armastats-api-key\" to your server start script.");
			return;
		}

		//
		System.GetCLIParam("armastats-api-key", m_sApiKey);
		
			
		//
		if (!System.IsCLIParam("armastats-server-id"))
		{
			AS_LoggerService.Error("Please add the CLI Parameter \"armastats-server-id\" to your server start script.");
			return;
		}

		//
		System.GetCLIParam("armastats-server-id", m_sServerId);
				
		//
		AS_LoggerService.Debug("Setting API to " + m_sApi);
		AS_LoggerService.Debug("Setting API Key to " + m_sApiKey);
		AS_LoggerService.Debug("Setting Server Id to " + m_sServerId);
		
		//
		m_bInitSuccessfully = true;
		
		//
  		AS_LoggerService.Log("Sending ping to API..");
		
		SendPing();
	}
	
	void SetConnectedSuccessfully() 
	{
		m_bConnectedSuccessfully = true;
	}
	
	bool IsInitializedSuccessfully()
	{
		return m_bConnectedSuccessfully;
	}
	
	bool IsReadyToSendPackets() {
		return m_bInitSuccessfully && m_bConnectedSuccessfully;
	}

	//------------------------------------------------------------------------------------------------
	//! Sends the PING Call to our API to validate that everything is working as expected
	void SendPing()
	{
		// If callback is not set already: Create a new one
		if (!m_xRestCallbackSendPing) {
			m_xRestCallbackSendPing = new AS_RestCallbackSendPing();
		}
		
		// Referencing SyncService in order to access service function
		m_xRestCallbackSendPing.SetSyncService(this);
		
		// 
		AS_PingPacketJsonApiStruct packet = new AS_PingPacketJsonApiStruct();
		packet.serverId = m_sServerId;
		packet.apiKey = m_sApiKey;
		
		packet.Pack();
		string packetAsString = packet.AsString();
		
		AS_LoggerService.Debug("PingPacket: " + packetAsString);
				
		// Sending Call
		RestContext ctx = GetGame().GetRestApi().GetContext(m_sApi);
		ctx.SetHeaders("Content-Type,application/json");
		ctx.POST(m_xRestCallbackSendPing, AS_EndPointURIService.GetEndpointPing(), packetAsString);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Sends the Kill Data to our API
	void SendKill(AS_KillElement killElement, string sessionId)
	{
		// Create callback if not created already
		if (!m_xRestCallbackSendKillPacket) {
			m_xRestCallbackSendKillPacket = new AS_RestCallbackSendKillPacket();
		}
		
		// Create KillElement
		AS_KillElementJsonApiStruct killElementPacket = new AS_KillElementJsonApiStruct();
		killElementPacket.FillWithKillElementData(killElement);
		
		// Create KillPacket
		AS_KillPacketJsonApiStruct killPacket = new AS_KillPacketJsonApiStruct();
		killPacket.SetKillElements({killElementPacket});
		killPacket.SetServerId(m_sServerId);
		killPacket.SetApiKey(m_sApiKey);
		killPacket.SetSessionId(sessionId);
		
		// Create JSON
		killPacket.Pack();
		string packetAsString = killPacket.AsString();
		
		AS_LoggerService.Debug("KillPacket: " + packetAsString);
				
		// Send Call
		RestContext ctx = GetGame().GetRestApi().GetContext(m_sApi);
		ctx.SetHeaders("Content-Type,application/json");
		ctx.POST(m_xRestCallbackSendKillPacket, AS_EndPointURIService.GetEndpointKillLog(), packetAsString);
	}

	//------------------------------------------------------------------------------------------------
	//! Sends the player statistics to our API
	void SendPlayerStatistics(array<ref AS_PlayerStatisticsElement> playerStatisticsElements, string sessionId)
	{
		// Create callback if not created already
		if (!m_xSendPlayerStatisticsRestCallback) {
			m_xSendPlayerStatisticsRestCallback = new AS_SendPlayerStatisticsRestCallback();
		}
		
		// Create the base packet
		AS_PlayerStatisticsPacketJsonApiStruct packet = new AS_PlayerStatisticsPacketJsonApiStruct();
		packet.SetSessionId(sessionId);
		packet.SetServerId(m_sServerId);
		packet.SetApiKey(m_sApiKey);
		
		// Map the internal statistics elements to JSON objects
		array<ref AS_PlayerStatisticsElementJsonApiStruct> elementsToPush = {};
		foreach (AS_PlayerStatisticsElement playerStatisticsElement : playerStatisticsElements)
		{
			AS_PlayerStatisticsElementJsonApiStruct elementToPush = new AS_PlayerStatisticsElementJsonApiStruct();
			elementToPush.FillWithPlayerStatisticsElement(playerStatisticsElement);
			
			elementsToPush.Insert(elementToPush);
		}
		
		// Assign the JSON objects to the packet
		packet.SetPlayerStatisticsElements(elementsToPush);
		
		// Create JSON
		packet.Pack();
		string packetAsString = packet.AsString();
		AS_LoggerService.Debug("PlayerStatisticsPacket: " + packetAsString);

		// Send Call
		RestContext ctx = GetGame().GetRestApi().GetContext(m_sApi);
		ctx.SetHeaders("Content-Type,application/json");
		ctx.POST(m_xRestCallbackSendKillPacket, AS_EndPointURIService.GetEndPointPlayerStatistics(), packetAsString);
	}
}
