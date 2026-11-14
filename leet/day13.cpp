//1267. Count Servers that Communicate
#include <vector>

using namespace std;

static const auto fast_io = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        
        vector<int> rowCount(m, 0);
        vector<int> colCount(n, 0);
        
        // Pass 1: Count servers per row and column
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }
        
        int communicableServers = 0;
        
        // Pass 2: Count servers that share a row or column with another server
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && (rowCount[i] > 1 || colCount[j] > 1)) {
                    communicableServers++;
                }
            }
        }
        
        return communicableServers;
    }
};