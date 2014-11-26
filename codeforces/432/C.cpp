#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int n, a[MN], pos[MN], sieve[MN], p[MN];

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        for(int j=i*i; j < MN; j += i)
            sieve[j] = 1;
    }
    FOR(i,2,MN-1)
        if (sieve[i])
            p[i] = p[i-1];
        else p[i] = i;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    init();
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i];
            pos[a[i]] = i;
        }
        vector< pair<int,int> > res;

        FOR(i,1,n) {
            while (pos[i] > i) {
                int u = pos[i];
                int len = u - i + 1;
                int v = u - p[len] + 1;
                swap(a[u], a[v]);
                pos[a[u]] = u;
                pos[a[v]] = v;

                res.push_back(make_pair(min(u, v), max(u, v)));
            }
        }

        cout << res.size() << endl;
        for(auto p : res) cout << p.first << ' ' << p.second << "\n";
    }
    return 0;
}
