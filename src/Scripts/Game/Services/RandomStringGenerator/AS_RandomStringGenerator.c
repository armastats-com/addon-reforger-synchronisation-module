//------------------------------------------------------------------------------------------------
//! Helper Class for Random Strings
class AS_RandomStringGenerator {
	
	//------------------------------------------------------------------------------------------------
	// Creates and returns a random string for a given length
    static string GenerateRandomString(int length) {
        string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
        string result = "";
        int charsLength = chars.Length();
        
        for (int i = 0; i < length; i++) {
            int randomIndex = Math.RandomInt(0, charsLength);
            result += chars[randomIndex];
        }
        
        return result;
    }
}