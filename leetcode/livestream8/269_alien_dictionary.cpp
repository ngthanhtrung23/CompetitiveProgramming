class Solution {
public:
    string alienOrder(vector<string>& words) {
        set<char> all;  // all characters in all words
        for (auto word : words) {
            for (char c : word) {
                all.insert(c);
            }
        }
        
        // step 1: find restriction: char a < char b
        map<char, int> inDeg;
        map<char, vector<char>> edges;
        
        for (int i = 0; i + 1 < (int) words.size(); i++) {
            string a = words[i];
            string b = words[i+1];
            
            bool diff = false;
            for (int j = 0; j < (int) min(a.size(), b.size()); j++) {
                if (a[j] != b[j]) {
                    // add edge (a[j], b[j])
                    inDeg[b[j]]++;
                    edges[a[j]].push_back(b[j]);
                    diff = true;
                    break;
                }
            }
            
            // abc < ab
            if (!diff && a.size() > b.size()) {
                return "";
            }
        }
        
        // step 2: topo sort
        // - repeat: find vertex with in-degree = 0
        string res = "";
        while (!all.empty()) {
            char zeroInDeg = 0;
            for (char c : all) {
                if (inDeg[c] == 0) {
                    zeroInDeg = c;
                    break;
                }
            }
            if (zeroInDeg == 0) {
                // no solution
                return "";
            }
            all.erase(zeroInDeg);
            res += zeroInDeg;
            
            for (char x : edges[zeroInDeg]) {
                // delete (c, x)
                inDeg[x]--;
            }
        }
        
        return res;
    }
};
