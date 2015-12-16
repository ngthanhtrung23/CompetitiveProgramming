
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

pair<int,int> x[10111];
pair<int,int> id[10111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("generators.in", "r", stdin);
    freopen("generators.out", "w", stdout);
    int n, k;
    while (cin >> n >> k) {
        memset(x, -1, sizeof x);
        FOR(i,1,n) {
            int x0, a, b, c;
            cin >> x0 >> a >> b >> c;
            FOR(turn,0,1001) {
                int cur;
                if (turn == 0) cur = x0;
                else {
                    cur = (x0 * a + b) % c;
                    x0 = cur;
                }

                if (x[i].first < 0) {
                    x[i].first = cur;
                    id[i].first = turn;
                }
                else {
                    if (x[i].first % k == cur % k) {
                        if (cur > x[i].first) {
                            x[i].first = cur;
                            id[i].first = turn;
                        }
                        continue;
                    }
                    if (x[i].first < cur) {
                        x[i].second = x[i].first;
                        id[i].second = id[i].first;

                        x[i].first = cur;
                        id[i].first = turn;
                    }
                    else if (cur > x[i].second) {
                        x[i].second = cur;
                        id[i].second = turn;
                    }
                }
            }
        }
        int sum = 0;
        FOR(i,1,n) sum += x[i].first;
        if (sum % k) {
            cout << sum << '\n';
            FOR(i,1,n) cout << id[i].first << ' ';
            cout << '\n';
            continue;
        }
        int best = -1, save = -1;
        FOR(i,1,n) {
            if (x[i].second < 0) continue;
            int cur = sum - x[i].first + x[i].second;
            if (cur <= best) continue;

            if (cur % k) {
                best = cur;
                save = i;
            }
        }
        if (best < 0) {
            cout << -1 << endl;
            continue;
        }
        cout << best << '\n';
        FOR(i,1,n) {
            if (i == save) cout << id[i].second;
            else cout << id[i].first;
            cout << ' ';
        }
        cout << endl;
    }
}
