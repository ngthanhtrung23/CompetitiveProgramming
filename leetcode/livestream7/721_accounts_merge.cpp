struct DSU {
    vector<int> parent;
    int n;
    
    DSU(int _n) {
        n = _n;
        parent = vector<int> (n, -1);
    }
    
    int getRoot(int u) {
        if (parent[u] < 0) return u;
        
        return parent[u] = getRoot(parent[u]);
    }
    
    void merge(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return;
        
        if (u > v) swap(u, v);
        
        // u < v
        parent[v] = u;
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        map<string, vector<int>> emailToIds;
        int n = accounts.size();
        for (int i = 0; i < n; i++) {
            auto& account = accounts[i];
            for (int j = 1; j < account.size(); j++) {
                string email = account[j];
                emailToIds[email].push_back(i);
            }
        }
        
        DSU dsu(n);
        for (auto& [email, ids] : emailToIds) {
            for (int i = 0; i+1 < (int) ids.size(); i++) {
                dsu.merge(ids[i], ids[i+1]);
            }
        }
        
        vector<vector<string>> res;
        for (int i = 0; i < n; i++) {
            if (dsu.getRoot(i) != i) continue;
            
            set<string> emails;
            for (int j = i; j < n; j++) {
                if (dsu.getRoot(j) == i) {
                    for (int emailId = 1;
                         emailId < accounts[j].size();
                         emailId++) {
                        emails.insert(accounts[j][emailId]);
                    }
                }
            }
            vector<string> account;
            account.push_back(accounts[i][0]);
            for (const auto& email : emails) {
                account.push_back(email);
            }
            res.push_back(account);
        }
        return res;
    }
};
