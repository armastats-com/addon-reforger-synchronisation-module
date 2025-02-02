class AS_KillElementPacket : JsonApiStruct
{
	string victimPlayerIdentityId;
	string victimPlayerName;
	string victimKillerRelation;
	string victimCharacterControlType;
	string victimFactionName;
	string killerPlayerIdentityId;
	string killerPlayerName;
	string killerCharacterControlType;
	string killerFactionName;
	string killerWeaponName;
	float distance;
	
	void AS_KillElementPacket()
	{
		// these variables will be converted to JSON or filled from JSON
		RegV("victimPlayerIdentityId");
		RegV("victimPlayerName");
		RegV("victimKillerRelation");
		RegV("victimCharacterControlType");
		RegV("victimFactionName");
		RegV("killerPlayerIdentityId");
		RegV("killerPlayerName");
		RegV("killerCharacterControlType");
		RegV("killerFactionName");
		RegV("killerWeaponName");
		RegV("distance");
	}
	
	void FillWithKillElementData(AS_KillElement element)
	{
	 	victimPlayerIdentityId = element.m_sVictimPlayerIdentityId;
		victimPlayerName = element.m_sVictimPlayerName;
		victimKillerRelation = element.m_sVictimKillerRelation;
		victimCharacterControlType = element.m_sVictimCharacterControlType;
	 	victimFactionName = element.m_sVictimFactionName;
		
	 	killerPlayerIdentityId = element.m_sKillerPlayerIdentityId;
	 	killerPlayerName = element.m_sKillerPlayerName;
	 	killerCharacterControlType = element.m_sKillerCharacterControlType;
	 	killerFactionName = element.m_sKillerFactionName;
	 	killerWeaponName = element.m_sKillerWeaponName;
	 	distance = element.m_fDistance;
	}
}