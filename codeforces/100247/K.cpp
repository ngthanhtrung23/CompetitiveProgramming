#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
struct Team {
    int a, b, c;

    void read() {
        GI(a); GI(b); GI(c);
    }
} a[MN];
bool operator < (const Team& u, const Team& v) {
    return u.a < v.a;
}
int n;
vector<int> nodes[MN];
vector<int> f[MN];

void addNode(int x, int y) {
    nodes[x].push_back(y);
}

void fakeUpdate(int u, int v) {
    for(int x = u; x <= n; x += x & -x)
        addNode(x, v);
}

void fakeGet(int u, int v) {
    for(int x = u; x > 0; x -= x & -x)
        addNode(x, v);
}

void update(int u, int v) {
    for(int x = u; x <= n; x += x & -x)
        for(int y = lower_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin() + 1; y <= nodes[x].size(); y += y & -y)
            f[x][y]++;
}

int get(int u, int v) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        for(int y = upper_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin(); y > 0; y -= y & -y)
            res += f[x][y];
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) a[i].read();
        sort(a+1, a+n+1);

        int res = 0;
        FOR(i,1,n) {
            a[i].b = n - a[i].b + 1;
            a[i].c = n - a[i].c + 1;
        }

//        FORD(i,n,1) {
//            res += n - i;
//            FOR(j,i+1,n) {
//                if (a[j].b < a[i].b && a[j].c < a[i].c)
//                    --res;
//            }
//        }

        FORD(i,n,1) {
            fakeUpdate(a[i].b, a[i].c);
        }
        FOR(i,1,n) {
            nodes[i].push_back(1000111000);
            sort(nodes[i].begin(), nodes[i].end());
            f[i].resize(SZ(nodes[i]) + 3);
        }
        FORD(i,n,1) {
            res += n - i;
            res -= get(a[i].b, a[i].c);
            update(a[i].b, a[i].c);
        }
        cout << res << endl;
    }
}
