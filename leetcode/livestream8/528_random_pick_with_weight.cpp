class Solution {
public:
    Solution(vector<int>& _w) : w(_w) {
        // 0, 1, 2, 3, .., n-1
        // 0, 0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3...
        // dice
        sum = std::accumulate(w.begin(), w.end(), 0);
    }
    
    // O(N)
    // Can optimize to O(log(N)) by using partial_sum
    int pickIndex() {
        int dice = rand() % sum;
        int cur = 0;
        for (int i = 0; i < w.size(); i++) {
            cur += w[i];
            if (cur > dice) return i;
        }
        assert(false);
    }

private:
    vector<int> w;
    int sum;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
