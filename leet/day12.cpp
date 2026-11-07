//1882. Process Tasks Using Servers
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdint>

using namespace std;

// Fast I/O block
static const auto fast_io = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

struct BusyServer {
    int64_t free_time;
    uint64_t server_key; // Packed (weight << 32) | index

    // Min-heap ordering: sort primarily by free_time, then server_key
    bool operator>(const BusyServer& other) const {
        if (free_time != other.free_time) {
            return free_time > other.free_time;
        }
        return server_key > other.server_key;
    }
};

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        const int n = servers.size();
        const int m = tasks.size();
        
        vector<int> ans(m);

        // Under-the-hood vector for free_servers with linear-time heapify
        vector<uint64_t> free_vec;
        free_vec.reserve(n);
        for (int i = 0; i < n; ++i) {
            free_vec.push_back(((uint64_t)servers[i] << 32) | (uint32_t)i);
        }

        // Min-heap of free servers (weight, index) packed in uint64_t
        priority_queue<uint64_t, vector<uint64_t>, greater<uint64_t>> free_pq(
            greater<uint64_t>(), std::move(free_vec)
        );

        // Min-heap of busy servers
        priority_queue<BusyServer, vector<BusyServer>, greater<BusyServer>> busy_pq;

        int64_t curr_time = 0;

        for (int j = 0; j < m; ++j) {
            if ((int64_t)j > curr_time) {
                curr_time = j;
            }

            // If no servers are available, jump time directly to the earliest finishing server
            if (free_pq.empty()) {
                curr_time = busy_pq.top().free_time;
            }

            // Release all servers done by curr_time
            while (!busy_pq.empty() && busy_pq.top().free_time <= curr_time) {
                free_pq.push(busy_pq.top().server_key);
                busy_pq.pop();
            }

            // Pick the best available server
            uint64_t best_server = free_pq.top();
            free_pq.pop();

            // Extract the original server index (lower 32 bits)
            ans[j] = (int)(best_server & 0xFFFFFFFFULL);

            // Re-insert into busy queue
            busy_pq.push({curr_time + tasks[j], best_server});
        }

        return ans;
    }
};