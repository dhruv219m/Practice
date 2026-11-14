class Solution(object):
    def uniquePaths(self, grid):
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        
        # Helper to simulate reflection chain until landing on 0, reaching end, or falling out of bounds
        def step(r, c, direction):
            while 0 <= r < m and 0 <= c < n:
                if (r, c) == (m - 1, n - 1) or grid[r][c] == 0:
                    return (r, c)
                
                # Reflected before entering cell (r, c)
                if direction == 'R':
                    r += 1
                    direction = 'D'
                else:
                    c += 1
                    direction = 'R'
                    
            return None

        dp = [[0] * n for _ in range(m)]
        dp[m - 1][n - 1] = 1

        for r in range(m - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                # Skip mirrors and the destination cell itself
                if grid[r][c] == 1 or (r == m - 1 and c == n - 1):
                    continue

                total_paths = 0

                # 1. Try moving Right to (r, c + 1)
                dest_right = step(r, c + 1, 'R')
                if dest_right is not None:
                    total_paths = (total_paths + dp[dest_right[0]][dest_right[1]]) % MOD

                # 2. Try moving Down to (r + 1, c)
                dest_down = step(r + 1, c, 'D')
                if dest_down is not None:
                    total_paths = (total_paths + dp[dest_down[0]][dest_down[1]]) % MOD

                dp[r][c] = total_paths

        return dp[0][0]