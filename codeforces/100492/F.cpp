
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n;
string s;
int x[44];

bool isGood(int i) {
    for(int k = 1; i + 2*k - 1 <= n; ++k) {
        if (s.substr(i, k) == s.substr(i+k, k)) return false;
    }
    return true;
}

bool check() {
    FOR(i,1,n) x[i] = isGood(i);
    FOR(i,1,n) x[i] += x[i-1];

    FOR(i,1,n) if (2*x[i] < i) return false;
    return true;
}

vector<string> res[44];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("free.in", "r", stdin);
    freopen("free.out", "w", stdout);

    res[0].push_back(" ");
    FOR(i,1,40) {
        n = i;
        for(auto t : res[i-1]) {
            s = t + "0";
            if (check()) res[i].push_back(s);

            s = t + "1";
            if (check()) res[i].push_back(s);
        }
    }

    while (cin >> n) {
        cout << SZ(res[n]) << endl;
        for(auto s : res[n]) {
            cout << s.substr(1) << '\n';
        }
        cout << endl;
    }
}
