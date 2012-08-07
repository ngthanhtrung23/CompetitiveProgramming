
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

char s[5011], t[5011], a[5011];
int cnt[300], ls, lt, now[300];

bool check(int start) {
    FOR(c,'a','z') now[c] = cnt[c];

    FOR(i,start,max(ls,lt)-1) {
        char need = t[i];
        char can = 'z';
        while (!now[can] && can >= 'a') --can;
        if (!now[can]) can = 0;

        if (can < need) return false;
        if (can > need) return true;

        if (can) --now[can];
    }
    return false;
}

int main() {
    while (gets(s)) {
        gets(t);
        ls = strlen(s), lt = strlen(t);
        memset(a, 0, sizeof a);
        memset(cnt, 0, sizeof cnt);

        REP(i,ls) {
            cnt[s[i]]++;
        }

        bool ok = true, bigger = false;

        REP(i,ls) {
            char res = ' ';
            FOR(c,'a','z') if (cnt[c]) {
                if (bigger) {
                    res = c;
                    --cnt[c];
                    break;
                }
                if (!bigger && c < t[i]) continue;

                if (c > t[i]) {
                    bigger = true;
                    res = c;
                    --cnt[c];
                    break;
                }
                cnt[c]--;
                if (!check(i+1)) ++cnt[c];
                else {
                    res = c;
                    break;
                }
            }
            if (res == ' ') {
                ok = false;
                break;
            }
            else a[i] = res;
        }
        if (!bigger || !ok) puts("-1");
        else puts(a);
    }
    return 0;
}
