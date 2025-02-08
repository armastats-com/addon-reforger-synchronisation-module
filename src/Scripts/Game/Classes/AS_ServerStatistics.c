class AS_ServerStatistics
{

    float m_iNumberOfPlayersOnline;
    float m_iNumberOfPlayersOnlineXbox;
    float m_iNumberOfPlayersOnlinePS;
    float m_iNumberOfPlayersOnlinePC;

    //------------------------------------------------------------------------------------------------
    void AS_ServerStatistics()
    {

    }
	
	void SetNumberOfPlayersOnline(int f)
	{
		m_iNumberOfPlayersOnline = f;
	}
	
	void SetNumberOfPlayersOnlineXbox(int f)
	{
		m_iNumberOfPlayersOnlineXbox = f;
	}
	
	void SetNumberOfPlayersOnlinePS(int f)
	{
		m_iNumberOfPlayersOnlinePS = f;
	}
	
	void SetNumberOfPlayersOnlinePC(int f)
	{
		m_iNumberOfPlayersOnlinePC = f;
	}

};