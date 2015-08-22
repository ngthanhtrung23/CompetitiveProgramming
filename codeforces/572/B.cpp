
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
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    int n, s;
    while (cin >> n >> s) {
        map<int,int> buy, sell;
        while (n--) {
            char typ; int p, val;
            cin >> typ >> p >> val;
            if (typ == 'B') buy[-p] += val;
            else sell[p] += val;
        }
        int cnt = 0;
        vector< pair<int,int> > x;
        for(auto p : sell) {
            x.push_back(p);
            ++cnt; if (cnt == s) break;
        }
        reverse(x.begin(), x.end());
        for(auto p : x) {
            printf("S %d %d\n", p.first, p.second);
        }
        cnt = 0;
        for(auto p : buy) {
            printf("B %d %d\n", -p.first, p.second);
            ++cnt; if (cnt == s) break;
        }
    }
}
