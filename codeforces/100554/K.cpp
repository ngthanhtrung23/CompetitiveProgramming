
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

string s;

bool good() {
    int nDigit = 0, nStar = 0;
    for(char c : s) {
        if (c == '*') {
            ++nStar;
            if (nDigit < nStar + 1) return false;
        }
        else {
            ++nDigit;
        }
    }

    if (nStar == 0) return true;
    if (s.back() != '*') return false;

    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> s;
        if (good()) cout << 0 << endl;
        else {
            int res = 0;
            // step 1: swap
            if (s.back() != '*') {
                int first = 0;
                while (s[first] != '*') ++first;

                swap(s[first], s.back());

                ++res;
            }
            // step 2: insert nStar + 1 - nDigit
            int nDigit = 0, nStar = 0;
            for(char c : s) {
                if (c == '*') ++nStar;
                else ++nDigit;
            }
            string t = "";
            REP(i,nStar+1-nDigit) t += '0', ++res;
            s = t + s;

            // step 3: (add+1) / 2
            nDigit = 0, nStar = 0;
            int add = 0;
            for(char c : s) {
                if (c == '*') {
                    ++nStar;
                    add = max(add, nStar + 1 - nDigit);
                }
                else ++nDigit;
            }
            cout << res + (add + 1) / 2 << endl;
        }
    }
}
