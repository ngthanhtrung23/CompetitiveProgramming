
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
using namespace std;

const int MN = 200111;

int n;
struct Migrate {
    int a, b, c;
    int f, id;
} x[MN];

bool operator < (const Migrate& x, const Migrate& y) {
    if (x.f != y.f) return x.f < y.f;
    return x.id < y.id;
}

bool operator == (const Migrate& x, const Migrate& y) {
    return x.id == y.id;
}

vector<int> ls[MN];
int cur[MN];

void update(Migrate& x) {
    x.f = -cur[x.a] + max(cur[x.b], cur[x.c]);
//    x.f = -2*cur[x.a] + cur[x.b] + cur[x.c];
}

vector<int> res;
set<Migrate> all;
bool visited[MN];

void solve() {
    memset(visited, false, sizeof visited);

    while (!all.empty()) {
        auto u = *all.begin();
        all.erase(all.begin());

        int id = u.id;
        res.push_back(id);
        visited[id] = true;

        int t[3];
        t[0] = u.a;
        t[1] = u.b;
        t[2] = u.c;
        if (cur[t[1]] == 9 || cur[t[2]] == 9) {
            puts("NO");
            return ;
        }

        cur[t[0]] -= 2;
        ++cur[t[1]];
        ++cur[t[2]];

        REP(turn,3) {
            for(int id : ls[t[turn]]) if (!visited[id]) {
                all.erase(x[id]);
                update(x[id]);
                all.insert(x[id]);
            }
        }
    }
    puts("YES");
    for(int id : res) printf("%d ", id); puts("");
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            ls[i].clear();
            cur[i] = 4;
        }
        all.clear();
        res.clear();

        FOR(i,1,4*n) {
            cin >> x[i].a >> x[i].b >> x[i].c;
            x[i].id = i;
            update(x[i]);

            all.insert(x[i]);
            ls[x[i].a].push_back(i);
            ls[x[i].b].push_back(i);
            ls[x[i].c].push_back(i);
        }

        solve();
    }
}

