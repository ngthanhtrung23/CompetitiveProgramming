
#include <bits/stdc++.h>
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

const int MN = 311;

int f[MN];
int x[MN];
set<int> all;

void attempt(int i, int need) {
    if (need == 0) {
        if (i == 2) return ;
        int sum = 0;
        FOR(j,1,i-1) sum ^= f[x[j]];
        all.insert(sum);
        return ;
    }
    FOR(cur,x[i-1]+1,need) {
        x[i] = cur;
        attempt(i+1, need - cur);
        x[i] = 0;
    }
}

vector<int> res;

void solve(int n) {
    if (n <= 15) {
        for(int x = 8; x >= 1; x /= 2)
            if (n >= x) {
                n -= x;
                res.push_back(x);
            }
        assert(n == 0);
        return ;
    }
    int x, y, z;
    if (n <= 29) {
        x = 3, y = 5, z = 6;
    }
    else {
        x = 3; y = 10; z = 11;
        while (x + y + z + 4 <= n) {
            y += 2;
            z += 2;
        }
    }
    res.push_back(x);
    res.push_back(y);
    res.push_back(z);
    solve(n-x - y - z);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("nonequal.in", "r", stdin);
    freopen("nonequal.out", "w", stdout);
    FOR(i,1,20) {
        all.clear();
        attempt(1, i);
        f[i] = 0;
        while (all.count(f[i])) ++f[i];
    }
    FOR(i,21,300) f[i] = i-4;

    int n;
    while (cin >> n) {
        if (f[n] == 0) {
            cout << "lose" << endl;
            continue;
        }
        cout << "win" << endl;
        res.clear();
        solve(n);

        sort(res.begin(), res.end());
        for(int x : res) cout << x << ' '; cout << endl;

        int sum = 0;
        for(int x : res) {
            sum ^= f[x];
        }
        assert(sum == 0);
    }
}
