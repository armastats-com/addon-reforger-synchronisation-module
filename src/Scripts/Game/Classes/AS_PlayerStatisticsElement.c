class AS_PlayerStatisticsElement
{
    string m_sPlayerIdentityId;
    string m_sPlayerName;
	
	float m_fGamingTime;
	
	float m_fExperiencePoints;
	
	float m_fPointsInfantry;
	float m_fPointsLogistics;
	float m_fPointsMedical;
	float m_fPointsWarcriminal;
	
	float m_fKillsEnemy;
	float m_fKillsEnemyAI;
	
	float m_fKillsFriendly;
	float m_fKillsFriendlyAI;
	
	float m_fRoadKillsEnemy;
	float m_fRoadKillsEnemyAI;
	
	float m_fRoadKillsFriendly;
	float m_fRoadKillsFriendlyAI;
	
	float m_fDeaths;

    float m_fDistanceWalked;
    float m_fDistanceDriven;
    float m_fDistanceDrivenAsOccupant;

    float m_fShots;
    float m_fGrenadesThrown;

    float m_fBandageSelf;
    float m_fBandageFriendlies;

    float m_fTourniquetSelf;
    float m_fTourniquetFriendlies;

    float m_fSalineSelf;
    float m_fSalineFriendlies;

    float m_fMorphineSelf;
    float m_fMorphineFriendlies;

    //------------------------------------------------------------------------------------------------
    void AS_PlayerStatisticsElement()
    {

    }
	
	void SetPlayerName(string s) 
	{
		m_sPlayerName = s;
	}
	
	void SetRoadKillsFriendly(float f)
	{
		m_fRoadKillsFriendly = f;
	}
	
	void SetRoadKillsFriendlyAI(float f)
	{
		m_fRoadKillsFriendlyAI = f;
	}
	
	void SetRoadKillsEnemy(float f)
	{
		m_fRoadKillsEnemy = f;
	}
	
	void SetRoadKillsEnemyAI(float f)
	{
		m_fRoadKillsEnemyAI = f;
	}
	
	void SetDeaths(float f)
	{
		m_fDeaths = f;
	}
	
	void SetKillsFriendly(float f)
	{
	  	m_fKillsFriendly = f;
	}
	
	void SetKillsFriendlyAI(float f)
	{
	  	m_fKillsFriendlyAI = f;
	}
	
	void SetKillsEnemy(float f)
	{
	  	m_fKillsEnemy = f;
	}
	
	void SetKillsEnemyAI(float f)
	{
	  	m_fKillsEnemyAI = f;
	}

    void SetPlayerIdentityId(string s)
    {
        m_sPlayerIdentityId = s;
    }
	
	void SetExperience(float f)
	{
	    m_fExperiencePoints = f;
	}
	
	void SetPointsInfantry(float f)
	{
	    m_fPointsInfantry = f;
	}
	
	void SetPointsLogistics(float f)
	{
	    m_fPointsLogistics = f;
	}
	
	void SetPointsMedical(float f)
	{
	    m_fPointsMedical = f;
	}
	
	void SetPointsWarcriminal(float f)
	{
	    m_fPointsWarcriminal = f;
	}
	
	void SetDistanceWalked(float f)
	{
	    m_fDistanceWalked = f;
	}
	
	void SetGamingTime(float f)
	{
	    m_fGamingTime = f;
	}

	void SetDistanceDriven(float f)
	{
	    m_fDistanceDriven = f;
	}

	void SetDistanceAsOccupant(float f)
	{
	    m_fDistanceDrivenAsOccupant = f;
	}

	void SetShots(float f)
	{
	    m_fShots = f;
	}

	void SetGrenadesThrown(float f)
	{
	    m_fGrenadesThrown = f;
	}

	void SetBandagesSelf(float f)
	{
	    m_fBandageSelf = f;
	}

	void SetBandagesFriendlies(float f)
	{
	    m_fBandageFriendlies = f;
	}

	void SetTourniquetSelf(float f)
	{
	    m_fTourniquetSelf = f;
	}

	void SetTourniquetFriendlies(float f)
	{
	    m_fTourniquetFriendlies = f;
	}

	void SetSalineSelf(float f)
	{
	    m_fSalineSelf = f;
	}

	void SetSalineFriendlies(float f)
	{
	    m_fSalineFriendlies = f;
	}

	void SetMorphineSelf(float f)
	{
	    m_fMorphineSelf = f;
	}

	void SetMorphineFriendlies(float f)
	{
	    m_fMorphineFriendlies = f;
	}
	

};