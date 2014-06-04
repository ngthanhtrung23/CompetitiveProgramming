#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n, k, p, a[MN];
int nEven, even[MN], nOdd, odd[MN];
vector<int> res1[MN], res2[MN];

void init() {
    nEven = nOdd = 0;
}

#define NO { cout << "NO\n"; return ; }

void solve() {
    // PR(even, nEven);
    // PR(odd, nOdd);
    if (nOdd < k-p) NO;
    if ((nOdd - (k-p)) % 2) NO;

    FOR(i,1,p) res2[i].clear();
    FOR(i,1,k-p) res1[i].clear();

    FOR(i,1,k-p) {
        res1[i].push_back(odd[i]);
    }
    int x = 0;
    for(int i = k-p+1; i <= nOdd; i += 2) {
        if (p == 0) {
            res1[1].push_back(odd[i]);
            res1[1].push_back(odd[i+1]);
        }
        else {
            ++x; if (x > p) x = p;
            res2[x].push_back(odd[i]);
            res2[x].push_back(odd[i+1]);
        }
    }

    FOR(i,1,nEven) {
        if (p == 0) {
            res1[1].push_back(even[i]);
        }
        else {
            ++x; if (x > p) x = p;
            res2[x].push_back(even[i]);
        }
    }

    FOR(i,1,p) if (res2[i].size() == 0) NO;
    FOR(i,1,k-p) if (res1[i].size() == 0) NO;

    cout << "YES\n";
    FOR(i,1,k-p) {
        cout << res1[i].size();
        REP(x,res1[i].size()) cout << ' ' << res1[i][x]; cout << endl;
    }
    FOR(i,1,p) {
        cout << res2[i].size();
        REP(x,res2[i].size()) cout << ' ' << res2[i][x]; cout << endl;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> p) {
        init();
        FOR(i,1,n) {
            cin >> a[i];
            if (a[i] % 2 == 0) even[++nEven] = a[i];
            else odd[++nOdd] = a[i];
        }

        solve();
    }
    return 0;
}
