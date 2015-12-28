
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

int x[100111], nx;
vector< vector<int> > res;
vector<int> cur;
int sign;

void attempt(int i, int cnt) {
    if (i > nx) {
        if ((cnt % 2 == 0 && sign == 1)
                || (cnt % 2 == 1 && sign == -1)) {
            res.push_back(cur);
        }
        return ;
    }

    REP(turn,2) {
        int t;
        if (turn == 1) t = -x[i];
        else t = x[i];

        if (i > 1 && abs(t) == abs(cur.back()) && t < cur.back()) continue;

        cur.push_back(t);
        attempt(i+1, cnt + turn);
        cur.pop_back();
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("product.in", "r", stdin);
    freopen("product.out", "w", stdout);

    int n;
    while (cin >> n) {
        sign = 1;
        if (n < 0) {
            sign = -1;
            n = -n;
        }
        nx = 0;
        for(int i = 2; i*i <= n; ++i) {
            while (n % i == 0) {
                x[++nx] = i;
                n /= i;
            }
        }
        if (n > 1) {
            x[++nx] = n;
        }
        cur.clear();
        res.clear();
        attempt(1, 0);

        REP(i,SZ(res)) {
            sort(res[i].begin(), res[i].end());
        }
        sort(res.begin(), res.end());
//        res.resize(unique(res.begin(), res.end()) - res.begin());
        cout << SZ(res) << '\n';
        for(auto p : res) {
            for(auto x : p) cout << x << ' ';
            cout << '\n';
        }
    }
}
