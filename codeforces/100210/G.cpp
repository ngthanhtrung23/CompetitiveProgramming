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

const int MN = 10111;
int group[MN];
vector<int> res[MN];

int main() {
    ios :: sync_with_stdio(false);
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);

    int n;
    while (cin >> n) {
        int k = 1;
        while (k * k < n) ++k;

        FOR(i,1,k) res[i].clear();

        int has = n;
        int last = n+1;
        FORD(group,k,1) {
            int can = min(k, has - (group-1));
            FORD(i,last-1,last-can) res[group].push_back(i);

            has -= can;
            last -= can;
        }
        FOR(group,1,k) {
            for(int x : res[group]) cout << x << ' ';
        }
        cout << endl;
    }
}