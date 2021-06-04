class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if (nums.empty()) return {};
        
        // left[i] = product(nums[0]..nums[i])
        // right[i] = product(nums[i]..nums[-1])
        int n = nums.size();
        vector<int> left(n), right(n);
        for (int i = 0; i < n; i++) {
            if (i == 0) left[i] = nums[i];
            else {
                left[i] = left[i-1] * nums[i];
            }
        }
        for (int i = n-1; i >= 0; i--) {
            if (i == n-1) right[i] = nums[i];
            else {
                right[i] = right[i+1] * nums[i];
            }
        }
        
        // result
        vector<int> res;
        for (int i = 0; i < n; i++) {
            int cur = 1;
            if (i > 0) cur *= left[i-1];
            if (i+1 < n) cur *= right[i+1];
            res.push_back(cur);
        }
        return res;
    }
};
