
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

int n;
pair<pair<int,int>,int> a[100111];

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);

    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d%d", &a[i].first.first, &a[i].first.second);
            a[i].second = i;
        }
        sort(a+1, a+n);

        int can = 1;
        int i = 0;
        vector<int> res;
        try {
            while (can < a[n].first.first) {
                int best = -1, save = -1;
                while (i+1 < n && a[i+1].first.first <= can) {
                    ++i;
                    if (a[i].first.second > best) {
                        best = a[i].first.second;
                        save = a[i].second;
                    }
                }
                if (best <= can) throw 1;

                can = best;
                res.push_back(save);
            }
            res.push_back(n);

            printf("%d\n", SZ(res));
            for(int x : res) printf("%d ", x); puts("");
        } catch (int e) {
            puts("No such luck");
        }
    }
}
