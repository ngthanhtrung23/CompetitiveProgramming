
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
const int MN = 200111;
int n;

multiset<int> hs, vs, h_gap, v_gap;

int main() {
    int X, Y, n;
    while (scanf("%d%d%d\n", &X, &Y, &n) == 3) {
        hs.clear(); vs.clear(); h_gap.clear(); v_gap.clear();

        hs.insert(0); hs.insert(Y); h_gap.insert(-Y);
        vs.insert(0); vs.insert(X); v_gap.insert(-X);

        while (n--) {
            char c; int u;
            scanf("%c %d\n", &c, &u);
            if (c == 'H') {
                auto it = hs.lower_bound(u);
                int b = *it;
                --it;
                int a = *it;
                h_gap.erase(h_gap.find(a - b));
                
                hs.insert(u);
                h_gap.insert(a - u);
                h_gap.insert(u - b);
            }
            else {
                auto it = vs.lower_bound(u);
                int b = *it;
                --it;
                int a = *it;
                v_gap.erase(v_gap.find(a - b));

                vs.insert(u);
                v_gap.insert(a - u);
                v_gap.insert(u - b);
            }

            printf("%lld\n", (*h_gap.begin()) * (ll) (*v_gap.begin()));
        }
    }
    return 0;
}
