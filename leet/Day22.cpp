//2911. Minimum Changes to Make K Semi-palindromes
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        
        // 1. Precompute proper divisors for every possible substring length L (2 <= L <= n)
        vector<vector<int>> divisors(n + 1);
        for (int L = 2; L <= n; ++L) {
            for (int d = 1; d * d <= L; ++d) {
                if (L % d == 0) {
                    if (d < L) divisors[L].push_back(d);
                    int other = L / d;
                    if (other != d && other < L) divisors[L].push_back(other);
                }
            }
        }

        // 2. Precompute cost[i][j]: min changes to make s[i..j] a semi-palindrome
        const int INF = 1e9;
        vector<vector<int>> cost(n, vector<int>(n, INF));

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int L = j - i + 1;
                int min_changes = INF;

                for (int d : divisors[L]) {
                    int changes = 0;
                    int group_len = L / d;
                    // Check each of the d interleaved groups
                    for (int rem = 0; rem < d; ++rem) {
                        int left = i + rem;
                        int right = i + rem + (group_len - 1) * d;
                        while (left < right) {
                            if (s[left] != s[right]) {
                                ++changes;
                            }
                            left += d;
                            right -= d;
                        }
                    }
                    min_changes = min(min_changes, changes);
                }
                cost[i][j] = min_changes;
            }
        }

        // 3. Partition DP: dp[i] = min changes for prefix s[0..i-1] with current number of parts
        vector<int> dp(n + 1, INF);
        dp[0] = 0;

        for (int p = 1; p <= k; ++p) {
            vector<int> next_dp(n + 1, INF);
            // Each partition needs at least length 2, so prefix length i >= 2 * p
            for (int i = 2 * p; i <= n; ++i) {
                for (int j = 2 * (p - 1); j <= i - 2; ++j) {
                    if (dp[j] != INF) {
                        next_dp[i] = min(next_dp[i], dp[j] + cost[j][i - 1]);
                    }
                }
            }
            dp = move(next_dp);
        }

        return dp[n];
    }
};
