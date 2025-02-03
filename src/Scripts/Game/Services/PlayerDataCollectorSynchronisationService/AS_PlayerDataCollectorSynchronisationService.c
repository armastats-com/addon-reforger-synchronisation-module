class AS_PlayerDataCollectorSynchronisationService
{
	//
	protected static ref AS_PlayerDataCollectorSynchronisationService s_Instance;
	private ref AS_StatisticsSynchronisationService m_xStatisticsSynchronisationService;
	
	//
	private string m_sSessionId;
	
	//
	bool m_bIsfirstRun = true;
	ref map<string, ref AS_PlayerStatisticsElement> m_mPlayerStatsElement = new map<string, ref AS_PlayerStatisticsElement>();
	
	//------------------------------------------------------------------------------------------------
	//! Main Method to access the Synchronisation Service Instance.
	//! Attention: This is a Singleton! Call AS_PlayerDataCollectorSynchronisationService.getInstance() only!
	static ref AS_PlayerDataCollectorSynchronisationService GetInstance(string sessionId)
	{
		//
	    if (s_Instance)
		{
			return s_Instance;
		}
		
		// Create instance and bind vals
		s_Instance = new AS_PlayerDataCollectorSynchronisationService();	
		
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
		GetGame().GetCallqueue().CallLater(GetPlayerData, 60000, true);
	}
	
	void GetPlayerData() 
	{
		// Abort in case the initialization was not successful
		if (!m_xStatisticsSynchronisationService.IsInitializedSuccessfully()) {
			return;
		}
		
		//
		array<int> players = new array<int>;
		GetGame().GetPlayerManager().GetPlayers(players);
		BackendApi backendApi = GetGame().GetBackendApi();
		
		//
		array<ref AS_PlayerStatisticsElement> playerStatsToSend = new array<ref AS_PlayerStatisticsElement>;
		
		//
		foreach (int playerId: players)
		{
			//
			SCR_PlayerData playerDataNew = GetGame().GetDataCollector().GetPlayerData(playerId);
			string playerIdentityId = backendApi.GetPlayerIdentityId(playerId);
			array<float> reforgerPlayerStats = playerDataNew.GetStats();
			
			// In case it's the first run (on initialization): Only get the data from the manager
			if (m_bIsfirstRun) {
				ref AS_PlayerStatisticsElement playerStatsElement = new AS_PlayerStatisticsElement();
				MapReforgerPlayerStatsToPlayerStatsElement(playerStatsElement, playerIdentityId, reforgerPlayerStats);				
				m_mPlayerStatsElement.Set(playerIdentityId, playerStatsElement);
				continue;
			}
			
			// If it's not the first run, try to create the delta and prepare data to be sent to server
			if (!m_bIsfirstRun) {
			    // Try to get the PlayerStatsElement from the last calculation round
			    ref AS_PlayerStatisticsElement playerStatsElementLastRound = m_mPlayerStatsElement.Get(playerIdentityId);

				// If there's no prev distance: just save it and abort
				if (!playerStatsElementLastRound) {
					//
					ref AS_PlayerStatisticsElement playerStatsElement = new AS_PlayerStatisticsElement();
					MapReforgerPlayerStatsToPlayerStatsElement(playerStatsElementLastRound, playerIdentityId, reforgerPlayerStats);

                    m_mPlayerStatsElement.Set(playerIdentityId, playerStatsElementLastRound);

					continue;
				}
				
				// Create a new PlayerStats Object with the current data
				ref AS_PlayerStatisticsElement playerStatsElementCurrentRound = new AS_PlayerStatisticsElement();
				MapReforgerPlayerStatsToPlayerStatsElement(playerStatsElementCurrentRound, playerIdentityId, reforgerPlayerStats);
				
				// Create a new PlayerStats Object with the deltas of current and last stats (we only send deltas)
				ref AS_PlayerStatisticsElement playerStatsElementToSend = new AS_PlayerStatisticsElement();
                playerStatsElementToSend.SetPlayerIdentityId(playerIdentityId);
				MapPlayerStatsElementDeltasToElementToSend(playerStatsElementToSend, playerStatsElementLastRound, playerStatsElementCurrentRound);
				
				// Add the Delta Object to our "to send" queue
                playerStatsToSend.Insert(playerStatsElementToSend);

				// Update the PlayerStats Object for the next round
				m_mPlayerStatsElement.Set(playerIdentityId, playerStatsElementCurrentRound);

			}
		}
		
		// If it's a first run: We don't need to send anything
		if (m_bIsfirstRun) {
			m_bIsfirstRun = false;
			return;
		}
		
		// Send the statistics to the API
		m_xStatisticsSynchronisationService.SendPlayerStatistics(playerStatsToSend, m_sSessionId);
	}
	
	void MapReforgerPlayerStatsToPlayerStatsElement(AS_PlayerStatisticsElement playerStatsElement, string playerIdentityId, array<float> reforgerPlayerStats)
	{
		playerStatsElement.SetPlayerIdentityId(playerIdentityId);		
		playerStatsElement.SetGamingTime(reforgerPlayerStats[SCR_EDataStats.SESSION_DURATION]);
		playerStatsElement.SetExperience(reforgerPlayerStats[SCR_EDataStats.LEVEL_EXPERIENCE]);
		playerStatsElement.SetPointsInfantry(reforgerPlayerStats[SCR_EDataStats.SPPOINTS0]);
		playerStatsElement.SetPointsLogistics(reforgerPlayerStats[SCR_EDataStats.SPPOINTS1]);
		playerStatsElement.SetPointsMedical(reforgerPlayerStats[SCR_EDataStats.SPPOINTS2]);
		playerStatsElement.SetPointsWarcriminal(reforgerPlayerStats[SCR_EDataStats.WARCRIMES]);
		playerStatsElement.SetKillsEnemy(reforgerPlayerStats[SCR_EDataStats.KILLS]);
		playerStatsElement.SetKillsEnemyAI(reforgerPlayerStats[SCR_EDataStats.AI_KILLS]);
		playerStatsElement.SetKillsFriendly(reforgerPlayerStats[SCR_EDataStats.FRIENDLY_KILLS]);
		playerStatsElement.SetKillsFriendlyAI(reforgerPlayerStats[SCR_EDataStats.FRIENDLY_AI_KILLS]);
		playerStatsElement.SetRoadKillsEnemy(reforgerPlayerStats[SCR_EDataStats.ROADKILLS]);
		playerStatsElement.SetRoadKillsEnemyAI(reforgerPlayerStats[SCR_EDataStats.AI_ROADKILLS]);
		playerStatsElement.SetRoadKillsFriendly(reforgerPlayerStats[SCR_EDataStats.FRIENDLY_ROADKILLS]);
		playerStatsElement.SetRoadKillsFriendlyAI(reforgerPlayerStats[SCR_EDataStats.FRIENDLY_AI_ROADKILLS]);
		playerStatsElement.SetDeaths(reforgerPlayerStats[SCR_EDataStats.DEATHS]);
		playerStatsElement.SetDistanceWalked(reforgerPlayerStats[SCR_EDataStats.DISTANCE_WALKED]);
		playerStatsElement.SetDistanceDriven(reforgerPlayerStats[SCR_EDataStats.DISTANCE_DRIVEN]);
        playerStatsElement.SetDistanceAsOccupant(reforgerPlayerStats[SCR_EDataStats.DISTANCE_AS_OCCUPANT]);
        playerStatsElement.SetShots(reforgerPlayerStats[SCR_EDataStats.SHOTS]);
        playerStatsElement.SetGrenadesThrown(reforgerPlayerStats[SCR_EDataStats.GRENADES_THROWN]);
        playerStatsElement.SetBandagesSelf(reforgerPlayerStats[SCR_EDataStats.BANDAGE_SELF]);
        playerStatsElement.SetBandagesFriendlies(reforgerPlayerStats[SCR_EDataStats.BANDAGE_FRIENDLIES]);
        playerStatsElement.SetTourniquetSelf(reforgerPlayerStats[SCR_EDataStats.TOURNIQUET_SELF]);
        playerStatsElement.SetTourniquetFriendlies(reforgerPlayerStats[SCR_EDataStats.TOURNIQUET_FRIENDLIES]);
        playerStatsElement.SetSalineSelf(reforgerPlayerStats[SCR_EDataStats.SALINE_SELF]);
        playerStatsElement.SetSalineFriendlies(reforgerPlayerStats[SCR_EDataStats.SALINE_FRIENDLIES]);
        playerStatsElement.SetMorphineSelf(reforgerPlayerStats[SCR_EDataStats.MORPHINE_SELF]);
        playerStatsElement.SetMorphineFriendlies(reforgerPlayerStats[SCR_EDataStats.MORPHINE_FRIENDLIES]);
	}
	
	void MapPlayerStatsElementDeltasToElementToSend(AS_PlayerStatisticsElement playerStatsElementToSend, AS_PlayerStatisticsElement playerStatsElementLastRound, AS_PlayerStatisticsElement playerStatsElementCurrentRound)
	{
		playerStatsElementToSend.SetGamingTime(playerStatsElementCurrentRound.m_fGamingTime - playerStatsElementLastRound.m_fGamingTime);
		playerStatsElementToSend.SetExperience(playerStatsElementCurrentRound.m_fExperiencePoints - playerStatsElementLastRound.m_fExperiencePoints);
		playerStatsElementToSend.SetPointsInfantry(playerStatsElementCurrentRound.m_fPointsInfantry - playerStatsElementLastRound.m_fPointsInfantry);
		playerStatsElementToSend.SetPointsLogistics(playerStatsElementCurrentRound.m_fPointsLogistics - playerStatsElementLastRound.m_fPointsLogistics);
		playerStatsElementToSend.SetPointsMedical(playerStatsElementCurrentRound.m_fPointsMedical - playerStatsElementLastRound.m_fPointsMedical);
		playerStatsElementToSend.SetPointsWarcriminal(playerStatsElementCurrentRound.m_fPointsWarcriminal - playerStatsElementLastRound.m_fPointsWarcriminal);
		playerStatsElementToSend.SetKillsEnemy(playerStatsElementCurrentRound.m_fKillsEnemy - playerStatsElementLastRound.m_fKillsEnemy);
		playerStatsElementToSend.SetKillsEnemyAI(playerStatsElementCurrentRound.m_fKillsEnemyAI - playerStatsElementLastRound.m_fKillsEnemyAI);
		playerStatsElementToSend.SetKillsFriendly(playerStatsElementCurrentRound.m_fKillsFriendly - playerStatsElementLastRound.m_fKillsFriendly);
		playerStatsElementToSend.SetKillsFriendlyAI(playerStatsElementCurrentRound.m_fKillsFriendlyAI - playerStatsElementLastRound.m_fKillsFriendlyAI);
		playerStatsElementToSend.SetRoadKillsEnemy(playerStatsElementCurrentRound.m_fRoadKillsEnemy - playerStatsElementLastRound.m_fRoadKillsEnemy);
		playerStatsElementToSend.SetRoadKillsEnemyAI(playerStatsElementCurrentRound.m_fRoadKillsEnemyAI - playerStatsElementLastRound.m_fRoadKillsEnemyAI);
		playerStatsElementToSend.SetRoadKillsFriendly(playerStatsElementCurrentRound.m_fRoadKillsFriendly - playerStatsElementLastRound.m_fRoadKillsFriendly);
		playerStatsElementToSend.SetRoadKillsFriendlyAI(playerStatsElementCurrentRound.m_fRoadKillsFriendlyAI - playerStatsElementLastRound.m_fRoadKillsFriendlyAI);
		playerStatsElementToSend.SetDeaths(playerStatsElementCurrentRound.m_fDeaths - playerStatsElementLastRound.m_fDeaths);
		playerStatsElementToSend.SetDistanceWalked(playerStatsElementCurrentRound.m_fDistanceWalked - playerStatsElementLastRound.m_fDistanceWalked);
        playerStatsElementToSend.SetDistanceDriven(playerStatsElementCurrentRound.m_fDistanceDriven - playerStatsElementLastRound.m_fDistanceDriven);
        playerStatsElementToSend.SetDistanceAsOccupant(playerStatsElementCurrentRound.m_fDistanceDrivenAsOccupant - playerStatsElementLastRound.m_fDistanceDrivenAsOccupant);
        playerStatsElementToSend.SetShots(playerStatsElementCurrentRound.m_fShots - playerStatsElementLastRound.m_fShots);
        playerStatsElementToSend.SetGrenadesThrown(playerStatsElementCurrentRound.m_fGrenadesThrown - playerStatsElementLastRound.m_fGrenadesThrown);
        playerStatsElementToSend.SetBandagesSelf(playerStatsElementCurrentRound.m_fBandageSelf - playerStatsElementLastRound.m_fBandageSelf);
        playerStatsElementToSend.SetBandagesFriendlies(playerStatsElementCurrentRound.m_fBandageFriendlies - playerStatsElementLastRound.m_fBandageFriendlies);
        playerStatsElementToSend.SetTourniquetSelf(playerStatsElementCurrentRound.m_fTourniquetSelf - playerStatsElementLastRound.m_fTourniquetSelf);
        playerStatsElementToSend.SetTourniquetFriendlies(playerStatsElementCurrentRound.m_fTourniquetFriendlies - playerStatsElementLastRound.m_fTourniquetFriendlies);
        playerStatsElementToSend.SetSalineSelf(playerStatsElementCurrentRound.m_fSalineSelf - playerStatsElementLastRound.m_fSalineSelf);
        playerStatsElementToSend.SetSalineFriendlies(playerStatsElementCurrentRound.m_fSalineFriendlies - playerStatsElementLastRound.m_fSalineFriendlies);
        playerStatsElementToSend.SetMorphineSelf(playerStatsElementCurrentRound.m_fMorphineSelf - playerStatsElementLastRound.m_fMorphineSelf);
        playerStatsElementToSend.SetMorphineFriendlies(playerStatsElementCurrentRound.m_fMorphineFriendlies - playerStatsElementLastRound.m_fMorphineFriendlies);	
	}	
}
