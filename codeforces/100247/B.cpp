#include <bits/stdc++.h>
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

const ll MOD = 1e9 + 7;
int cnt[33];
char s[1000111];
int last[33];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (scanf("%d\n", &n) == 1) {
        map<ll,ll> all;
        FOR(i,1,n) {
            memset(cnt, 0, sizeof cnt);
            memset(last, -1, sizeof last);

            gets(s);
            REP(j,strlen(s)) {
                cnt[s[j] - 'a'] = cnt[s[j] - 'a'] * 1000003 + (j - last[s[j] - 'a']);
                last[s[j] - 'a'] = j;
            }
            sort(cnt, cnt+26);
            ll hash = 0;
            REP(i,26) {
                hash = hash * MOD + cnt[i];
            }
            all[hash] += 1;
        }

        ll res = 0;
        for(auto p : all) {
            res += p.second * (p.second - 1) / 2;
        }
        cout << res << endl;
    }
}
