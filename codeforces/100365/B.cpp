
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

string s;

void solve() {
    int len = SZ(s);
    s = " " + s + " ";

    // same length
    if (len % 2 == 0) {
        FORD(i,len,1) {
            // first different character is at i

            bool ok = true;
            for(int u = 1, v = len; u <= v; ++u, --v) {
                if (u < i && v < i && s[u] == s[v]) {
                    ok = false;
                    break;
                }
            }

            if (!ok) continue;

            // position i: must increase
            s[i]++;
            while (i > len - i + 1 && s[i] == s[len - i + 1]) ++s[i];
            if (s[i] > '9') continue;

            // position i+1 .. len
            FOR(u,i+1,len) {
                int v = len - u + 1;
                if (u < v) s[u] = '0';
                else {
                    s[u] = '0';
                    if (s[u] == s[v]) s[u]++;
                }
            }
            FOR(i,1,len) cout << s[i]; cout << endl;
            return ;
        }
    }

    // greater length
    ++len; if (len % 2) ++len;
    FOR(i,1,len/2) {
        if (i == 1) cout << '1';
        else cout << '0';
    }
    FORD(i,len/2,1) {
        if (i == 1) cout << '0';
        else cout << '1';
    }
    cout << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("anti.in", "r", stdin);
    freopen("anti.out", "w", stdout);
    while (cin >> s) {
        if (s == "0") break;
        solve();
    }
}
