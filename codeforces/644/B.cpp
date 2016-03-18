#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
int n, b, t[MN], d[MN], res[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%lld%lld", &n, &b) == 2) {
        set< pair<int,int> > events;
        FOR(i,1,n) {
            scanf("%lld%lld", &t[i], &d[i]);
            events.insert(make_pair(t[i], +i));
        }
        int free = 1;

        queue<int> qu;

        memset(res, -1, sizeof res);

        while (!events.empty()) {
            auto it = events.begin();
            auto e = *it; events.erase(it);

            if (e.second > 0) {
                // a new event arrive
                if (free && qu.empty()) {
                    // case 1 --> execute immediately
                    res[ e.second ] = e.first + d[e.second];
                    free = 0;
                    events.insert(make_pair(e.first + d[e.second], -1));
                }
                else if (SZ(qu) < b) {
                    // case 2 --> push to queue
                    qu.push(e.second);
                }
                else {
                    // case 3 --> ignore
                }
            }
            else {
                free = 1;
                if (!qu.empty()) {
                    free = 0;
                    int i = qu.front(); qu.pop();
                    res[i] = e.first + d[i];
                    events.insert(make_pair(e.first + d[i], -1));
                }
            }
        }
        FOR(i,1,n) printf("%lld ", res[i]); puts("");
    }
}