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

string s;
int cnt[11];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> s) {
        memset(cnt, 0, sizeof cnt);
        for(char c : s)
            cnt[c - '0']++;
        vector<int> a;
        --cnt[1];
        --cnt[6];
        --cnt[8];
        --cnt[9];
        int rem = 0;
        FOR(i,1,9) {
            while (cnt[i]) {
                a.push_back(i);
                --cnt[i];
                rem = (rem * 10 + i) % 7;
            }
        }
        rem = (rem * 10000) % 7;
        int x[4] = {1, 6, 8, 9};
        do {
            int cur = 0;
            REP(i,4) cur = (cur * 10 + x[i]) % 7;

            if ((rem + cur) % 7 == 0) {
                break;
            }
        } while (next_permutation(x, x+4));
        for(int x : a) cout << x;
        REP(t,4) cout << x[t];
        while (cnt[0]) {
            cout << 0;
            --cnt[0];
        }
        cout << endl;
    }
    return 0;
}
