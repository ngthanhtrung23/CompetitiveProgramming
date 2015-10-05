
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

struct Comp {
    string typ;
    int price, quality;
} a[1011];
map<string,int> minPrice;
int n, budget;

bool check(int q) {
    minPrice.clear();

    FOR(i,1,n) {
        int t = 1000111000;
        if (a[i].quality >= q) t = a[i].price;

        if (!minPrice.count(a[i].typ))
            minPrice[a[i].typ] = t;
        else minPrice[a[i].typ] = min(minPrice[a[i].typ], t);
    }

    ll need = 0;
    for(auto p : minPrice) {
        need += p.second;
    }
    return need <= budget;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> budget;
        FOR(i,1,n) {
            string tmp;
            cin >> a[i].typ >> tmp >> a[i].price >> a[i].quality;
        }
        int l = 0, r = 1000111000, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        cout << res << '\n';
    }
}
