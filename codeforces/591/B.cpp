
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
using namespace std;

char val[333];
string s;
int n, k;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> s) {
        FOR(c,'a','z') val[c] = c;
        FOR(i,1,k) {
            char u, v; cin >> u >> v;

            char x = 'a'; while (val[x] != u) ++x;
            char y = 'a'; while (val[y] != v) ++y;
            swap(val[x], val[y]);
        }
        for(char c : s) putchar(val[c]);
        puts("");
    }
}
