//3946. Maximum Number of Items From Sale I
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        const int MAX_F = 1500;
        vector<int> freq(MAX_F + 1, 0);
        int min_price = 1e9;

        for (const auto& item : items) {
            freq[item[0]]++;
            min_price = min(min_price, item[1]);
        }

        // total_div[f] = number of items j whose factor_j is divisible by f
        vector<int> total_div(MAX_F + 1, 0);
        for (int f = 1; f <= MAX_F; ++f) {
            if (freq[f] == 0) continue;
            for (int m = f; m <= MAX_F; m += f) {
                total_div[f] += freq[m];
            }
        }

        // 0/1 Knapsack for the first copy of each item
        vector<int> dp(budget + 1, -1e9);
        dp[0] = 0;

        for (const auto& item : items) {
            int f = item[0], p = item[1];
            int gain = total_div[f];
            for (int c = budget; c >= p; --c) {
                if (dp[c - p] != -1e9) {
                    dp[c] = max(dp[c], dp[c - p] + gain);
                }
            }
        }

        // Spend any leftover budget on the cheapest item (1 copy per min_price)
        int ans = 0;
        for (int c = 0; c <= budget; ++c) {
            if (dp[c] != -1e9) {
                ans = max(ans, dp[c] + (budget - c) / min_price);
            }
        }

        return ans;
    }
};

