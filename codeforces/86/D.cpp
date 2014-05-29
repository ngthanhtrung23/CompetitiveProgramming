#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MAX_BLOCK = 400;
const int MN = 200111;

// n, q, a as defined in the problem
int n, q;
int a[MN];

// cnt(k) = frequency of k
int cnt[1000111];

// Store the queries
struct Query {
    int l, r, id;
} queries[MN];
// The answers that we will output
long long res[MN];

// Mo's algorithm comparator
bool operator < (const Query &a, const Query &b) {
    if (a.l / MAX_BLOCK != b.l / MAX_BLOCK) return a.l < b.l;
    else return a.r < b.r;
}

long long sum;

void add(int s) {
    sum -= cnt[s]*(long long)cnt[s] * s;
    ++cnt[s];
    sum += cnt[s]*(long long)cnt[s] * s;
}

void remove(int s) {
    sum -= cnt[s]*(long long)cnt[s] * s;
    --cnt[s];
    sum += cnt[s]*(long long)cnt[s] * s;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        memset(cnt, 0, sizeof cnt);
        sum = 0;

        FOR(i,1,n) cin >> a[i];
        FOR(i,1,q) {
            cin >> queries[i].l >> queries[i].r;
            queries[i].id = i;
        }
        sort(queries+1, queries+q+1);

        int l = 0, r = 0;
        FOR(i,1,q) {
            if (i == 1) {
                FOR(t,queries[i].l,queries[i].r) {
                    add(a[t]);
                }
            }
            else {
                if (l < queries[i].l) {
                    FOR(t,l,queries[i].l-1) remove(a[t]);
                }
                else if (l > queries[i].l) {
                    FOR(t,queries[i].l,l-1) add(a[t]);
                }

                if (r < queries[i].r) {
                    FOR(t,r+1,queries[i].r) add(a[t]);
                }
                else if (r > queries[i].r) {
                    FOR(t,queries[i].r+1,r) remove(a[t]);
                }
            }
            l = queries[i].l, r = queries[i].r;
            res[queries[i].id] = sum;
        }
        FOR(i,1,q) cout << res[i] << "\n";
    }
    return 0;
}
