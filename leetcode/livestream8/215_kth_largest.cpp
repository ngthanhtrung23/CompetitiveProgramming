class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        k = nums.size() - k;
        std::nth_element(nums.begin(), nums.begin() + k, nums.end());
        return nums[k];
    }
}
