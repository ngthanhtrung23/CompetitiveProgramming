// Algo: prefix sum & sweep

#include <bits/stdc++.h>
using namespace std;

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

const int N = 5011;
int a[N][N], col[N][N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    FOR(i,1,n) FOR(j,1,n) {
        cin >> a[i][j];
        col[i][j] = a[i][j] + col[i-1][j];
    }

    FOR(i,1,n) FOR(j,1,n) {
        a[i][j] += a[i-1][j+1];
    }

    auto diag = [&] (int r1, int c1, int r2, int c2) {
        assert(r1 + c1 == r2 + c2);
        assert(r1 <= r2);
        return a[r2][c2] - a[r1-1][c1+1];
    };

    long long res = 0;
    FOR(r,1,n-k+1) {
        long long cur = 0;
        FOR(d,0,k-1) {
            cur += diag(r, 1+d, r+d, 1);
        }
        upMax(res, cur);

        FOR(c,2,n-k+1) {
            cur -= col[r+k-1][c-1] - col[r-1][c-1];
            cur += diag(r, c+k-1, r+k-1, c);
            upMax(res, cur);
        }
    }
    cout << res << endl;
    return 0;
}
