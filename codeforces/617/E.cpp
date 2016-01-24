
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

const int MN = 1000111;
int cnt1[2000111], cnt2[2000111];
int n, q, k;

int a[MN];
struct Query {
    int l, r;
    int id;
} queries[MN];

bool operator < (const Query& a, const Query& b) {
    if (a.l / 300 != b.l / 300) return a.l / 300 < b.l / 300;
    else return a.r < b.r;
}

ll res[MN];
ll all = 0;

void extend(int l, int r, int u, int v) {
    while (r < v) {
        ++r;
        cnt1[a[r - 1]]++;
        all += cnt1[a[r] ^ k];
        cnt2[a[r]]++;

//        cout << '[' << l << '-' << r << "] --> " << all << "\n";
    }
    while (r > v) {
        all -= cnt1[a[r] ^ k];
        cnt1[a[r - 1]]--;
        cnt2[a[r]]--;
        --r;

//        cout << '[' << l << '-' << r << "] --> " << all << "\n";
    }

    while (l < u) {
        all -= cnt2[a[l-1] ^ k];
        cnt2[a[l]]--;
        cnt1[a[l-1]]--;
        ++l;

//        cout << '[' << l << '-' << r << "] --> " << all << "\n";
    }
    while (l > u) {
        --l;
        cnt2[a[l]]++;
        all += cnt2[a[l-1] ^ k];
        cnt1[a[l-1]]++;

//        cout << '[' << l << '-' << r << "] --> " << all << "\n";
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d%d", &n, &q, &k) == 3) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
        }
        FOR(i,1,n) a[i] ^= a[i-1];

        FOR(i,1,q) {
            scanf("%d%d", &queries[i].l, &queries[i].r);
            queries[i].id = i;
        }
        sort(queries+1, queries+q+1);

        all = 0;
        memset(cnt1, 0, sizeof cnt1);
        memset(cnt2, 0, sizeof cnt2);

        int l = 1, r = 1;
        cnt1[0] = 1;
        cnt2[a[1]] = 1;
        if (a[1] == k) ++all;

        FOR(i,1,q) {
            extend(l, r, queries[i].l, queries[i].r);
            res[queries[i].id] = all;

            l = queries[i].l;
            r = queries[i].r;
        }

        FOR(i,1,q) printf("%lld\n", res[i]);
    }
}
