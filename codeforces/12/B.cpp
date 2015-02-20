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

string a, b, res;
int cnt[300];

int main() {
    while (cin >> a >> b) {
        if (a == "0") {
            if (b == "0") puts("OK");
            else puts("WRONG_ANSWER");
            continue;
        }
        res = "";
        memset(cnt, 0, sizeof cnt);
        REP(i,a.length()) {
            cnt[a[i]]++;
        }

        stringstream ss; ss.clear();
        for(char i = '1'; i <= '9'; i++) if (cnt[i]) {
            ss << (char) i;
            --cnt[i];
            break;
        }
        for(char i = '0'; i <= '9'; i++) {
            while (cnt[i]) {
                --cnt[i];
                ss << (char) i;
            }
        }
        ss >> res;
        if (res != b) puts("WRONG_ANSWER"); else puts("OK");
    }
    return 0;
}