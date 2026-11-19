#2567. Minimum Score by Changing Two Elements
import heapq

class Solution:
    def minimizeSum(self, nums: list[int]) -> int:
        if len(nums) <= 3:
            return 0
        
        # min1 <= min2 <= min3
        min1, min2, min3 = heapq.nsmallest(3, nums)
        # max1 >= max2 >= max3
        max1, max2, max3 = heapq.nlargest(3, nums)
        
        return min(max3 - min1, max1 - min3, max2 - min2)
