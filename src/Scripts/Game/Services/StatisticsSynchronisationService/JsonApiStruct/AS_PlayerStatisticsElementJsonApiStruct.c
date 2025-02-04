class AS_PlayerStatisticsElementJsonApiStruct : JsonApiStruct
{
	string playerIdentityId;
	float gamingTime;
	float experiencePoints;
	float pointsInfantry;
	float pointsLogistics;
	float pointsMedical;
	float pointsWarcriminal;
	float killsEnemy;
	float killsEnemyAI;
	float killsFriendly;
	float killsFriendlyAI;
	float roadKillsEnemy;
	float roadKillsEnemyAI;
	float roadKillsFriendly;
	float roadKillsFriendlyAI;
	float deaths;
	float distanceWalked;
	float distanceDriven;
	float distanceDrivenAsOccupant;
	float shotsFired;
	float grenadesThrown;
	float bandageSelf;
	float bandageFriendlies;
	float tourniquetSelf;
	float tourniquetFriendlies;
	float salineSelf;
	float salineFriendlies;
	float morphineSelf;
	float morphineFriendlies;
	
	void AS_PlayerStatisticsElementJsonApiStruct()
	{
		RegV("playerIdentityId");
		RegV("gamingTime");
		RegV("experiencePoints");
		RegV("pointsInfantry");
		RegV("pointsLogistics");
		RegV("pointsMedical");
		RegV("pointsWarcriminal");
		RegV("killsEnemy");
		RegV("killsEnemyAI");
		RegV("killsFriendly");
		RegV("killsFriendlyAI");
		RegV("roadKillsEnemy");
		RegV("roadKillsEnemyAI");
		RegV("roadKillsFriendly");
		RegV("roadKillsFriendlyAI");
		RegV("deaths");
		RegV("distanceWalked");
		RegV("distanceDriven");
		RegV("distanceDrivenAsOccupant");
		RegV("shotsFired");
		RegV("grenadesThrown");
		RegV("bandageSelf");
		RegV("bandageFriendlies");
		RegV("tourniquetSelf");
		RegV("tourniquetFriendlies");
		RegV("salineSelf");
		RegV("salineFriendlies");
		RegV("morphineSelf");
		RegV("morphineFriendlies");
	}
	
	void FillWithPlayerStatisticsElement(AS_PlayerStatisticsElement element)
	{
	 	playerIdentityId = element.m_sPlayerIdentityId;
        gamingTime = element.m_fGamingTime;
		experiencePoints = element.m_fGamingTime;
		pointsInfantry = element.m_fPointsInfantry;
		pointsLogistics = element.m_fPointsLogistics;
		pointsMedical = element.m_fPointsMedical;
		pointsWarcriminal = element.m_fPointsWarcriminal;
		killsEnemy = element.m_fKillsEnemy;
		killsEnemyAI = element.m_fKillsEnemyAI;
		killsFriendly = element.m_fKillsFriendly;
		killsFriendlyAI = element.m_fKillsFriendlyAI;
		roadKillsEnemy = element.m_fRoadKillsEnemy;
		roadKillsEnemyAI = element.m_fRoadKillsEnemyAI;
		roadKillsFriendly = element.m_fRoadKillsFriendly;
		roadKillsFriendlyAI = element.m_fRoadKillsFriendlyAI;
		deaths = element.m_fDeaths;
        distanceWalked = element.m_fDistanceWalked;
        distanceDriven = element.m_fDistanceDriven;
        distanceDrivenAsOccupant = element.m_fDistanceDrivenAsOccupant;
        shotsFired = element.m_fShots;
        grenadesThrown = element.m_fGrenadesThrown;
        bandageSelf = element.m_fBandageSelf;
        bandageFriendlies = element.m_fBandageFriendlies;
        tourniquetSelf = element.m_fTourniquetSelf;
        tourniquetFriendlies = element.m_fTourniquetFriendlies;
        salineSelf = element.m_fSalineSelf;
        salineFriendlies = element.m_fSalineFriendlies;
        morphineSelf = element.m_fMorphineSelf;
        morphineFriendlies = element.m_fMorphineFriendlies;
	}
}