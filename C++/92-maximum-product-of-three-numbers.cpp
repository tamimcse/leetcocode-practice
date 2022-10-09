/*
https://leetcode.com/problems/maximum-product-of-three-numbers/
*/
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int len = nums.size();
        
        if (nums.back() > 0) {
            return max (nums[0] * nums[1] * nums.back(), 
                        nums[len - 1] * nums[len - 2] * nums[len - 3]);
        } else {
            return nums[len - 1] * nums[len - 2] * nums[len - 3];
        }
    }
};
