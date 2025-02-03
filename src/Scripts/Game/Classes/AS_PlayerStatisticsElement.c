class AS_PlayerStatsElement
{
    string m_sPlayerIdentityId;
	
	float m_fGamingTime;

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
    void AS_PlayerStatsElement()
    {

    }

    void SetPlayerIdentityId(string s)
    {
        m_sPlayerIdentityId = s;
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