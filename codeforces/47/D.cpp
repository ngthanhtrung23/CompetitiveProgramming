
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, m;
string s[11];
int correct[11], cur[11];

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int encode() {
    int res = 0;
    FOR(i,1,m) {
        res = res * 6 + cur[i];
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        int left_from = 0, left_to = n / 2 - 1;
        int right_from = left_to + 1, right_to = n - 1;

        FOR(i,1,m) cin >> s[i] >> correct[i];

        map<int,int> cnt;
        REP(mask,TWO(left_to - left_from + 1)) {
            FOR(i,1,m) {
                cur[i] = 0;
                REP(j,left_to - left_from + 1) {
                    if (CONTAIN(mask,j) && s[i][j] == '1') ++cur[i];
                    if (!CONTAIN(mask,j) && s[i][j] == '0') ++cur[i];
                }
            }
            try {
                FOR(i,1,m) if (cur[i] > correct[i]) throw 1;
                cnt[encode()]++;
            } catch(int e) {
            }
        }

        ll res = 0;
        REP(mask,TWO(right_to - right_from + 1)) {
            FOR(i,1,m) {
                cur[i] = correct[i];
                REP(j,right_to - right_from + 1) {
                    if (CONTAIN(mask,j) && s[i][right_from + j] == '1') --cur[i];
                    if (!CONTAIN(mask,j) && s[i][right_from + j] == '0') --cur[i];
                }
            }
            try {
                FOR(i,1,m) if (cur[i] < 0) throw 1;
                res += cnt[encode()];
            } catch (int e) {
            }
        }
        cout << res << endl;
    }
}
