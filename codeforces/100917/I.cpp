#include <bits/stdc++.h>
#define int long long
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int cnt[TWO(20) + 11], nxt[TWO(20) + 11];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    REP(i,TWO(20)) {
        cnt[i] = __builtin_popcount(i) % 2;
        nxt[i] = (487237LL * i + 1011807) % TWO(20);
    }

    int can;
    vector<int> cur;
    cur.resize(TWO(20));
    REP(i,TWO(20)) cur[i] = i;

    cin >> can;
    while (true) {
        bool good = true;
        for(int x : cur) if (cnt[x] == 0) {
            good = false;
            break;
        }
        if (good) {
            cout << 200 - can << endl;
            cin >> can;
            assert(can == -1);
            break;
        }
        cout << 1 << endl;
        int prev = can;
        cin >> can;

        vector<int> go;
        if (prev > can) {
            for(int x : cur) {
                if (cnt[x] == 0) go.push_back(nxt[x]);
            }
        }
        else {
            for(int x : cur) {
                if (cnt[x] == 1) go.push_back(nxt[x]);
            }
        }
        cur = go;
        sort(cur.begin(), cur.end());
        cur.resize(unique(cur.begin(), cur.end()) - cur.begin());
    }
    return 0;
}
