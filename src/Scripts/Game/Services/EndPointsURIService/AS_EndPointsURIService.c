class AS_EndPointURIService
{
	protected const string m_sEndpointPing = "v1/receiver/ping";
	protected const string m_sEndpointKillLog = "v1/receiver/kill-log";
	protected const string m_sEndpointPlayerStatistics = "v1/receiver/player-statistics";
	protected const string m_sEndpointServerStatistics = "v1/receiver/server-statistics";
	
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
		return m_sEndpointPlayerStatistics;
	}
	
	static string GetEndPointServerStatistics()
	{
		return m_sEndpointServerStatistics;
	}
}
