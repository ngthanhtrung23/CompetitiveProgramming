class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        if (words.empty()) return {};

        int i = 0;
        int n = words.size();
        vector<string> res;
        while (i < n) {
            int j = i;
            int total = words[i].size();
            
            while (j + 1 < n && total + 1 + words[j+1].size() <= maxWidth) {
                j++;
                total += 1 + words[j].size();
            }
            
            // insert words in [i, j]
            string cur = "";  // current line
            if (i == j) {
                // case 1: line has 1 word
                cur = words[i];
                cur += whitespace(maxWidth - words[i].size());
            } else if (j == n - 1) {
                // case 2: last line
                cur = words[i];
                for (int x = i+1; x <= j; x++) {
                    cur += ' ';
                    cur += words[x];
                }
                cur += whitespace(maxWidth - cur.size());
            } else {
                // case 3: insert spaces between
                int sumLength = 0;
                for (int x = i; x <= j; x++) {
                    sumLength += words[x].size();
                }

                int extraSpaces = maxWidth - sumLength;
                int nGaps = j - i;

                // initialize spaces
                vector<string> spaces;
                for (int x = 0; x < nGaps; x++) {
                    int nSpace = extraSpaces / nGaps;
                    
                    if (x < extraSpaces % nGaps) {
                        ++nSpace;
                    }
                    spaces.push_back(whitespace(nSpace));
                }
                
                cur = words[i];
                for (int x = i + 1; x <= j; x++) {
                    cur += spaces[x - i - 1];
                    cur += words[x];
                }
            }
            res.push_back(cur);
            
            i = j + 1;
        }
        
        return res;
    }
   
private:
    string whitespace(int n) {
        string res = "";
        while (n--) {
            res += ' ';
        }
        return res;
    }
};
