#3814
class Solution:
    def palindromePath(self, n, edges, s, queries):
        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        # Each character is represented by one bit.
        chars = [1 << (ord(c) - 97) for c in s]

        LOG = n.bit_length()
        up = [[0] * n for _ in range(LOG)]
        depth = [0] * n
        tin = [0] * n
        tout = [0] * n
        base = [0] * n

        # Iterative DFS: Euler tour, root-prefix masks,
        # depths and binary-lifting ancestor table.
        timer = 0
        stack = [(0, 0, False)]

        while stack:
            u, p, exiting = stack.pop()

            if exiting:
                tout[u] = timer - 1
                continue

            depth[u] = 0 if u == 0 else depth[p] + 1
            up[0][u] = p

            for k in range(1, LOG):
                up[k][u] = up[k - 1][up[k - 1][u]]

            base[u] = chars[u] if u == 0 else base[p] ^ chars[u]

            tin[u] = timer
            timer += 1

            stack.append((u, p, True))

            for v in graph[u]:
                if v != p:
                    stack.append((v, u, False))

        # Binary lifting for Lowest Common Ancestor.
        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u

            diff = depth[u] - depth[v]
            k = 0

            while diff:
                if diff & 1:
                    u = up[k][u]
                diff >>= 1
                k += 1

            if u == v:
                return u

            for k in range(LOG - 1, -1, -1):
                if up[k][u] != up[k][v]:
                    u = up[k][u]
                    v = up[k][v]

            return up[0][u]

        # Fenwick tree supporting range XOR updates
        # and point XOR queries.
        bit = [0] * (n + 2)

        def add(i, value):
            while i <= n + 1:
                bit[i] ^= value
                i += i & -i

        def prefix(i):
            result = 0
            while i > 0:
                result ^= bit[i]
                i -= i & -i
            return result

        # Current root-to-node parity mask.
        def root_mask(u):
            return base[u] ^ prefix(tin[u] + 1)

        ans = []

        for query in queries:
            parts = query.split()

            if parts[0] == "update":
                u = int(parts[1])
                new_mask = 1 << (ord(parts[2]) - 97)
                delta = chars[u] ^ new_mask

                if delta:
                    # Updating a node affects the root-prefix
                    # mask of every node in its subtree.
                    add(tin[u] + 1, delta)
                    add(tout[u] + 2, delta)
                    chars[u] = new_mask

            else:
                u = int(parts[1])
                v = int(parts[2])
                w = lca(u, v)

                # XOR of characters on the complete path.
                path_mask = (
                    root_mask(u)
                    ^ root_mask(v)
                    ^ chars[w]
                )

                # A palindrome permutation allows at most
                # one character with an odd frequency.
                ans.append(
                    (path_mask & (path_mask - 1)) == 0
                )

        return ans
