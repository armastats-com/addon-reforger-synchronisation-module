modded class SCR_BaseGameMode : SCR_BaseGameMode
{
	// Map zur Speicherung der Kills und Tode pro Spieler
	private ref map<string, int> m_Kills;
	private ref map<string, int> m_Deaths;
	
	private ref AS_StatisticsSynchronisationService m_StatisticsSynchronisationService;


	//
	protected ref ScriptInvokerBase<SCR_BaseGameMode_OnControllableDestroyed> m_OnControllableDestroyed = new ScriptInvokerBase<SCR_BaseGameMode_OnControllableDestroyed>();

	//------------------------------------------------------------------------------------------------
	//! OnGameStart Event
	override void OnGameStart()
	{
		//
		super.OnGameStart();
		
		// Get an Instance of the Synchronisation Service
		m_StatisticsSynchronisationService = AS_StatisticsSynchronisationService.GetInstance();
		m_StatisticsSynchronisationService.PerformInitializationCheck();
	}

	override void OnControllableDestroyed(IEntity entity, IEntity killerEntity, notnull Instigator instigator)
	{
		super.OnControllableDestroyed(entity, killerEntity, instigator);
		
		//~ 
		BackendApi backendApi = GetGame().GetBackendApi();
		PlayerManager playerManager = GetGame().GetPlayerManager();
		FactionManager factionManager = GetGame().GetFactionManager();	

		//~ Create instigator context data to determine what the relation is between victim and killer and control types of the victim and killer
		SCR_InstigatorContextData instigatorContextData = new SCR_InstigatorContextData(-1, entity, killerEntity, instigator);
		m_OnControllableDestroyed.Invoke(instigatorContextData);
		
		//~
		// TODO Case Suicide 
		// TODO Case KILLED_BY_ENEMY_AI
		// TODO Case KILLED_BY_ENEMY_PLAYER
		// TODO Case KILLED_BY_FRIENDLY_AI
		// TODO Case KILLED_BY_FRIENDLY_PLAYER
		// TODO Case KILLED_BY_UNLIMITED_EDITOR
		// TODO Case DELETED
		// TODO Case DELETED_BY_EDITOR
		// TODO Case VICTIM_IS_NEUTRAL_OR_FACTIONLESS
		// TODO Case NOT_A_CHARACTER
		// string victimKillerRelation = typename.EnumToString(SCR_ECharacterDeathStatusRelations, instigatorContextData.GetVictimKillerRelation());
		
		//~
		// TODO UNKNOWN
		// TODO PLAYER
		// TODO AI
		// TODO POSSESSED_AI
		// TODO UNLIMITED_EDITOR
		//string victimCharacterControlType = typename.EnumToString(SCR_ECharacterControlType, instigatorContextData.GetVictimCharacterControlType());

		//
		AS_KillElement killElement = new AS_KillElement();
		
		// Extract all victim related data
		int victimPlayerId = instigatorContextData.GetVictimPlayerID();
		string victimPlayerIdentityId = backendApi.GetPlayerIdentityId(victimPlayerId);
		string victimPlayerName = playerManager.GetPlayerNameByIdentity(victimPlayerIdentityId);
		string victimKillerRelation = typename.EnumToString(SCR_ECharacterDeathStatusRelations, instigatorContextData.GetVictimKillerRelation());
		string victimCharacterControlType = typename.EnumToString(SCR_ECharacterControlType, instigatorContextData.GetVictimCharacterControlType());
		Faction victimFaction = GetFaction(entity, victimPlayerId);
		string victimFactionName = victimFaction.GetFactionName();
		
		// Extract all victim related data
		killElement.SetVictimPlayerIdentityId(victimPlayerIdentityId);
		killElement.SetVictimPlayerName(victimPlayerName);
		killElement.SetVictimKillerRelation(victimKillerRelation);
		killElement.SetVictimCharacterControlType(victimCharacterControlType);
		killElement.SetVictimFactionName(victimFactionName);
		
		// Extract all killer related data
		int killerPlayerId = instigatorContextData.GetKillerPlayerID();
		string killerPlayerIdentityId = backendApi.GetPlayerIdentityId(killerPlayerId);
		string killerPlayerName = playerManager.GetPlayerNameByIdentity(killerPlayerIdentityId);
		string killerCharacterControlType = typename.EnumToString(SCR_ECharacterControlType, instigatorContextData.GetKillerCharacterControlType());
		Faction killerFaction = GetFaction(killerEntity, killerPlayerId);
		string killerFactionName = killerFaction.GetFactionName();
		
		string killerWeaponName;
		BaseWeaponManagerComponent weaponManager = BaseWeaponManagerComponent.Cast(killerEntity.FindComponent(BaseWeaponManagerComponent));
		if (weaponManager) 
		{
			WeaponSlotComponent slot = weaponManager.GetCurrentSlot();
			killerWeaponName = slot.GetUIInfo().GetName();
		}
		
		killElement.SetKillerPlayerIdentityId(killerPlayerIdentityId);
		killElement.SetKillerPlayerName(killerPlayerName);
		killElement.SetKillerCharacterControlType(killerCharacterControlType);
		killElement.SetKillerFactionName(killerFactionName);
		killElement.SetKillerWeaponName(killerWeaponName);
		
		//
		if (entity && killerEntity) 
		{
			vector entityPos = entity.GetOrigin();
	        vector attackerPos = killerEntity.GetOrigin();
	        float distance = vector.Distance(entityPos, attackerPos);
			killElement.SetDistance(distance);
		}
		
		// Debug Output
		Print("Victim Data:");
		Print("victimPlayerId: " + victimPlayerId);
		Print("victimPlayerIdentityId: " + victimPlayerIdentityId);
		Print("victimPlayerName: " + victimPlayerName);
		Print("victimKillerRelation: " + victimKillerRelation);
		Print("victimCharacterControlType: " + victimCharacterControlType);
		Print("victimFaction: " + victimFaction);
		Print("victimFactionName: " + victimFactionName);
		Print("Killer Data:");
		Print("killerPlayerId: " + killerPlayerId);
		Print("killerPlayerIdentityId: " + killerPlayerIdentityId);
		Print("killerPlayerName: " + killerPlayerName);
		Print("killerCharacterControlType: " + killerCharacterControlType);
		Print("killerFaction: " + killerFaction);
		Print("killerFactionName: " + killerFactionName);
		Print("killerWeaponName: " + killerWeaponName);
		Print("distance: " + killElement.m_fDistance.ToString());
		
		//
		m_StatisticsSynchronisationService.SendKill(killElement);
	}
	
	protected Faction GetFaction(IEntity entity, int playerID)
	{
		if (!entity)
			return GetFactionFromPlayerID(playerID);
		
		FactionAffiliationComponent factionAffiliation = FactionAffiliationComponent.Cast(entity.FindComponent(FactionAffiliationComponent));
		if (!factionAffiliation)
			return GetFactionFromPlayerID(playerID);
		
		return factionAffiliation.GetAffiliatedFaction();
	}
	
	//------------------------------------------------------------------------------------------------
	//~ Get faction off player ID
	protected Faction GetFactionFromPlayerID(int playerID)
	{
		if (playerID <= 0)
			return null;
		
		return SCR_FactionManager.SGetPlayerFaction(playerID);
	}
}
