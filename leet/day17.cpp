//3105. Longest Strictly Increasing or Strictly Decreasing Subarray
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int inc = 1, dec = 1, max_len = 1;
        int n = nums.size();
        
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                max_len = max(max_len, ++inc);
                dec = 1;
            } else if (nums[i] < nums[i - 1]) {
                max_len = max(max_len, ++dec);
                inc = 1;
            } else {
                inc = 1;
                dec = 1;
            }
        }
        
        return max_len;
    }
};