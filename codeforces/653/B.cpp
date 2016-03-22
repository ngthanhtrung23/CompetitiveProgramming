
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

const int MN = 66;
string a[MN], b[MN];
int n, q;

int compress(string s) {
    while (SZ(s) > 1) {
        bool can = true;
        FOR(i,1,q) {
            if (a[i][0] == s[0] && a[i][1] == s[1]) {
                s = b[i] + s.substr(2);
                can = false;
                break;
            }
        }
        if (can) break;
    }
    return SZ(s) == 1 && s[0] == 'a';
}

int res = 0;

void attempt(int i, string cur) {
    if (i > n) {
        if (compress(cur) == 1) {
            ++res;
        }
        return ;
    }
    FOR(c,'a','f') {
        string next = cur;
        next += c;

        attempt(i+1, next);
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> q) {
        FOR(i,1,q) cin >> a[i] >> b[i];
        res = 0;
        attempt(1, "");
        cout << res << endl;
    }
}
