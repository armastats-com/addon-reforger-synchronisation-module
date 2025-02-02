class AS_KillElement
{
    string m_sVictimPlayerIdentityId;
	string m_sVictimPlayerName;
	string m_sVictimKillerRelation;
	string m_sVictimCharacterControlType;
	string m_sVictimFactionName;
	
	string m_sKillerPlayerIdentityId;
	string m_sKillerPlayerName;
	string m_sKillerCharacterControlType;
	string m_sKillerFactionName;
	string m_sKillerWeaponName;
	
	float m_fDistance;

    //------------------------------------------------------------------------------------------------
    void AS_KillElement()
    {

    }
	
	void SetVictimPlayerIdentityId(string id)
	{
	    m_sVictimPlayerIdentityId = id;
	}
	
	void SetVictimPlayerName(string id)
	{
	    m_sVictimPlayerName = id;
	}
	
	void SetVictimKillerRelation(string id)
	{
	    m_sVictimKillerRelation = id;
	}
	
	void SetVictimCharacterControlType(string id)
	{
	    m_sVictimCharacterControlType = id;
	}
	
	void SetVictimFactionName(string id)
	{
	    m_sVictimFactionName = id;
	}
	
	void SetKillerPlayerIdentityId(string id)
	{
	    m_sKillerPlayerIdentityId = id;
	}
	
	void SetKillerPlayerName(string id)
	{
	    m_sKillerPlayerName = id;
	}
	
	void SetKillerCharacterControlType(string id)
	{
	    m_sKillerCharacterControlType = id;
	}
	
	void SetKillerFactionName(string id)
	{
	    m_sKillerFactionName = id;
	}
	
	void SetKillerWeaponName(string id)
	{
	    m_sKillerWeaponName = id;
	}
	
	void SetDistance(float id)
	{
	    m_fDistance = id;
	}
};