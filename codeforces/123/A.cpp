
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
char res[1011];

int isPrime(int n) {
    for(int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return n > 1;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> s) {
        memset(cnt, 0, sizeof cnt);
        for(char c : s) cnt[c]++;

        int ln = max_element(cnt, cnt+300) - cnt;

        int n = SZ(s);
        try {
            memset(res, ' ', sizeof res);
            FOR(i,2,n/2) {
                res[i] = (char) ln;
                cnt[ln]--;
                if (cnt[ln] < 0) throw 1;
            }
            FOR(i,n/2+1,n) if (!isPrime(i)) {
                res[i] = (char) ln;
                cnt[ln]--;
                if (cnt[ln] < 0) throw 1;
            }
            FOR(i,1,n) if (res[i] == ' ') {
                res[i] = 'a';
                while (cnt[res[i]] == 0) ++res[i];
                --cnt[res[i]];
            }
            cout << "YES" << endl;
            FOR(i,1,n) cout << (char) res[i]; cout << endl;
        } catch (int e) {
            cout << "NO" << endl;
        }
    }
}
