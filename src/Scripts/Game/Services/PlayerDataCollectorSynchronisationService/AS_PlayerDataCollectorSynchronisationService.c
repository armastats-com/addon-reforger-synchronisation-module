class AS_PlayerDataCollectorSynchronisationService
{
	//
	protected static ref AS_PlayerDataCollectorSynchronisationService s_Instance;
	
	//
	bool m_bIsfirstRun = true;
	ref map<string, ref AS_PlayerStatsElement> m_mPlayerStatsElement = new map<string, ref AS_PlayerStatsElement>();
	
	//------------------------------------------------------------------------------------------------
	//! Main Method to access the Synchronisation Service Instance.
	//! Attention: This is a Singleton! Call AS_PlayerDataCollectorSynchronisationService.getInstance() only!
	static ref AS_PlayerDataCollectorSynchronisationService GetInstance()
	{
		//
	    if (s_Instance)
		{
			return s_Instance;
		}
		
		//
		s_Instance = new AS_PlayerDataCollectorSynchronisationService();
		
		
		//
		return s_Instance;
	}
	
	void StartCronjob()
	{
		GetGame().GetCallqueue().CallLater(GetPlayerData, 10000, true);
	}
	
	void GetPlayerData() 
	{
		array<int> players = new array<int>;
		GetGame().GetPlayerManager().GetPlayers(players);
		BackendApi backendApi = GetGame().GetBackendApi();
		
		array<ref AS_PlayerStatsElement> playerStatsToSend = new array<ref AS_PlayerStatsElement>;
		
		foreach (int playerId: players)
		{
			//
			SCR_PlayerData playerDataNew = GetGame().GetDataCollector().GetPlayerData(playerId);
			string playerIdentityId = backendApi.GetPlayerIdentityId(playerId);
			array<float> reforgerPlayerStats = playerDataNew.GetStats();
			
			// In case it's the first run (on initialization): Only get the data from the manager
			if (m_bIsfirstRun) {
				ref AS_PlayerStatsElement playerStatsElement = new AS_PlayerStatsElement();
				MapReforgerPlayerStatsToPlayerStatsElement(playerStatsElement, playerIdentityId, reforgerPlayerStats);				
				m_mPlayerStatsElement.Set(playerIdentityId, playerStatsElement);
				continue;
			}
			
			// If it's not the first run, try to create the delta and prepare data to be sent to server
			if (!m_bIsfirstRun) {
			    // Try to get the PlayerStatsElement from the last calculation round
			    ref AS_PlayerStatsElement playerStatsElementLastRound = m_mPlayerStatsElement.Get(playerIdentityId);

				// If there's no prev distance: just save it and abort
				if (!playerStatsElementLastRound) {
					//
					ref AS_PlayerStatsElement playerStatsElement = new AS_PlayerStatsElement();
					MapReforgerPlayerStatsToPlayerStatsElement(playerStatsElementLastRound, playerIdentityId, reforgerPlayerStats);

                    m_mPlayerStatsElement.Set(playerIdentityId, playerStatsElementLastRound);

					continue;
				}
				
				// Create a new PlayerStats Object with the current data
				ref AS_PlayerStatsElement playerStatsElementCurrentRound = new AS_PlayerStatsElement();
				MapReforgerPlayerStatsToPlayerStatsElement(playerStatsElementCurrentRound, playerIdentityId, reforgerPlayerStats);
				
				// Create a new PlayerStats Object with the deltas of current and last stats (we only send deltas)
				ref AS_PlayerStatsElement playerStatsElementToSend = new AS_PlayerStatsElement();
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
		
		// TODO Send Stuff
		Print("I would send " + playerStatsToSend.Get(0).m_fDistanceWalked);
	}
	
	void MapReforgerPlayerStatsToPlayerStatsElement(AS_PlayerStatsElement playerStatsElement, string playerIdentityId, array<float> reforgerPlayerStats)
	{
		playerStatsElement.SetPlayerIdentityId(playerIdentityId);
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
	
	void MapPlayerStatsElementDeltasToElementToSend(AS_PlayerStatsElement playerStatsElementToSend, AS_PlayerStatsElement playerStatsElementLastRound, AS_PlayerStatsElement playerStatsElementCurrentRound)
	{
		playerStatsElementToSend.SetDistanceWalked(playerStatsElementCurrentRound.m_fDistanceWalked - playerStatsElementLastRound.m_fDistanceWalked);
        playerStatsElementToSend.SetDistanceDriven(playerStatsElementCurrentRound.m_fDistanceDriven - playerStatsElementLastRound.m_fDistanceDriven);
        playerStatsElementToSend.SetDistanceAsOccupant(playerStatsElementCurrentRound.m_fDistanceAsOccupant - playerStatsElementLastRound.m_fDistanceAsOccupant);
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
