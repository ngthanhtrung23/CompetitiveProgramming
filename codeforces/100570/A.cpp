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

const long long MOD = 1000000007;
const int MN = 100111;

int n, q, a[MN];
vector< pair<int,int> > factors[66];
double _log[66];
long long Power[66][66], inverse[66];
vector< int > pos[66];

long long Pow(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = Pow(x * x % MOD, k >> 1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}
long long inv(long long x) {
    return Pow(x, MOD - 2);
}

void init() {
    FOR(val,1,60) {
        _log[val] = log(val);
        Power[val][0] = 1;
        FOR(i,1,60) Power[val][i] = Power[val][i-1] * val;

        int u = val;
        FOR(i,2,60) if (u % i == 0) {
            int p = 0;
            while (u % i == 0) {
                ++p;
                u /= i;
            }
            factors[val].push_back(make_pair(i, p));
        }

        inverse[val] = inv(val);
    }
    FOR(i,1,60) {
        assert(inverse[i] * (long long) i % MOD == 1);
    }
}

pair<double,int> res[MN];
int cnt[MN];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    init();
    while (cin >> n >> q) {
        FOR(i,1,60) pos[i].clear();
        FOR(i,1,n) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        FOR(i,1,60) pos[i].push_back(n+1);

        FOR(i,1,n) res[i] = make_pair(1e50, -1);
        FOR(i,1,n) {
            // Consider segments that start at i
            vector< pair<int,int> > segs;
            FOR(val,1,60) {
                int j = *lower_bound(pos[val].begin(), pos[val].end(), i);
                if (j <= n) segs.push_back(make_pair(j, val));
            }
            sort(segs.begin(), segs.end());
//            DEBUG(i);
//            for(auto p : segs) cout << p.first << ' ' << p.second << "   "; cout << endl;

            memset(cnt, 0, sizeof cnt);
            double sum = 0;
            long long prod = 1;
            REP(t,segs.size()) {
                int value = segs[t].second;
                int j = (t+1 < segs.size()) ? segs[t+1].first - 1 : n;
                int len = j - i + 1;

                for(auto p : factors[value]) {
                    if (p.second > cnt[p.first]) {
                        int old = Power[p.first][cnt[p.first]];
                        sum -= _log[old];
                        prod = prod * inverse[old] % MOD;

                        cnt[p.first] = p.second;

                        int New = Power[p.first][p.second];
                        sum += _log[New];
                        prod = prod * New % MOD;
                    }
                }
//                cout << value << ' ' << sum << ' ' << prod << endl;

                res[len] = min(res[len], make_pair(sum, (int) prod));
            }
        }
        FORD(i,n-1,1) res[i] = min(res[i], res[i+1]);
        while (q--) {
            int x; cin >> x;
            cout << res[x].second << "\n";
        }
    }
    return 0;
}
