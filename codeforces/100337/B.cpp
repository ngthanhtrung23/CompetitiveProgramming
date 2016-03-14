#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 4111;
int f[MN];
pair<int,int> tr[MN];
int tr2[MN];
short eq[MN][MN];
string s;
int n;

void trace(int n) {
    if (n == 0) return ;

    if (tr[n].first < 0) {
        trace(n-1);
        cout << s[n];
    }
    else {
        trace(tr2[n]);
        cout << '(' << tr[n].first << ',' << tr[n].second << ')';
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("lz.in", "r", stdin);
    freopen("lz.out", "w", stdout);
    while (cin >> s) {
        n = SZ(s);
        s = " " + s + " ";
        memset(eq, 0, sizeof eq);
        FOR(i,1,n) FOR(j,i+1,n) {
            if (s[i] == s[j]) eq[i][j] = eq[i-1][j-1] + 1;
            else eq[i][j] = 0;
        }
        f[0] = 0;
        FOR(i,1,n) {
            f[i] = f[i-1] + 9;
            tr[i] = make_pair(-1, -1);
            FOR(j,1,i-1) {
                int l = eq[j][i];
                if (!l) continue;

                int prev = i - l;
                int cost = f[prev] + 25;
                if (cost < f[i]) {
                    f[i] = cost;
                    tr[i] = make_pair(prev - (j - l), l);
                    tr2[i] = prev;
                }
            }
        }
        cout << f[n] << endl;
        trace(n);
        cout << endl;
    }
}
