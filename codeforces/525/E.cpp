
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

long long gt[1011];
const long long oo = 10001110001110001LL;

long long fact(int n) {
    if (n <= 18) return gt[n];
    else return oo;
}

int n, k, a[33];
long long p3[30];
long long S;

namespace std {
    template<>
    struct hash< pair<int,long long> > {
        public:
            size_t operator() (pair<int,long long> x) const throw() {
                return x.first * 1000000009 + x.second;
            }
    };
}
unordered_map< pair<int, long long>, long long > cnt;

long long getBit(long long mask, int pos) {
    return (mask % p3[pos+1]) / p3[pos];
}

long long setBit(long long mask, int pos, int val) {
    return mask + (val - getBit(mask, pos)) * p3[pos];
}

int main() {
    gt[0] = 1; FOR(i,1,18) gt[i] = gt[i-1] * (long long) i;
    p3[0] = 1; FOR(i,1,30) p3[i] = p3[i-1] * 3;
    while (cin >> n >> k >> S) {
        FOR(i,1,n) cin >> a[i];

        int left_size = n / 2 + n % 2;
        int left_from = 1, left_to = left_size;

        int right_size = n - left_size;
        int right_from = left_to + 1, right_to = n;
        cnt.clear();

        REP(mask,p3[left_size]) {
            long long sum = 0;
            int k = 0;
            REP(offset,left_size) {
                int i = left_from + offset;

                int u = getBit(mask, offset);
                if (u == 1) sum += a[i];
                if (u == 2) sum += fact(a[i]), k += 1;
            }
            cnt[make_pair(k, sum)]++;
        }
//        for(auto x : cnt)
//            cout << x.first.first << ' ' << x.first.second << "   " << x.second << endl;

        long long res = 0;
        REP(mask,p3[right_size]) {
            long long sum = 0;
            int v = 0;
            REP(offset, right_size) {
                int i = right_from + offset;
                int u = getBit(mask, offset);
                if (u == 1) sum += a[i];
                if (u == 2) sum += fact(a[i]), v += 1;
            }
            FOR(u,0,left_size)
                if (u + v <= k)
                    res += cnt[make_pair(u, S - sum)];
        }
        cout << res << endl;
    }
    return 0;
}

