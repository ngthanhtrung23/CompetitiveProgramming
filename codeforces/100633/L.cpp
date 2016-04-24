
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

const int MN = 100111;
int n;
int a[MN];
map<int,int> cnt;

int get() {
    auto it = *cnt.rbegin();
    return it.first * it.second;
}

void down(int i) {
    cnt[a[i]]--; if (cnt[a[i]] == 0) cnt.erase(a[i]);
    --a[i];
    cnt[a[i]]++;
}
void up(int i) {
    cnt[a[i]]--; if (cnt[a[i]] == 0) cnt.erase(a[i]);
    ++a[i];
    cnt[a[i]]++;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        cnt.clear();
        FOR(i,1,n) {
            GI(a[i]);
            cnt[a[i]]++;
        }
        int res = get();

        FOR(i,1,n) {
            // move to left
            if (i > 1 && a[i]) {
                down(i);
                up(i-1);

                res = min(res, get());

                down(i-1);
                up(i);
            }
            // move to right
            if (i < n && a[i]) {
                down(i);
                up(i+1);
                res = min(res, get());

                up(i);
                down(i+1);
            }
        }

        cout << res << endl;
    }
}
