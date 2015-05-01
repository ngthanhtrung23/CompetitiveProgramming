
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

const int MN = 300111;

int a[MN], n, suffixId[MN], cnt[MN];
vector<int> s;

struct SuffixArray {
    vector<int> a;
    int N, m;
    vector<int> SA, LCP, x, y, w, c;

    SuffixArray(vector<int> _a, int m) : N(_a.size() + 1), m(m),
            SA(MN), LCP(MN), x(MN), y(MN), w(max(m, MN)), c(MN) {
        a.push_back(0);
        for(int x : _a) a.push_back(x);
        DA();
        kasaiLCP();
        #define REF(X) { rotate(X.begin(), X.begin()+1, X.end()); X.pop_back(); }
        REF(SA); REF(LCP);
        a.erase(a.begin());
        for(int i = 0; i < SA.size(); ++i) --SA[i];
        #undef REF
    }

    inline bool cmp (const int a, const int b, const int l) { return (y[a] == y[b] && y[a + l] == y[b + l]); }

    void Sort() {
        for(int i = 0; i < m; ++i) w[i] = 0;
        for(int i = 0; i < N; ++i) ++w[x[y[i]]];
        for(int i = 0; i < m - 1; ++i) w[i + 1] += w[i];
        for(int i = N - 1; i >= 0; --i) SA[--w[x[y[i]]]] = y[i];
    }

    void DA() {
        for(int i = 0; i < N; ++i) x[i] = a[i], y[i] = i;
        Sort();
        for(int i, j = 1, p = 1; p < N; j <<= 1, m = p) {
            for(p = 0, i = N - j; i < N; i++) y[p++] = i;
            for (int k = 0; k < N; ++k) if (SA[k] >= j) y[p++] = SA[k] - j;
            Sort();
            for(swap(x, y), p = 1, x[SA[0]] = 0, i = 1; i < N; ++i)
                x[SA[i]] = cmp(SA[i - 1], SA[i], j) ? p - 1 : p++;
        }
    }

    void kasaiLCP() {
        for (int i = 0; i < N; i++) c[SA[i]] = i;
        for (int i = 0, j, k = 0; i < N; LCP[c[i++]] = k)
            if (c[i] > 0) for (k ? k-- : 0, j = SA[c[i] - 1]; a[i + k] == a[j + k]; k++);
            else k = 0;
    }
};

int c[MN], nc;
void RR() {
    REP(i,s.size()) {
        c[i] = s[i];
    }
    sort(c, c+s.size());
    nc = unique(c, c+s.size()) - c;
    REP(i,s.size())
        s[i] = lower_bound(c, c+nc, s[i]) - c + 1;
}

int nQuery;

struct Query {
    int u, v, res;
} queries[MN];

int lg[MN], minVal[22][MN];
SuffixArray SA(vector<int>{}, 100);

#define TWO(X) (1<<(X))
void buildRMQ() {
    memset(lg, -1, sizeof lg);
    for(int i = 1, t = 0; i < MN; i *= 2, ++t) {
        lg[i] = t;
    }
    FOR(i,2,MN-1) if (lg[i] < 0) lg[i] = lg[i-1];

    FOR(i,1,s.size()) {
        minVal[0][i] = SA.LCP[i];
    }

    FOR(t,1,19) {
        FOR(i,0,s.size()-TWO(t)) {
            minVal[t][i] = min(minVal[t-1][i], minVal[t-1][i+TWO(t-1)]);
        }
    }
}

int get(int l, int r) {
    int t = lg[r - l + 1];
    return min(minVal[t][l], minVal[t][r - TWO(t)+1]);
}

int getMin(int u, int len) {
    if (u == 0) return 0;
    int l = 0, r = u-1, res = u;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (get(mid+1, u) >= len) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res;
}

int getMax(int u, int len) {
    if (u == s.size()-1) return u;

    int l = u+1, r = s.size()-1, res = u;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (get(u+1, mid) >= len) {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return res;
}

vector< pair<int, pair<int,int> > > events[MN];

int bit[MN];
#define _(X) ((X) & (-(X)))

void bit_update(int u) {
    if (u == 0) return ;
    while (u < MN) {
        ++bit[u];
        u += _(u);
    }
}

int bit_get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        scanf("%d", &nQuery);
        FOR(i,1,nQuery) {
            scanf("%d%d", &queries[i].u, &queries[i].v);
        }


        FOR(i,2,n) {
            s.push_back(a[i] - a[i-1]);
        }
        s.push_back(2000111000);
        FOR(i,2,n) {
            s.push_back(a[i-1] - a[i]);
        }
//        PR0(s, s.size());

        RR();
//        PR0(s, s.size());

        SA = SuffixArray(s, 200111);
//        PR0(SA.SA, s.size());
//        PR0(SA.LCP, s.size());

        REP(i,s.size()) {
            int u = SA.SA[i];
            if (u >= 0 && u <= n-2) {
                suffixId[u+2] = i;
            }
        }

        REP(i,s.size()) {
            if (i == 0) cnt[i] = 0;
            else {
                cnt[i] = cnt[i-1];
                int u = SA.SA[i];
                if (u < 0 || u > n-2) ++cnt[i];
            }
        }
//        PR0(cnt, s.size());
//        PR(suffixId, n);

        buildRMQ();

        FOR(i,1,2*n) events[i].clear();
        FOR(q,1,nQuery) {
            int u = queries[q].u, v = queries[q].v;
            if (u == v) queries[q].res = n-1;
            else {
                int from = u + 1, len = v - u;

//                cout << "Query: " << u << ' ' << v << endl;
                int l = getMin(suffixId[from], len);
                int r = getMax(suffixId[from], len);
//                DEBUG(l);
//                DEBUG(r);

                queries[q].res = cnt[r] - cnt[l-1];

                // - số số thuộc [l, r], <= v+n-1
                // + số số thuộc [l, r], <= u+n-2
                events[v+n-1].push_back(make_pair(-q, make_pair(l, r)));
                events[u-len+n-2].push_back(make_pair( q, make_pair(l, r)));
            }
        }

        REP(i,s.size()) {
            int u = SA.SA[i];
            if (u < 0) continue;
            events[u].push_back(make_pair(0, make_pair(i, 0)));
        }

        FOR(x,1,n+n) {
            for(auto p : events[x]) {
                if (p.first == 0) bit_update(p.second.first);
            }

            for(auto p : events[x]) {
                if (p.first < 0)
                    queries[-p.first].res -= bit_get(p.second.second) - bit_get(p.second.first-1);
                else if (p.first > 0)
                    queries[ p.first].res += bit_get(p.second.second) - bit_get(p.second.first-1);
            }
        }

        FOR(i,1,nQuery) printf("%d\n", queries[i].res);
    }
    return 0;
}
