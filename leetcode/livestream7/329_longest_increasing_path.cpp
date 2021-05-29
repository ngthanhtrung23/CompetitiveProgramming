template<typename T>
using Matrix = vector<vector<T>>;

class Solution {
private:
    Matrix<int> f;
    int nRow, nCol;

public:
    int longestIncreasingPath(Matrix<int>& matrix) {
        if (matrix.empty()) return 0;

        nRow = matrix.size();
        nCol = matrix[0].size();
        f = Matrix<int> (nRow, vector<int> (nCol, -1));
        
        int res = 0;
        for (int row = 0; row < nRow; row++) {
            for (int col = 0; col < nCol; col++) {
                res = max(res, getF(row, col, matrix, f));
            }
        }
        return res;
    }

private:
    int getF(int row, int col, const Matrix<int>& matrix, Matrix<int>& f) {
        if (f[row][col] > -1) return f[row][col];
        
        int res = 1;
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di*di + dj*dj == 1) {
                    int nextRow = row + di;
                    int nextCol = col + dj;
                    if (nextRow < 0 || nextRow >= nRow
                       || nextCol < 0 || nextCol >= nCol) {
                        continue;
                    }
                    
                    if (matrix[nextRow][nextCol] > matrix[row][col]) {
                        res = max(res, 1 + getF(nextRow, nextCol, matrix, f));
                    }
                }
            }
        }
        return f[row][col] = res;
    }
};
