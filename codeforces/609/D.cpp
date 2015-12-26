
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;

int nDays, nGadget, need, nBurles;
ll a[MN], b[MN];
pair<ll,int> mina[MN], minb[MN];
pair<ll,int> x[MN];

ll t[MN], c[MN];

int get(int n) {
    FOR(i,1,nGadget) {
        x[i].second = i;
        if (t[i] == 1) x[i].first = mina[n].first * c[i];
        else x[i].first = minb[n].first * c[i];
    }

    sort(x+1, x+nGadget+1);
    int can = 0;
    ll sum = 0;
    FOR(i,1,nGadget) {
        if (sum + x[i].first <= nBurles) {
            ++can;
            sum += x[i].first;
        }
    }
    return can;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> nDays >> nGadget >> need >> nBurles) {
        FOR(i,1,nDays) {
            cin >> a[i];
            auto cur = make_pair(a[i], i);
            if (i == 1) mina[i] = cur;
            else mina[i] = min(mina[i-1], cur);
        }
        FOR(i,1,nDays) {
            cin >> b[i];
            auto cur = make_pair(b[i], i);
            if (i == 1) minb[i] = cur;
            else minb[i] = min(minb[i-1], cur);
        }

        FOR(i,1,nGadget) cin >> t[i] >> c[i];

        int l = 1, r = nDays, res = nDays+1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (get(mid) >= need) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        if (res > nDays) {
            cout << -1 << endl;
        }
        else {
            cout << res << endl;
            get(res);
            FOR(i,1,need) {
                int u = x[i].second, d = -1;
                if (t[u] == 1) d = mina[res].second;
                else d = minb[res].second;
                cout << u << ' ' << d << endl;
            }
        }
    }
}
