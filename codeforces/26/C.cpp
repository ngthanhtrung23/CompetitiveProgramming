
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int m, n, a, b, c;
char x[111][111];

char get(vector< pair<int,int> > p) {
    set<char> all;
    for(auto pos : p) {
        int u = pos.first, v = pos.second;
        all.insert(x[u-1][v]);
        all.insert(x[u+1][v]);
        all.insert(x[u][v+1]);
        all.insert(x[u][v-1]);
    }
    char res = 'a';
    while (all.count(res)) ++res;
    return res;
}

int main() {
    while (cin >> m >> n >> a >> b >> c) {
        memset(x, ' ', sizeof x);
        bool ok = true;
        if (m % 2 == 1 && n % 2 == 1) {
            ok = false;
        }
        else {
            if (m % 2 == 1) {
                for(int j = 0; j < n; j += 2) {
                    if (a == 0) {
                        ok = false;
                        break;
                    }
                    x[m-1][j] = x[m-1][j+1] = get({make_pair(m-1, j), make_pair(m-1, j+1)});
                    --a;
                }
            }
            else if (n % 2 == 1) {
                for(int i = 0; i < m; i += 2) {
                    if (b == 0) {
                        ok = false;
                        break;
                    }
                    x[i][n-1] = x[i+1][n-1] = get({make_pair(i, n-1), make_pair(i+1, n-1)});
                    --b;
                }
            }
            for(int i = 0; i < m-1; i += 2)
                for(int j = 0; j < n-1; j += 2) {
                    if (c > 0) {
                        x[i][j] = x[i][j+1] = x[i+1][j] = x[i+1][j+1]
                            = get({make_pair(i, j), make_pair(i, j+1), make_pair(i+1, j), make_pair(i+1, j+1)});
                        --c;
                    }
                    else if (a > 1) {
                        x[i][j] = x[i][j+1] = get({make_pair(i, j), make_pair(i, j+1)});
                        x[i+1][j] = x[i+1][j+1] = get({make_pair(i+1, j), make_pair(i+1, j+1)});
                        a -= 2;
                    }
                    else if (b > 1) {
                        x[i][j] = x[i+1][j] = get({make_pair(i, j), make_pair(i+1, j)});
                        x[i][j+1] = x[i+1][j+1] = get({make_pair(i, j+1), make_pair(i+1, j+1)});
                        b -= 2;
                    }
                    else {
                        ok = false;
                        break;
                    }
                }
        }
        if (!ok) cout << "IMPOSSIBLE" << endl;
        else {
            REP(i,m) {
                REP(j,n) cout << x[i][j];
                cout << '\n';
            }
        }
    }
    return 0;
}

