
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

const int MN = 5011;
map< vector<int>, int > cnt;
char tmp[MN];
int m, n;

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
    while (scanf("%d%d\n", &m, &n) == 2) {
        cnt.clear();

        vector<int> cur; FOR(i,1,8) cur.push_back(i); cnt[cur] = 0;
        vector<int> res = cur;

        FOR(i,1,m) {
            scanf("%s\n", &tmp[1]);
            vector<int> cur;
            FOR(j,1,n) if (tmp[j] == '1') {
                cur.push_back(j);
            }
            if (cur.size() > 15 || cur.size() < 8) continue;

            cnt[cur] += 1;
        }

        int best = 0;
        for(auto p : cnt)
            if (p.second > best) {
                best = p.second;
                res = p.first;
            }

        memset(tmp, '0', sizeof tmp);
        tmp[n+1] = 0;
        for(int x : res) tmp[x] = '1';
        puts(tmp + 1);
    }
}
