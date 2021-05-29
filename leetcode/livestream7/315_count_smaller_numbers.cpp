const int MAX_VAL = 10000;
struct Fenwick {
    vector<int> f;
    
    Fenwick() {
        f = vector<int> (2 * MAX_VAL + 10);
    }
    
    void update(int u) {
        for (int v = u; v < (int) f.size(); v += v&-v) {
            f[v]++;
        }
    }
    
    int get(int u) {
        int res = 0;
        for (int v = u; v > 0; v -= v&-v) {
            res += f[v];
        }
        return res;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.empty()) return {};
        
        // make sure all numbers are positive
        for (int& num : nums) {
            num += MAX_VAL + 1;
        }
        
        // count
        vector<int> res(nums.size(), 0);
        Fenwick f;
        
        for (int i = ((int) nums.size()) - 1; i >= 0; i--) {
            res[i] = f.get(nums[i] - 1);
            f.update(nums[i]);
        }
        
        return res;
    }
};

