//1524. Number of Sub-arrays With Odd Sum
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        long long total = 0;
        int even_count = 1; // Empty prefix sum (0) is even
        int odd_count = 0;
        int parity = 0;

        for (int num : arr) {
            parity ^= (num & 1);
            if (parity) {
                total += even_count;
                odd_count++;
            } else {
                total += odd_count;
                even_count++;
            }
        }

        return total % MOD;
    }
};
