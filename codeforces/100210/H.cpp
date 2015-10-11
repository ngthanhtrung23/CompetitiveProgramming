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

vector<int> a[111];

int main() {
    ios :: sync_with_stdio(false);
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);

    int n, r;
    while (cin >> n >> r) {
        --r;
        int d = n / r;
        int x = n % r;

        int cnt = 0;
        FOR(i,1,x) REP(turn,d+1) a[i].push_back(++cnt);
        FOR(i,x+1,r) REP(turn,d) a[i].push_back(++cnt);

        vector< pair<int,int> > res;
        FOR(i,1,r) FOR(j,i+1,r)
            for(int x : a[i])
                for(int y : a[j])
                    res.push_back(make_pair(x, y));

        cout << res.size() << endl;
        for(auto p : res) cout << p.first << ' ' << p.second << endl;
    }
}