class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // f(i) = true iff s[i..] can be segmented
        int n = s.size();
        vector<bool> f(n + 1, false);
        
        f[n] = true;  // empty string
        for (int i = n-1; i >= 0; i--) {
            for (auto word : wordDict) {
                // aab
                // i = 1 -> ab
                // word = abc
                // --> too long
                if (i + word.size() > s.size()) continue;
                if (s.substr(i, word.size()) != word) continue;
                if (!f[i + word.size()]) continue;
                
                f[i] = true;
                break;
            }
        }
        
        return f[0];
    }
};
