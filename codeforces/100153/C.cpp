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

#define TWO(X) (1LL<<((long long)X))
#define CONTAIN(S,X) (S & TWO(X))
pair< pair<long long, long long>, long long> ls[TWO(16) + 11];
long long w[44], v[44];
long long best, save;
pair<long long, long long> it[TWO(20)];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
void build(int i, int l, int r) {
    if (l == r) {
        it[i] = make_pair(ls[l].first.second, ls[l].second);
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    it[i] = max(it[CT(i)], it[CP(i)]);
}

const long long oo = 1000111000111000111LL;
pair<long long, long long> get(int i, int l, int r, long long u, long long v) {
    if (ls[r].first.first < u || v < ls[l].first.first) return make_pair(-oo, 0);
    if (u <= ls[l].first.first && ls[r].first.first <= v) return it[i];
    int mid = (l + r) >> 1;
    return max(get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
}

int main() {
    freopen("dowry.in", "r", stdin);
    freopen("dowry.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    long long L, R;
    while (cin >> n >> L >> R) {
        REP(i,n) cin >> w[i] >> v[i];
        
        int l_from = 0, l_to = n/2 - 1;
        int r_from = l_to + 1, r_to = n-1;
        best = -oo; save = 0;

        int x = 0;
        REP(mask,TWO(l_to+1)) {
            long long cur_w = 0, cur_v = 0;
            FOR(i,l_from,l_to)
                if (CONTAIN(mask,i))
                    cur_w += w[i], cur_v += v[i];
            ls[++x] = make_pair(make_pair(cur_w, cur_v), mask);
        }
        sort(ls+1, ls+x+1);
//        DEBUG(l_from);
//        DEBUG(l_to);
//        FOR(i,1,x) {
//            auto t = ls[i];
//            cout << t.first.first << ' ' << t.first.second << "   " << t.second << endl;
//        }
//        DEBUG("---");
        build(1, 1, x);
        for(long long mask = 0; mask < TWO(n); mask += TWO(n/2)) {
            long long cur_w = 0, cur_v = 0;
            FOR(i,r_from,r_to)
                if (CONTAIN(mask,i))
                    cur_w += w[i], cur_v += v[i];

//            cout << cur_w << ' ' << cur_v << ' ' << mask << endl;
            pair<long long, long long> left = get(1, 1, x, L - cur_w, R - cur_w);
//            DEBUG(left.first);

            if (left.first + cur_v > best) {
                best = left.first + cur_v;
                save = left.second + mask;
            }
        }
        if (best < 0) cout << 0 << endl;
        else {
            int cnt = 0;
            vector<int> res;
            REP(i,n)
                if (CONTAIN(save, i)) {
                    ++cnt;
                    res.push_back(i);
                }
            cout << cnt << endl;
            for(int x : res) cout << x+1 << ' '; cout << endl;
        }
    }
    return 0;
}
