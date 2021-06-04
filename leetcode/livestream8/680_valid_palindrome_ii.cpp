class Solution:
    def validPalindrome(self, s: str) -> bool:
        if self.isPalin(s):
            return True
        
        i = 0
        j = len(s) - 1
        while i < j:
            if s[i] != s[j]:
                if self.isPalin(s[:i] + s[i+1:]):
                    return True
                
                if self.isPalin(s[:j] + s[j+1:]):
                    return True
                
                return False
            i += 1
            j -= 1
        
        return False
        
    
    def isPalin(self, s: str) -> bool:
        r = s[::-1]
        return r == s
