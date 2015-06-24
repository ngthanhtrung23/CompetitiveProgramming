
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

#define ll long long
struct Frac {
    ll x, y;
    Frac(ll x = 0, ll y = 1) : x(x), y(y) {
        ll g = __gcd(x, y);
        x /= g;
        y /= g;
    }
};

bool operator == (const Frac& a, const Frac& b) {
    return a.x * b.y == a.y * b.x;
}

bool operator < (const Frac& a, const Frac& b) {
    return a.x*b.y < a.y*b.x;
}

const int MN = 100111;
int n, m, bad[MN], removed[MN];
vector<int> ke[MN];
int cur[MN];

int main() {
    int nBad = 0;
    while (scanf("%d%d%d", &n, &m, &nBad) == 3) {
        memset(bad, false, sizeof bad);
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,nBad) {
            int x; scanf("%d", &x);
            bad[x] = true;
        }

        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        int nGood = n - nBad;
        Frac res = Frac(0, 1);
        REP(turn,2) {
//            DEBUG(turn);
            set< pair<Frac,int> > all;
            FOR(i,1,n) if (!bad[i]) {
                int x = 0;
                for(int u : ke[i])
                    if (!bad[u]) ++x;
                cur[i] = x;

                all.insert(make_pair(Frac(cur[i], ke[i].size()), i));
            }

            memset(removed, false, sizeof removed);
            while (all.size() >= 1) {
                auto p = *all.begin();
                int u = p.second;

                // update result
//                cout << p.first.x << ' ' << p.first.y << endl;
//                for(auto p : all) cout << p.second << ' '; cout << endl;

                if (turn == 0) {
                    if (res < p.first) res = p.first;
                }
                else {
                    if (res == p.first) {
                        printf("%d\n", all.size());
                        for(auto p : all) {
                            printf("%d ", p.second);
                        }
                        puts("");
                        break;
                    }
                }

                // remove 1 element
                all.erase(all.begin());
                if (all.empty()) break;

                removed[u] = true;
                for(int v : ke[u]) {
                    if (bad[v] || removed[v]) continue;
                    all.erase(all.find(make_pair(Frac(cur[v], ke[v].size()), v)));
                    cur[v]--;

                    all.insert(make_pair(Frac(cur[v], ke[v].size()), v));
                }
            }
        }
    }
}

