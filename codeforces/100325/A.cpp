
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

const int MN = 5011;
string s;

short cost[MN][MN];
#define next __next
int f[MN], next[MN];

string t;

void trace(int i) {
    if (i == 0) return ;
    if (f[i] == i) {
        REP(x,i) cout << s[x];
        cout << " 1" << '\n';
        return ;
    }
    FOR(j,0,i-1) if (f[i] == f[j] + cost[j][i-1]) {
        trace(j);
        REP(x,cost[j][i-1])
            cout << s[j + x];
        int len = i - j;
        cout << ' ' << len / cost[j][i-1] << '\n';
        break;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("decomp.in", "r", stdin);
    freopen("decomp.out", "w", stdout);

    while (cin >> s) {
        // DEBUG
//        REP(i,MN) s += (char) ('A' + rand() % 20);

        int ls = s.length();
        REP(i,ls) {
            t = s.substr(i);
            next[0] = -1;

            int lt = t.length();
            int j = -1;
            FOR(i,1,lt-1) {
                while (j >= 0 && t[j+1] != t[i]) j = next[j];
                if (t[j+1] == t[i]) ++j;
                next[i] = j;
            }

            FOR(j,i,ls-1) {
                int len = j - i + 1;
                int mat = next[j - i] + 1;

                // looks wrong
                if (mat + mat >= len && len % (len - mat) == 0) cost[i][j] = len - mat;
                else cost[i][j] = len;
            }
        }

        f[0] = 0;
        FOR(i,1,ls) {
            f[i] = i;
            FOR(j,0,i-1)
                f[i] = min(f[i], f[j] + cost[j][i-1]);
        }
        cout << f[ls] << '\n';
        trace(ls);
    }
}
