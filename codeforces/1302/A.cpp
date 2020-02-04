#include<bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 0, _n = n; i < _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }

using Row = std::vector<int>;
using Matrix = std::vector<Row>;
int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    size_t nRow, nCol;
    std::cin >> nRow >> nCol;
    // Bug: swap nRow and nCol
    std::swap(nRow, nCol);
    Matrix a(nRow, Row(nCol));

    for (size_t i = 0; i < nRow; i++) {
        for (size_t j = 0; j < nCol; j++) {
            std::cin >> a[i][j];
        }
    }

    Row maxRow(nRow), cntMaxRow(nRow);
    Row minCol(nCol, std::numeric_limits<int>::max()), cntMinCol(nCol);

    for (size_t i = 0; i < nRow; i++) {
        for (size_t j = 0; j < nCol; j++) {
            maxRow[i] = std::max(maxRow[i], a[i][j]);
            minCol[j] = std::min(minCol[j], a[i][j]);
        }
    }
    for (size_t i = 0; i < nRow; i++) {
        for (size_t j = 0; j < nCol; j++) {
            if (a[i][j] == maxRow[i]) {
                ++cntMaxRow[i];
            }
            if (a[i][j] == minCol[j]) {
                ++cntMinCol[j];
            }
        }
    }

    for (size_t i = 0; i < nRow; i++) {
        for (size_t j = 0; j < nCol; j++) {
            if (a[i][j] == minCol[j]
                    && cntMinCol[j] == 1
                    && a[i][j] == maxRow[i]
                    && cntMaxRow[i] == 1) {
                std::cout << i + 1 << ' ' << j + 1 << std::endl;
                return 0;
            }
        }
    }

    // No answer.
    std::cout << 0 << ' ' << 0 << std::endl;
}
