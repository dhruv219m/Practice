//462. Minimum Moves to Equal Array Elements II
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        // Find the median using nth_element (O(N) time instead of O(N log N) sort)
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        int median = nums[n / 2];
        
        int moves = 0;
        for (int num : nums) {
            moves += abs(num - median);
        }
        
        return moves;
    }
};
