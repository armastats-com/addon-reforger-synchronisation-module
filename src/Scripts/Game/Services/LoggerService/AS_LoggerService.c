class AS_LoggerService
{
    protected const string pre = "[ArmaStats.com] ";

	static void Log(string s)
	{
		Print(pre + s);
	}
	
	static void Debug(string s)
	{
		Print(pre + s, LogLevel.DEBUG);
	}

	static void Error(string s)
	{
		Print(pre + s, LogLevel.ERROR);
	}
}
