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

const int MN = 100111;
const int MOD = 1000000007;
string s, t;
#define next next_
long long f[MN], sum[MN], sumSum[MN], next[MN], first[MN];
int ls, lt;

void init() {
    memset(next, 0, sizeof next);
    memset(first, 0, sizeof first);
    int j = 0; next[1] = 0;
    FOR(i,2,lt) {
        while (j > 0 && t[i] != t[j+1]) j = next[j];
        if (t[i] == t[j+1]) ++j;
        next[i] = j;
    }
//    PR(next, lt);

    j = 0;
    FOR(i,1,ls) {
        while (j > 0 && s[i] != t[j+1]) j = next[j];
        if (s[i] == t[j+1]) ++j;

        if (j == lt) {
            first[i] = i - lt + 1;
            j = next[j];
        }
    }
    FOR(i,1,ls)
        if (first[i] == 0) first[i] = first[i-1];
//    PR(first, ls);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s >> t) {
        ls = s.length(), lt = t.length();
        s = " " + s;
        t = " " + t;
        init();
        memset(f, 0, sizeof f);
        memset(sum, 0, sizeof sum);
        memset(sumSum, 0, sizeof sumSum);

        FOR(i,1,ls) {
            if (first[i]) {
                f[i] = (sumSum[first[i]-1] + first[i]) % MOD;
            }
            sum[i] = (sum[i-1] + f[i]) % MOD;
            sumSum[i] = (sumSum[i-1] + sum[i]) % MOD;
        }
//        PR(f, ls);
//        PR(sum, ls);
//        PR(sumSum, ls);
        cout << sum[ls] << endl;
    }
    return 0;
}
