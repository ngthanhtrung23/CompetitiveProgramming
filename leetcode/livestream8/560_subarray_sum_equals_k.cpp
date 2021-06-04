class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // sum(i) = sum(nums[0]..nums[i])
        // sum(i) - sum(j) = k
        // sum(j) = sum(i) - k
        
        vector<int> sums(nums.size());
        std::partial_sum(nums.begin(), nums.end(), sums.begin());
        
        map<int, int> cnt;
        cnt[0] = 1;
        int res = 0;  // should be int64_t
        for (int sum_i : sums) {
            int sum_j = sum_i - k;
            res += cnt[sum_j];
            
            cnt[sum_i]++;
        }
        
        return res;
    }
};
