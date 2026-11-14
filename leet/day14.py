#1606. Find Servers That Handled Most Number of Requests
import heapq

class Solution:
    def busiestServers(self, k: int, arrival: list[int], load: list[int]) -> list[int]:
        # 'available' stores available server indices shifted to >= i
        available = list(range(k))
        # 'busy' stores tuples of (end_time, server_id)
        busy = []
        count = [0] * k
        
        for i, (start, duration) in enumerate(zip(arrival, load)):
            # 1. Free up servers that have completed their tasks by 'start'
            while busy and busy[0][0] <= start:
                _, server_id = heapq.heappop(busy)
                # Project server_id into the range [i, i + k - 1]
                heapq.heappush(available, i + (server_id - i) % k)
            
            # 2. Assign request to the next available server in circular order
            if available:
                server_id = heapq.heappop(available) % k
                heapq.heappush(busy, (start + duration, server_id))
                count[server_id] += 1
                
        max_reqs = max(count)
        return [i for i, c in enumerate(count) if c == max_reqs]