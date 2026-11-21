#3331. Find Subtree Sizes After Changes
class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)

        children = [[] for _ in range(n)]

        for i in range(1, n):
            children[parent[i]].append(i)

        last = [-1] * 26
        old = [-1] * n
        new_parent = [-1] * n

        stack = [(0, 0)]

        # First DFS: determine new parents
        while stack:
            node, state = stack.pop()
            c = ord(s[node]) - 97

            if state == 0:
                old[node] = last[c]

                p = last[c]
                if p == -1:
                    p = parent[node]

                new_parent[node] = p

                last[c] = node
                stack.append((node, 1))

                for child in reversed(children[node]):
                    stack.append((child, 0))

            else:
                last[c] = old[node]

        # Build modified tree
        new_children = [[] for _ in range(n)]

        for i in range(1, n):
            new_children[new_parent[i]].append(i)

        # Second DFS: get traversal order
        order = [0]

        for node in order:
            for child in new_children[node]:
                order.append(child)

        # Calculate subtree sizes
        ans = [1] * n

        for node in reversed(order[1:]):
            ans[new_parent[node]] += ans[node]

        return ans
