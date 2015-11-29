
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

string s;
int cnt[333];
char res[200111];

int main() {
    ios :: sync_with_stdio(false);
    cin.tie(0);

    while (cin >> s) {
        memset(cnt, 0, sizeof cnt);
        for(char c : s) cnt[c] += 1;

        FORD(c,'z','a') {
            if (cnt[c] % 2) {
                FOR(c2,'a',c-1) if (cnt[c2] % 2) {
                    cnt[c]--;
                    cnt[c2]++;
                    break;
                }
            }
        }
        for(int i = 0, j = s.length() - 1; i <= j; ++i, --j) {
            if (i == j) {
                FOR(c,'a','z') if (cnt[c]) {
                    res[i] = c;
                    break;
                }
            }
            else {
                FOR(c,'a','z') if (cnt[c] >= 2) {
                    res[i] = res[j] = c;
                    cnt[c] -= 2;
                    break;
                }
            }
        }
        REP(i,s.length()) putchar(res[i]);
        puts("");
    }
}
