
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int get(int n) {
    int res = 0;
    if (n < 5) return 0;
    return n / 5 + get(n / 5);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int m;
    while (cin >> m) {
        // find first number that have at least m leading zeros
        int l = 0, r = 1000111, res = 1000111;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (get(mid) >= m) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        vector<int> all;
        if (get(res) == m) {
            while (get(res) == m) {
                all.push_back(res);
                ++res;
            }
        }
        cout << SZ(all) << endl;
        for(int x : all) cout << x << ' '; cout << endl;
    }
}
