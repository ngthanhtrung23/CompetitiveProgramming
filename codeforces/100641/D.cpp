
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

string s;
int n;
vector<int> f[55][55];
bool mark[5011];

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    map<char,int> value;
    value['I'] = 1;
    value['V'] = 5;
    value['X'] = 10;
    value['L'] = 50;
    value['C'] = 100;

    while (cin >> s && s != "0") {
        n = s.length();
        s = " " + s;
        FORD(i,n,1) FOR(j,i,n) {
            f[i][j].clear();
            if (i == j) {
                f[i][j].push_back(value[s[i]]);
            }
            else {
                FOR(k,i,j-1) {
                    for(auto x : f[i][k]) {
                        for(auto y : f[k+1][j]) {
                            if (x >= y) {
                                if (!mark[x+y]) {
                                    f[i][j].push_back(x + y);
                                    mark[x+y] = true;
                                }
                            }
                            else {
                                if (!mark[y-x]) {
                                    f[i][j].push_back(y - x);
                                    mark[y-x] = true;
                                }
                            }
                        }
                    }
                }
                sort(f[i][j].begin(), f[i][j].end());
                for(int x : f[i][j])
                    mark[x] = false;
            }
        }
        cout << "Case " << ++test << ':';
        for(auto x : f[1][n]) cout << ' ' << x;
        cout << '\n';
    }
    return 0;
}
