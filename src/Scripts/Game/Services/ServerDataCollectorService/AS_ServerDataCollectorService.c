class AS_ServerDataCollectorService
{
	//
	protected static ref AS_ServerDataCollectorService s_Instance;
	protected ref AS_StatisticsSynchronisationService m_xStatisticsSynchronisationService;
	protected string m_sSessionId;
	
	//------------------------------------------------------------------------------------------------
	//! Main Method to access the ServerDataCollectorService Service Instance.
	//! Attention: This is a Singleton! Call AS_ServerDataCollectorService.getInstance() only!
	static ref AS_ServerDataCollectorService GetInstance(string sessionId)
	{
		//
	    if (s_Instance)
		{
			return s_Instance;
		}

		// Create instance and bind vals
		s_Instance = new AS_ServerDataCollectorService();

		//
		return s_Instance;
	}
	
	void SetStatisticsSynchronisationService(AS_StatisticsSynchronisationService instance)
	{
		m_xStatisticsSynchronisationService = instance;
	}
	
	void SetSessionId(string s)
	{
		m_sSessionId = s;
	}
	
	void StartCronjob()
	{
		GetGame().GetCallqueue().CallLater(GetServerData, 60000, true);
	}
	
	void GetServerData()
	{
		// Abort in case the initialization was not successful
		if (!m_xStatisticsSynchronisationService.IsInitializedSuccessfully()) {
			return;
		}

		//
	    int playerCountOnline = GetGame().GetPlayerManager().GetPlayerCount();
		int playerCountMax = GetGame().GetServerInfo().GetPlayerLimit();
			
		//
		int playerCountOnlineXbox = 0;
		int playerCountOnlinePS = 0;
		int playerCountOnlinePC = 0;
		array<int> players = new array<int>;		
		GetGame().GetPlayerManager().GetPlayers(players);
		foreach (int playerId: players)
		{
			PlatformKind platform = GetGame().GetPlayerManager().GetPlatformKind(playerId);
			switch (platform)
			{
				case PlatformKind.PSN:
				{
					playerCountOnlinePS++;
					break;
				}
				case PlatformKind.XBOX:
				{
					playerCountOnlineXbox++;
					break;
				}
				case PlatformKind.STEAM:
				{
					playerCountOnlinePC++;
					break;
				}
				case PlatformKind.NONE:
				{
					playerCountOnlinePC++;
					break;
				}
			}
		}
		
		
		//
		AS_ServerStatistics serverStatistics = new AS_ServerStatistics();
		serverStatistics.SetNumberOfPlayersOnline(playerCountOnline);
		serverStatistics.SetNumberOfPlayersOnlineXbox(playerCountOnlineXbox);
		serverStatistics.SetNumberOfPlayersOnlinePS(playerCountOnlinePS);
		serverStatistics.SetNumberOfPlayersOnlinePC(playerCountOnlinePC);
		serverStatistics.SetNumberOfPlayersOnlineMax(playerCountMax);

		//
		m_xStatisticsSynchronisationService.SendServerStatistics(serverStatistics, m_sSessionId);
	}
}