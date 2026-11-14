//" Count Zero Request Servers
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = logs.size();
        int q_len = queries.size();

        // 1. Pack logs into uint64_t: (time << 32) | server_id
        // Time naturally sorts first in ascending order.
        vector<uint64_t> packed_logs(m);
        for (int i = 0; i < m; ++i) {
            packed_logs[i] = ((uint64_t)logs[i][1] << 32) | (uint32_t)logs[i][0];
        }
        sort(packed_logs.begin(), packed_logs.end());

        // 2. Pack queries into uint64_t: (q_time << 32) | original_index
        vector<uint64_t> packed_queries(q_len);
        for (int i = 0; i < q_len; ++i) {
            packed_queries[i] = ((uint64_t)queries[i] << 32) | (uint32_t)i;
        }
        sort(packed_queries.begin(), packed_queries.end());

        vector<int> ans(q_len);
        vector<int> server_count(n + 1, 0);
        int active_servers = 0;
        int left = 0, right = 0;

        // Mask for extracting lower 32 bits
        const uint64_t MASK_32 = 0xFFFFFFFFULL;

        for (int i = 0; i < q_len; ++i) {
            uint64_t q_entry = packed_queries[i];
            int q_time = q_entry >> 32;
            int original_idx = q_entry & MASK_32;
            int window_start = q_time - x;

            // Expand right pointer
            while (right < m && (packed_logs[right] >> 32) <= (uint64_t)q_time) {
                int s_id = packed_logs[right] & MASK_32;
                if (++server_count[s_id] == 1) {
                    active_servers++;
                }
                right++;
            }

            // Shrink left pointer
            while (left < m && (packed_logs[left] >> 32) < (uint64_t)window_start) {
                int s_id = packed_logs[left] & MASK_32;
                if (--server_count[s_id] == 0) {
                    active_servers--;
                }
                left++;
            }

            ans[original_idx] = n - active_servers;
        }

        return ans;
    }
};"