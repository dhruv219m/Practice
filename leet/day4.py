
class Solution:
    def shortestPath(self, n, edges, labels, k):
        import heapq

        graph = [[] for _ in range(n)]

        for u, v, w in edges:
            graph[u].append((v, w))

        INF = float('inf')
        dist = [[INF] * (k + 1) for _ in range(n)]

        dist[0][1] = 0
        pq = [(0, 0, 1)]

        while pq:
            cost, u, count = heapq.heappop(pq)

            if cost != dist[u][count]:
                continue

            if u == n - 1:
                return cost

            for v, w in graph[u]:
                if labels[u] == labels[v]:
                    nc = count + 1
                else:
                    nc = 1

                if nc > k:
                    continue

                new_cost = cost + w

                if new_cost < dist[v][nc]:
                    dist[v][nc] = new_cost
                    heapq.heappush(pq, (new_cost, v, nc))

        return -1
