
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()

const int MN = 200111;
int n, k;
int a[MN], b[MN];

bool check(int equal) {
    FOR(i,1,equal) {
        b[i] = a[i];
        if (i > k && b[i-k] != b[i]) return false;
    }
    FOR(i,equal+1,n) {
        if (i > k) b[i] = b[i-k];
        else {
            if (a[i] == 9) b[i] = 9;
            else b[i] = a[i] + 1;
        }
        if (b[i] < a[i]) return false;
        if (b[i] > a[i]) return true;
    }
    return true;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (cin >> n >> k) {
        string s; cin >> s; s = " " + s + " ";
        FOR(i,1,n) a[i] = s[i] - '0';

        int l = 1, r = n, res = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        cout << n << endl;
        bool bigger = false;
        FOR(i,1,n) {
            if (i <= res) b[i] = a[i];
            else {
                if (i > k) b[i] = b[i-k];
                else {
                    if (bigger) {
                        b[i] = 0;
                    } else {
                        if (a[i] == 9) b[i] = 9;
                        else {
                            b[i] = a[i] + 1;
                            bigger = true;
                        }
                    }
                }
            }
            cout << b[i];
        }
        cout << endl;
    }
    return 0;
}
