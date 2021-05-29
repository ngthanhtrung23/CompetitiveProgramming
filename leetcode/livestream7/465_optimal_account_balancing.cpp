int f[1<<21];
int balances[21];
int sum[1<<21]; // subset-sum
int n;

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        // If 1 group sum = 0 with x people -> x-1 transactions
        // -> DP O(3^n)
        
        memset(balances, 0, sizeof balances);
        n = 0;
        for (const auto& trans : transactions) {
            balances[trans[0]] += trans[2];
            balances[trans[1]] -= trans[2];
            
            n = max(n, trans[0]);
            n = max(n, trans[1]);
        }
        ++n;
        
        // initialize subset sum
        for (int mask = 0; mask < (1<<n); mask++) {
            sum[mask] = 0;
            for (int i = 0; i < n; i++) {
                if ((mask >> i) & 1) {
                    sum[mask] += balances[i];
                }
            }
        }
        
        memset(f, -1, sizeof f);
        return solve((1<<n) - 1);
    }
    
    // we still need to settle people contained in mask
    int solve(int mask) {
        if (__builtin_popcount(mask) < 2) return 0;
        if (f[mask] >= 0) return f[mask];
        assert(sum[mask] == 0);
        
        int res = __builtin_popcount(mask) - 1;
        for(int i = mask; i > 0; i = (i-1) & mask) {
            // i is a subset of mask
            if (sum[i] == 0 && i < mask) {
                res = min(res, __builtin_popcount(mask - i) - 1 + solve(i));
            }
        }
        return f[mask] = res;
    }

};
