#include <bits/stdc++.h>
using namespace std;

int n, c[11][11];

int readCol(int i, int j, int n) {
    j <= n ? (cin >> c[i][j], readCol(i, j+1, n)) : 1;
}

int readRow(int i, int n) {
    i <= n ? (readCol(i, 1, n), readRow(i+1, n)) : 1;
}

int floydJ(int k, int i, int j, int n) {
    j <= n ? (c[i][j] = min(c[i][j], c[i][k] + c[k][j]), floydJ(k, i, j+1, n)) : 1;
}

int floydI(int k, int i, int n) {
    i <= n ? (floydJ(k, i, 1, n), floydI(k, i+1, n)) : 1;
}

int floydK(int k, int n) {
    k <= n ? (floydI(k, 1, n), floydK(k+1, n)) : 1;
}

int getCol(int i, int j, int n) {
    return j <= n ? max(c[i][j], getCol(i, j+1, n)) : 0;
}

int getRow(int i, int n) {
    return i <= n ? max(getCol(i, 1, n), getRow(i+1, n)) : 0;
}

int main() {
    cin >> n;
    readRow(1, n);

    floydK(1, n);

    int res = getRow(1, n);
    cout << res << endl;
}
