#1385. Find the Distance Value Between Two Arrays
import bisect

class Solution:
    def findTheDistanceValue(self, arr1: list[int], arr2: list[int], d: int) -> int:
        arr2.sort()
        count = 0
        
        for x in arr1:
            # Find the leftmost index where arr2[idx] >= x - d
            idx = bisect.bisect_left(arr2, x - d)
            
            # If idx is within bounds and arr2[idx] <= x + d, a violating element exists
            if idx < len(arr2) and arr2[idx] <= x + d:
                continue
            
            count += 1
            
        return count