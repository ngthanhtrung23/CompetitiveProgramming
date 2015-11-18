
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))

#define right right___
using namespace std;

const int MN = 100111;
string a[MN];
vector< vector<int> > right, down;
int m, n;

void init(vector< vector<int> > &x) {
    x.resize(m + 5);
    REP(i,m+5) x[i].resize(n+5);
}

char tmp[100111];
int res[MN];

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
    while (scanf("%d%d\n", &m, &n) == 2) {
        init(right);
        init(down);

        FOR(i,1,m) {
            gets(tmp);
            a[i] = " " + string(tmp);
        }

        // right
        FOR(i,1,m) {
            right[i][n+1] = n+1;
            FORD(j,n,1) {
                if (a[i][j] == '+') right[i][j] = j;
                else right[i][j] = right[i][j+1];
            }
        }
        // down
        FORD(i,m+1,1) {
            FOR(j,1,n) {
                if (i == m+1) down[i][j] = i;
                else if (a[i][j] == '+') down[i][j] = i;
                else down[i][j] = down[i+1][j];
            }
        }
        memset(res, 0, sizeof res);
        FOR(i,1,m) FOR(j,1,n) {
            if (a[i][j] == '+') continue;
            int x = right[i][j] - j;
            res[x]++;

            x = down[i][j] - i;
            res[x]++;
        }
        FORD(i,max(m,n),1) res[i] += res[i+1];
        res[1] = 0;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') ++res[1];
        FOR(i,1,max(m,n)) printf("%d ", res[i]);
        puts("");
    }
}
