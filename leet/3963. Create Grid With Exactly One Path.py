
class Solution:
    def createGrid(self, m, n):
        return ["." * n] + ["#" * (n - 1) + "." for _ in range(m - 1)]
