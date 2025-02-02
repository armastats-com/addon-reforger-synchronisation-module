class AS_RandomStringGenerator {
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