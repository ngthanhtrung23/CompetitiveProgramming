
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

const ll MOD = 1e9 + 7;
int m, n, r;
map< vector<int>, int> id;

bool check(vector<int>& a) {
    REP(i,SZ(a))
    FOR(j,i+1,SZ(a)-1)
    if (a[i] != a[j])
        FOR(k,j+1,SZ(a)-1)
            if (a[i] == a[k])
                FOR(l,k+1,SZ(a)-1)
                    if (a[j] == a[l]) {
                        return true;
                    }
    return false;
}

void gen(int i, vector<int> &cur) {
    if (i >= m) {
        if (check(cur)) {
            int x = SZ(id);
            id[cur] = x;
        }
        return ;
    }

    set<int> all(cur.begin(), cur.end());
    FOR(val,0,SZ(all)) {
        vector<int> next = cur;
        next.push_back(val);
        gen(i+1, next);
    }
}

void init() {
    id.clear();
    vector<int> t;
    gen(0, t);
}

int f[55][20111];
vector<int> state[20111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("linked.in", "r", stdin);
    freopen("linked.out", "w", stdout);
    while (cin >> m >> n >> r) {
        init();

        int k = SZ(id);
        for(auto p : id) {
            auto v = p.first;
            set<int> all;
            
            ll cur = 1;
            for(int x : v) {
                if (all.find(x) != all.end()) continue;
                if (r <= SZ(all)) {
                    cur = 0;
                    continue;
                }

                cur = cur * (r - SZ(all)) % MOD;
                all.insert(x);
            }
            f[m][p.second] = cur;

            state[p.second] = v;
        }

        FOR(i,m,n-1) REP(j,k) {
            auto u = state[j];
            u.erase(u.begin());

            map<int,int> mp;

            // map u to min
            vector<int> v;
            for(int x : u) {
                if (mp.find(x) == mp.end()) {
                    int z = SZ(mp);
                    mp[x] = z;
                }
                v.push_back(mp[x]);
            }

            int has = SZ(mp);
            REP(add,has+1) {
                vector<int> next = v;
                next.push_back(add);

                if (id.find(next) != id.end()) {
                    ll mult = 1;
                    if (add == has) mult = r - has;
                    if (mult < 0) continue;

                    ll cur = f[i][j] * mult;
                    f[i+1][id[next]] = (f[i+1][id[next]] + cur) % MOD;
                }
            }
        }

        ll res = 0;
        REP(i,k) res = (res + f[n][i]) % MOD;
        cout << res << endl;
    }
}
