//3693. Climbing Stairs II
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        // Use a safe infinity value that won't overflow when adding 9
        const int INF = 1e9;
        int dp1 = 0, dp2 = INF, dp3 = INF;
        
        for (int c : costs) {
            int curr = c + min({dp1 + 1, dp2 + 4, dp3 + 9});
            dp3 = dp2;
            dp2 = dp1;
            dp1 = curr;
        }
        
        return dp1;
    }
};