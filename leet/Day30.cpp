//3934. Smallest Unique Subarray
#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;

class Solution {
    static constexpr uint64_t MOD1 = 1000000007ULL;
    static constexpr uint64_t MOD2 = 1000000009ULL;
    static constexpr uint64_t BASE1 = 1315423911ULL;
    static constexpr uint64_t BASE2 = 2654435761ULL;

    bool hasUniqueOfLen(int n, int len,
                        const vector<uint64_t>& p1, const vector<uint64_t>& p2,
                        const vector<uint64_t>& h1, const vector<uint64_t>& h2) {
        if (len > n) return false;

        unordered_map<uint64_t, int> freq;
        freq.reserve(static_cast<size_t>(n - len + 1) * 2);

        for (int i = 0; i + len <= n; ++i) {
            uint64_t x1 = (h1[i + len] + MOD1 - (h1[i] * p1[len]) % MOD1) % MOD1;
            uint64_t x2 = (h2[i + len] + MOD2 - (h2[i] * p2[len]) % MOD2) % MOD2;
            uint64_t key = (x1 << 32) | x2;
            ++freq[key];
        }

        for (int i = 0; i + len <= n; ++i) {
            uint64_t x1 = (h1[i + len] + MOD1 - (h1[i] * p1[len]) % MOD1) % MOD1;
            uint64_t x2 = (h2[i + len] + MOD2 - (h2[i] * p2[len]) % MOD2) % MOD2;
            uint64_t key = (x1 << 32) | x2;
            if (freq[key] == 1) {
                return true;
            }
        }
        return false;
    }

public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n <= 1) return n;

        vector<uint64_t> p1(n + 1, 1), p2(n + 1, 1);
        vector<uint64_t> h1(n + 1, 0), h2(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            uint64_t val = static_cast<uint64_t>(nums[i]) + 1ULL;
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
            h1[i + 1] = (h1[i] * BASE1 + val) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + val) % MOD2;
        }

        int lo = 1, hi = n, ans = n;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUniqueOfLen(n, mid, p1, p2, h1, h2)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};
