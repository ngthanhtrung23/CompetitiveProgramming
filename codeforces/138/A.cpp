
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

const string vowels = "aeiou";
bool vowel(char c) {
    return vowels.find(c) != string::npos;
}

string a[10111];
char tmp[10111];

int main() {
    int n, k;
    while (scanf("%d%d\n", &n, &k) == 2) {
        bool ok = true;
        FOR(i,1,4*n) {
            gets(tmp);
            a[i] = string(tmp);

            int cnt = 0;
            for(char c : a[i])
                if (vowel(c)) ++cnt;

            if (cnt < k) ok = false;

            if (ok) {
                cnt = 0;
                FORD(x,a[i].size()-1,0)
                    if (vowel(a[i][x])) {
                        ++cnt;
                        if (cnt == k) {
                            a[i] = a[i].substr(x);
                            break;
                        }
                    }
            }
        }
        if (!ok) {
            puts("NO");
            continue;
        }
//        PR(a, 4*n);

        // aaaa
        ok = true;
        REP(i,n) {
            if (a[4*i+1] != a[4*i+2]
                    || a[4*i+1] != a[4*i+3]
                    || a[4*i+1] != a[4*i+4]) {
                ok = false;
                break;
            }
        }
        if (ok) { puts("aaaa"); continue; }
        // aabb
        ok = true;
        REP(i,n) {
            if (a[4*i+1] != a[4*i+2]
                    || a[4*i+3] != a[4*i+4]) {
                ok = false;
                break;
            }
        }
        if (ok) { puts("aabb"); continue; }

        // abab
        ok = true;
        REP(i,n) {
            if (a[4*i+1] != a[4*i+3]
                    || a[4*i+2] != a[4*i+4]) {
                ok = false;
                break;
            }
        }
        if (ok) { puts("abab"); continue; }
        // abba
        ok = true;
        REP(i,n) {
            if (a[4*i+1] != a[4*i+4]
                    || a[4*i+2] != a[4*i+3]) {
                ok = false;
                break;
            }
        }
        if (ok) { puts("abba"); continue; }

        puts("NO");
    }
    return 0;
}
