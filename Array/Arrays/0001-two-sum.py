
# Problem: Two Sum
# LeetCode: https://leetcode.com/problems/two-sum/
# Difficulty: Easy
#
# Approach: Hash Map
# Time Complexity: O(n)
# Space Complexity: O(n)

class Solution:
    def twoSum(self, nums, target):
        seen = {}

        for i, num in enumerate(nums):
            complement = target - num

            if complement in seen:
                return [seen[complement], i]

            seen[num] = i