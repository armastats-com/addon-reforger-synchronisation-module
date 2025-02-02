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
	
	ref RestCallbackSendPing m_callbackExample;
	ref AS_RestCallbackSendKillPacket m_xRestCallbackSendKillPacket;
	
	
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
		
		//
		if (!System.IsCLIParam("armastats-api"))
		{
			Print("[ArmaStats.com] Please add the CLI Parameter \"armastats-api\" to your server start script.", LogLevel.ERROR);
			return;
		}

		//
		System.GetCLIParam("armastats-api", m_sApi);
		
		
		
		//
		if (!System.IsCLIParam("armastats-api-key"))
		{
			Print("[ArmaStats.com] Please add the CLI Parameter \"armastats-api-key\" to your server start script.", LogLevel.ERROR);
			return;
		}

		//
		System.GetCLIParam("armastats-api-key", m_sApiKey);
		
			
		//
		if (!System.IsCLIParam("armastats-server-id"))
		{
			Print("[ArmaStats.com] Please add the CLI Parameter \"armastats-server-id\" to your server start script.", LogLevel.ERROR);
			return;
		}

		//
		System.GetCLIParam("armastats-server-id", m_sServerId);
		
		
		
		//
		Print("[ArmaStats.com] Setting Api to " + m_sApi, LogLevel.DEBUG);
		Print("[ArmaStats.com] Setting Api Key to " + m_sApiKey, LogLevel.DEBUG);
		Print("[ArmaStats.com] Setting Server Id to " + m_sServerId, LogLevel.DEBUG);
		
		//
		m_bInitSuccessfully = true;
		
		// 		
		Print("[ArmaStats.com] Sending ping to API..", LogLevel.NORMAL);
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
		if (!m_callbackExample) {
			m_callbackExample = new RestCallbackSendPing();
		}
		
		// Referencing SyncService in order to access service function
		m_callbackExample.SetSyncService(this);
		
		// 
		AS_PingPacket packet = new AS_PingPacket();
		packet.serverId = m_sServerId;
		packet.apiKey = m_sApiKey;
		
		packet.Pack();
		string packetAsString = packet.AsString();
		Print("[ArmaStats.com] PingPacket: " + packetAsString, LogLevel.DEBUG);
		
		// Sending Call
		RestContext ctx = GetGame().GetRestApi().GetContext(m_sApi);
		ctx.SetHeaders("Content-Type,application/json");
		ctx.POST(m_callbackExample, "v1/reforger-receiver/ping", packetAsString);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Sends the Kill Data to our API
	void SendKill(AS_KillElement killElement)
	{
		// Create callback if not created already
		if (!m_xRestCallbackSendKillPacket) {
			m_xRestCallbackSendKillPacket = new AS_RestCallbackSendKillPacket();
		}
		
		// Create KillElement
		AS_KillElementPacket killElementPacket = new AS_KillElementPacket();
		killElementPacket.FillWithKillElementData(killElement);
		
		// Create KillPacket
		AS_KillPacket killPacket = new AS_KillPacket();
		killPacket.SetKillElements({killElementPacket});
		killPacket.SetServerId(m_sServerId);
		killPacket.SetApiKey(m_sApiKey);
		
		// Create JSON
		killPacket.Pack();
		string packetAsString = killPacket.AsString();
		Print("[ArmaStats.com] KillPacket: " + packetAsString, LogLevel.DEBUG);
		
		// Send Call
		RestContext ctx = GetGame().GetRestApi().GetContext(m_sApi);
		ctx.SetHeaders("Content-Type,application/json");
		ctx.POST(m_xRestCallbackSendKillPacket, "v1/reforger-receiver/kills", packetAsString);
	}
}
