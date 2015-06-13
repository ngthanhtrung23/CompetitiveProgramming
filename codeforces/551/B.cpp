
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

string a, b, c;
int cnta[311], cntb[311], cntc[311];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a >> b >> c) {
        memset(cnta, 0, sizeof cnta);
        memset(cntb, 0, sizeof cntb);
        memset(cntc, 0, sizeof cntc);

        for(char x : a) cnta[x] += 1;
        for(char x : b) cntb[x] += 1;
        for(char x : c) cntc[x] += 1;

        int savek = 0;
        int best = 0;
        FOR(k,0,a.length() / b.length()) {
            bool can = true;
            FOR(x,'a','z')
                if (cntb[x] * k > cnta[x]) can = false;
            if (!can) break;

            int cur = k;
            int ln = 1000111000;
            FOR(x,'a','z')
                if (cntc[x])
                    ln = min(ln, (cnta[x] - cntb[x]*k) / cntc[x]);
            if (best < cur + ln) {
                best = cur + ln;
                savek = k;
            }
        }
        FOR(i,1,savek) cout << b;
        FOR(i,1,best - savek) cout << c;
        FOR(x,'a','z') {
            cnta[x] -= cntb[x] * savek;
            cnta[x] -= cntc[x] * (best - savek);
            while (cnta[x]--) cout << (char) x;
        }
        cout << endl;
    }
    return 0;
}

