
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

const int MN = 400111;
int n, k, a[MN], good;
unordered_map<int,int> cnt;

void add(int id) {
    int u = a[id];
    cnt[u] += 1;
    if (cnt[u] == k) ++good;
}

void remove(int id) {
    int u = a[id];
    cnt[u] -= 1;
    if (cnt[u] == k-1) --good;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        cnt.clear();

        int right = 0; good = 0;
        long long res = 0;
        FOR(left,1,n) {
            if (left == 1) {
                right = 1;
                add(right);
            } else {
                remove(left-1);
            }
            while (good == 0 && right < n) {
                ++right;
                add(right);
            }

            if (good) {
                res += n - right + 1;
            }
        }
        cout << res << endl;
    }
    return 0;
}
