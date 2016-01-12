
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

int cnt[MN], a[MN], n, k;

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);

        memset(cnt, 0, sizeof cnt);
        int uniq = 0;

        int j = 1;
        int res = 1, savel = 1, saver = 1;
        FOR(i,1,n) {
            ++cnt[a[i]]; if (cnt[a[i]] == 1) ++uniq;

            while (uniq > k) {
                --cnt[a[j]]; if (cnt[a[j]] == 0) --uniq;
                ++j;
            }
            
            int cur = i - j + 1;
            if (cur > res) {
                res = cur;
                savel = j;
                saver = i;
            }
        }
        cout << savel << ' ' << saver << endl;
    }
}
