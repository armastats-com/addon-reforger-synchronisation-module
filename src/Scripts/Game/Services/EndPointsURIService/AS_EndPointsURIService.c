class AS_EndPointURIService
{
	protected const string m_sEndpointPing = "v1/receiver/ping";
	protected const string m_sEndpointKillLog = "v1/receiver/kill-log";
	protected const string m_sEndpointPlayerStatistics = "v1/receiver/player-statistics";
	
	static string GetEndpointPing()
	{
		return m_sEndpointPing;
	}
	
	static string GetEndpointKillLog()
	{
		return m_sEndpointKillLog;
	}
	
	static string GetEndPointPlayerStatistics()
	{
		return m_sEndpointKillLog;
	}
}
