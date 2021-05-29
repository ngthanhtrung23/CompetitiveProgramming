/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        random_shuffle(wordlist.begin(), wordlist.end());
        vector<bool> can(wordlist.size(), true);
        
        for (int i = 0; i < wordlist.size(); i++) {
            if (!can[i]) continue;
            
            int guess = master.guess(wordlist[i]);
            if (guess == wordlist[i].size()) {
                // found result
                return;
            }
            
            for (int j = i + 1; j < wordlist.size(); j++) {
                if (match(wordlist[i], wordlist[j]) != guess) {
                    can[j] = false;
                }
            }
        }
    }

private:
    int match(const string& a, const string& b) {
        int res = 0;
        for (int i = 0; i < a.size(); i++) {
            res += a[i] == b[i];
        }
        return res;
    }
};
