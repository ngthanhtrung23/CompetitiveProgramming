#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

int n, n1, n2;
pair<int,int> A[400111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        int cur = 0;
        n1 = n2 = 0;
        FOR(turn,1,2) {
            if (turn == 2) cin >> n;
            FOR(i,1,n) {
                int u; cin >> u;
                A[++cur] = make_pair(u, turn);
            }
        }
        sort(A+1, A+cur+1);
        int best = -1000111000, savea = 0, saveb = 0;
        n = cur;
        FOR(i,1,cur) if (A[i].second == 1) ++n1; else ++n2;
        int x1 = 0, x2 = 0;
        
        FOR(i,0,cur) {
            int a = (x1 * 2 + n1 * 3);
            int b = (x2 * 2 + n2 * 3);
            int now = a - b;
            if (now > best || (now == best && a > savea)) {
                best = now;
                savea = a;
                saveb = b;
            }
            if (A[i+1].second == 1) --n1, ++x1; else --n2, ++x2;
        }
        cout << savea << ':' << saveb << endl;
    }
    return 0;
}
