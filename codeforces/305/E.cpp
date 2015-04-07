
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

const int MN = 5000;
int f[MN + 11];
int cnt[MN + 11];

void init() {
    f[0] = 0;
    f[1] = 1;
    FOR(i,2,MN) {
        ++cnt[f[i-2]];
        FOR(x,0,i-3) {
            int y = i - 3 - x;
            ++cnt[f[x] ^ f[y]];
        }
        f[i] = 0;
        while (cnt[f[i]]) ++f[i];

        --cnt[f[i-2]];
        FOR(x,0,i-3) {
            int y = i - 3 - x;
            --cnt[f[x] ^ f[y]];
        }
    }
}

int main() {
    init();
    string s;
    while (cin >> s) {
        int l = s.length();
        int i = 1;
        
        int sum = 0;
        vector< pair<int,int> > x;
        while (i < l-1) {
            if (s[i-1] == s[i+1]) {
                int from = i;
                while (i+2 < l && s[i] == s[i+2]) {
                    ++i;
                }
                int len = i - from + 1;
                sum ^= f[len];
                x.push_back(make_pair(from, len));
                ++i;
            }
            else ++i;
        }
//        DEBUG(sum);
//        for(auto xx : x) cout << xx.first << ' ' << xx.second << "    "; cout << endl;

        if (sum == 0) cout << "Second" << endl;
        else {
            cout << "First" << endl;

            bool ok = false;
            for(auto xx : x) {
                int i = xx.second;

                if ((sum ^ f[i] ^ f[i-2]) == 0) {
                    cout << xx.first+1 << endl;
                    break;
                }
                FOR(x,0,i-3) {
                    int y = i - 3 - x;
                    if ((sum ^ f[i] ^ f[x] ^ f[y]) == 0) {
                        cout << 1+xx.first+x+1 << endl;
                        ok = true;
                        break;
                    }
                }
                if (ok) break;
            }
        }
    }
    return 0;
}
