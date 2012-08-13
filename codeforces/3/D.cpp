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
const int MN = 50111;

char s[MN];
int a[MN], b[MN];
set< pair<int,int> > ls;

int main() {
    while (gets(s)) {
        int k = 0;
        int n = strlen(s);
        REP(i,n) if (s[i] == '?') ++k;
        FOR(i,1,k) scanf("%d%d", &a[i], &b[i]);

        int cur = 0, sum = 0;
        long long res = 0;
        ls.clear();

        REP(i,n) {
            if (s[i] == '(') {
                ++sum;
            }
            else if (s[i] == ')') {
                --sum;
            }
            else if (s[i] == '?') {
                ++cur;
                --sum;
                res += b[cur];
                ls.insert(MP(a[cur]-b[cur], i));
                s[i] = ')';
            }

            if (sum < 0) {
                if (ls.size() == 0) {
                    puts("-1");
                    return 0;
                }
                pair<int,int> now = *ls.begin(); ls.erase(ls.begin());
                int j = now.S;
                s[j] = '(';
                res += now.F;
                sum += 2;
            }
        }
        if (sum) {
            puts("-1");
            return 0;
        }
        cout << res << endl;
        cout << s << endl;
        gets(s);
    }
    return 0;
}
