template<typename T>
using Matrix = vector<vector<T>>;

class Solution {
private:
    int nRow, nCol;

public:
    int maxAreaOfIsland(Matrix<int>& grid) {
        nRow = grid.size();
        nCol = grid[0].size();
        
        Matrix<bool> visited(nRow, vector<bool> (nCol, false));
        int res = 0;
        for (int i = 0; i < nRow; i++) {
            for (int j = 0; j < nCol; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    res = max(res, bfs(i, j, grid, visited));
                }
            }
        }
        return res;
    }
   
    int bfs(int startu, int startv, const Matrix<int>& grid, Matrix<bool>& visited) {
        int res = 0;
        queue< pair<int,int> > qu;
        qu.push({startu, startv});
        visited[startu][startv] = true;
        
        while (!qu.empty()) {
            auto [u, v] = qu.front();
            qu.pop();
            ++res;
            
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di*di + dj*dj == 1) {
                        int uu = u + di;
                        int vv = v + dj;
                        if (uu < 0 || uu >= nRow || vv < 0 || vv >= nCol) continue;
                        if (grid[uu][vv] != 1) continue;
                        if (visited[uu][vv]) continue;
                        
                        visited[uu][vv] = true;
                        qu.push({uu, vv});
                    }
                }
            }
        }
        
        return res;
    }
};
