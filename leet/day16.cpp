//3789. Minimum Cost to Acquire Required Items
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long c1 = min(cost1, costBoth);
        long long c2 = min(cost2, costBoth);
        long long c_both = min((long long)costBoth, c1 + c2);
        
        long long common = min(need1, need2);
        return common * c_both + (need1 - common) * c1 + (need2 - common) * c2;
    }
};