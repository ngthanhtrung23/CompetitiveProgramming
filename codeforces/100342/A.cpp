
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

int value[MN], a[MN], can[MN], priority[MN];
int n, k;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d%d", &n, &k);

        int firstOpen = -1, lastOpen = -1;
        FOR(i,1,k+k) {
            int x; scanf("%d", &x);
            priority[i] = x;
            value[x + k] = i;
            
            if (x > 0) {
                if (firstOpen < 0) firstOpen = x;
                lastOpen = x;
            }
        }
//        DEBUG(firstOpen);
//        DEBUG(lastOpen);

        FOR(i,1,n+n) scanf("%d", &a[i]);
        memset(can, 0, sizeof can);

        stack<int> st;
        FOR(i,1,n+n) { // can be same at first (i-1) positions and diff at position i?
            if (a[i] < 0) {
                // can replace i with some open brackets?
                int right = n + n - i;
                if (value[a[i] + k] < value[lastOpen + k]
                        && right >= st.size() + 1) {
                    can[i] = 1;
                }
            }
            else {
                // can replace i with some open brackets?
                if (a[i] != lastOpen) can[i] = 1;
                else {
                    // can replace with some close brackets?
                    if (!st.empty() && value[-st.top() + k] > value[a[i] + k]) {
                        can[i] = 1;
                    }
                }
            }

            if (a[i] < 0) {
                assert(a[i] == -st.top());
                st.pop();
            }
            else st.push(a[i]);
        }
//        PR(can, n+n);
        while (!st.empty()) st.pop();

        can[0] = 1;
        FORD(change,n+n,0) if (can[change]) {
//            DEBUG(change);
            // [1, change)
            FOR(i,1,change-1) {
                if (a[i] < 0) st.pop();
                else st.push(a[i]);
            }
            // change
            if (change) {
                if (a[change] < 0) {
                    // can replace with open
                    FOR(x,value[a[change] + k], k+k)
                        if (priority[x] > 0) {
                            a[change] = priority[x];
                            break;
                        }
                }
                else {
                    FOR(x,value[a[change] + k] + 1, k+k) {
                        int u = priority[x];
                        if (u < 0) {
                            if (!st.empty() && u == -st.top()) {
                                a[change] = u;
                                break;
                            }
                        }
                        else if (u > 0) {
                            a[change] = u;
                            break;
                        }
                    }
                }
                if (a[change] < 0) st.pop();
                else st.push(a[change]);
            }

            // (change, n+n]
            FOR(i,change+1,n+n) {
                int best = 0;
                // close
                if (!st.empty()) best = -st.top();
                // open
                int right = n + n - i;
                if (right >= st.size() + 1) {
                    if (best == 0 || value[firstOpen + k] < value[best + k])
                        best = firstOpen;
                }

                a[i] = best;
                if (a[i] < 0) st.pop();
                else st.push(a[i]);
            }

            break;
        }
        FOR(i,1,n+n) printf("%d ", a[i]); puts("");
    }
}
