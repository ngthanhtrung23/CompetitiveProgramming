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
long long it[MN * 4];
long long power[MN];

int b, MOD, l, n;

long long add(long long a, long long b, long long len) {
    return (a*power[len] + b) % MOD;
}

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
#define MID ((l + r) >> 1)
void update(int i, int l, int r, int u, long long val) {
    if (u < l || r < u) return ;
    if (l == r) { it[i] = val; return ; }
    update(CT(i), l, MID, u, val);
    update(CP(i), MID+1, r, u, val);

    it[i] = add(it[CT(i)], it[CP(i)], r - MID);
}

vector< pair<long long, pair<int,int> > > all;
void visit(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        all.push_back(make_pair(it[i], make_pair(l, r)));
        return ;
    }
    visit(CT(i), l, MID, u, v);
    visit(CP(i), MID+1, r, u, v);
}
long long get(int u, int v) {
    all.clear();
    visit(1, 1, l, u, v);
    int len = 0;
    long long res = 0;
    FORD(i,all.size()-1,0) {
        res = add(all[i].first, res, len);
        len += all[i].second.second - all[i].second.first + 1;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> b >> MOD >> l >> n && b) {
        power[0] = 1;
        FOR(i,1,l) power[i] = power[i-1] * b % MOD;

        memset(it, 0, sizeof it);
        while (n--) {
            char typ; cin >> typ;
            if (typ == 'E') {
                int u, val; cin >> u >> val;
                update(1, 1, l, u, val);
            }
            else {
                int u, v; cin >> u >> v;
                cout << get(u, v) << "\n";
            }
        }
        cout << "-\n";
    }
    return 0;
}
