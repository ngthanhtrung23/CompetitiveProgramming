class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        if (words.size() <= 1) {
            return true;
        }

        map<char, int> id;
        for (int i = 0; i < order.size(); i++) {
            id[order[i]] = i;
        }
        
        for (int i = 0; i + 1 < words.size(); i++) {
            if (!isLower(words[i], words[i+1], id)) {
                return false;
            }
        }
        return true;
    }

private:
    bool isLower(const string& a, const string& b, map<char, int>& id) {
        for (int i = 0; i < (int) min(a.size(), b.size()); i++) {
            if (a[i] != b[i]) {
                return id[a[i]] < id[b[i]];
            }
        }
        return a.size() <= b.size();
    }
};
