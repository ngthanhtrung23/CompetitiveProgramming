
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

const int MN = 2111;

string a, b;
int f[MN][MN], g[MN][MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> a >> b) {
        int la = SZ(a), lb = SZ(b);
        a = " " + a + " ";
        b = " " + b + " ";

        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        FORD(i,la,1) FORD(j,lb,1) {
            if (a[i] == b[j]) f[i][j] = f[i+1][j+1] + 1;
            else f[i][j] = 0;
        }
        FOR(i,1,la) FORD(j,lb,1) {
            if (a[i] == b[j]) g[i][j] = g[i-1][j+1] + 1;
            else g[i][j] = 0;
        }
        int j = 1;
        vector< pair<int,int> > res;
        try {
            while (j <= lb) {
                int len = 0;
                int savel = -1, saver = -1;

                FOR(i,1,la) {
                    if (f[i][j] > len) {
                        len = f[i][j];
                        savel = i;
                        saver = i + len - 1;
                    }
                    if (g[i][j] > len) {
                        len = g[i][j];
                        savel = i;
                        saver = i - len + 1;
                    }
                }

                if (len == 0) {
                    throw 1;
                }
                res.push_back(make_pair(savel, saver));
                j += len;
            }
            cout << SZ(res) << '\n';
            for(auto p : res) cout << p.first << ' ' << p.second << '\n';
            cout << endl;
        }
        catch (int e) {
            cout << -1 << endl;
        }
    }
}
