
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

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> cur;
        cur.clear();
        FOR(i,1,n) {
            int a; scanf("%d", &a);
            if (a == 0) {
                if (SZ(cur) == 0) {
                    puts("0");
                }
                else if (SZ(cur) == 1) {
                    puts("pushStack");
                    puts("1 popStack");
                }
                else if (SZ(cur) == 2) {
                    puts("pushStack");
                    puts("pushQueue");
                    puts("2 popStack popQueue");
                }
                else {
                    int x = -1, y = -1, z = -1;
                    REP(i,SZ(cur)) {
                        if (x == -1 || cur[i] > cur[x]) x = i;
                    }
                    REP(i,SZ(cur)) if (i != x) {
                        if (y == -1 || cur[i] > cur[y]) y = i;
                    }
                    REP(i,SZ(cur)) if (i != x && i != y) {
                        if (z == -1 || cur[i] > cur[z]) z = i;
                    }

                    REP(i,SZ(cur)) {
                        if (i == x) puts("pushStack");
                        else if (i == y) puts("pushQueue");
                        else if (i == z) puts("pushBack");
                        else puts("pushFront");
                    }
                    puts("3 popStack popQueue popBack");
                }
                cur.clear();
            }
            else {
                cur.push_back(a);
            }
        }
        REP(i,SZ(cur)) puts("pushStack");
    }
}
