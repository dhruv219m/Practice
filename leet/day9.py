#3505. Minimum Operations to Make Elements Within K Subarrays Equal
import heapq
from typing import List

class Solution:
    def minOperations(self, nums: List[int], x: int, k: int) -> int:
        n = len(nums)
        L, R = [], []
        in_L = [False] * n
        sumL, sumR = 0, 0
        countL, countR = 0, 0
        target_L = (x + 1) // 2
        costs = []

        def prune(limit: int):
            while L and L[0][1] <= limit:
                heapq.heappop(L)
            while R and R[0][1] <= limit:
                heapq.heappop(R)

        for i, val in enumerate(nums):
            # 1. Remove outgoing element if window slides past size x
            if i >= x:
                out_idx = i - x
                out_val = nums[out_idx]
                if in_L[out_idx]:
                    sumL -= out_val
                    countL -= 1
                else:
                    sumR -= out_val
                    countR -= 1
                prune(out_idx)

            # 2. Always route through L -> R to strictly preserve max(L) <= min(R)
            heapq.heappush(L, (-val, i))
            in_L[i] = True
            sumL += val
            countL += 1

            prune(i - x)
            neg_v, idx = heapq.heappop(L)
            v = -neg_v
            sumL -= v
            countL -= 1
            heapq.heappush(R, (v, idx))
            in_L[idx] = False
            sumR += v
            countR += 1

            # 3. Balance sizes once the window has x elements
            if i >= x - 1:
                limit = i - x
                prune(limit)
                while countL < target_L:
                    prune(limit)
                    v, idx = heapq.heappop(R)
                    sumR -= v
                    countR -= 1
                    heapq.heappush(L, (-v, idx))
                    in_L[idx] = True
                    sumL += v
                    countL += 1
                    prune(limit)
                
                median = -L[0][0]
                c = (sumR - sumL + median) if (x % 2 == 1) else (sumR - sumL)
                costs.append(c)

        # 4. DP to pick k non-overlapping windows of size x
        m = len(costs)
        dp = [0] * m
        curr_min = float('inf')
        for i in range(m):
            curr_min = min(curr_min, costs[i])
            dp[i] = curr_min

        for c in range(2, k + 1):
            new_dp = [float('inf')] * m
            for i in range((c - 1) * x, m):
                new_dp[i] = min(new_dp[i - 1], dp[i - x] + costs[i])
            dp = new_dp

        return int(dp[-1])