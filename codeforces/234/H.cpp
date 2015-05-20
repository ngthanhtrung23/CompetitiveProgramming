
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

const int MN = 200111;

int a[MN], b[MN], c[MN], id[MN];

int main() {
    ios :: sync_with_stdio(false);
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int na, nb;
    while (cin >> na) {
        FOR(i,1,na) cin >> a[i];
        cin >> nb;
        FOR(i,1,nb) cin >> b[i];

        int need = 0;
        memset(c, 0, sizeof c);

        int ia = na, ib = nb;
        FORD(i,na+nb,1) {
            if (ia && a[ia] == need) {
                id[i] = ia;
                c[i] = need;
                --ia;
            }
            else if (ib && b[ib] == need) {
                id[i] = na+ib;
                c[i] = need;
                --ib;
            }
            else need = 1-need, ++i;
        }
//        PR(c, na+nb);
        FOR(i,1,na+nb) cout << id[i] << ' '; cout << endl;

        vector<int> res;
        FOR(i,1,na+nb) if (c[i] != c[i+1]) res.push_back(i);
        cout << res.size() << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
