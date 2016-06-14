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
#define double long double
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int INF = 1000111000111000111LL;
const int MN = 300111;

struct Line {
    int a, b;
    int from, to;
} lines[MN];

struct Hull {
    vector<double> x;
    vector<int> a;
    vector<int> b;

    void init() {
        x.clear();
        a.clear();
        b.clear();
    }

    void remove() {
        a.pop_back();
        b.pop_back();
        x.pop_back();
    }

    void insert(Line l) {
        if (a.empty()) {
            x.push_back(-INF);
            a.push_back(l.a);
            b.push_back(l.b);
        }
        else {
            double xNew = -INF;
            while (!a.empty()) {
                if (a.back() == l.a) {
                    b.back() = max(b.back(), l.b);
                    return;
                }
                assert(l.a > a.back());

                xNew = 1.0 * (b.back() - l.b) / (l.a - a.back());
                if (xNew < x.back()) {
                    remove();
                }
                else break;
            }

            a.push_back(l.a);
            b.push_back(l.b);
            x.push_back(xNew);
        }
    }

    int get(int x0) {
        if (a.empty()) {
            return -INF;
        }
        int i = upper_bound(x.begin(), x.end(), x0) - x.begin() - 1;
        return a[i] * x0 + b[i];
    }
};

Hull it[MN * 4];

void init(int i, int l, int r) {
    it[i].init();
    if (l == r) return ;
    int mid = (l + r) >> 1;
    init(i<<1, l, mid);
    init(i<<1|1, mid+1, r);
}

void update(int i, int l, int r, int u, int v, Line t) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].insert(t);
        return ;
    }
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, v, t);
    update(i<<1|1, mid+1, r, u, v, t);
}

int get(int i, int l, int r, int time, int x0) {
    if (time < l || r < time) return -INF;

    int res = it[i].get(x0);
    if (l == r) return res;

    int mid = (l + r) >> 1;
    res = max(res, get(i<<1, l, mid, time, x0));
    res = max(res, get(i<<1|1, mid+1, r, time, x0));
    return res;
}

bool operator < (const Line& u, const Line& v) {
    if (u.a != v.a) return u.a < v.a;
    return u.b > v.b;
}
int nLine, id[MN];

struct Query {
    int time, x0;
} queries[MN];
int nQuery;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int q;
    while (GI(q) == 1) {
        nLine = 0;
        nQuery = 0;
        FOR(i,1,q) {
            int typ; GI(typ);
            if (typ == 1) {
                ++nLine;
                lines[nLine].from = i;
                lines[nLine].to = q;
                GI(lines[nLine].a);
                GI(lines[nLine].b);
                id[i] = nLine;
            }
            else if (typ == 2) {
                int x; GI(x);
                int lineId = id[x];
                lines[lineId].to = i;
            }
            else {
                ++nQuery;
                queries[nQuery].time = i;
                GI(queries[nQuery].x0);
            }
        }
        sort(lines+1, lines+nLine+1);

        init(1,1,q);
        FOR(i,1,nLine) {
            update(1, 1, q, lines[i].from, lines[i].to, lines[i]);
        }

        FOR(i,1,nQuery) {
            auto t = get(1, 1, q, queries[i].time, queries[i].x0);
            if (t == -INF) puts("EMPTY SET");
            else printf("%lld\n", t);
        }
    }
}