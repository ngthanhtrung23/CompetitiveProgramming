#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
int m, n;
char a[111][111];

char get(int i, int j) {
    set<char> s;
    REP(dir,4) s.insert(a[i+di[dir]][j+dj[dir]]);
    char cur = 'A'; while (s.count(cur)) ++cur;
    return cur;
}

bool canExtend(int i, int j, int i2, int j2) {
    char cur = a[i][j];
    FOR(v,j,j2+1) {
        if (a[i2+1][v] != ' ') return false;
    }
    FOR(u,i,i2+1) {
        if (a[u][j2+1] != ' ') return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        memset(a, ' ', sizeof a);

        FOR(i,1,m) FOR(j,1,n)
            if (a[i][j] == ' ') {
                char cur = get(i, j);

                a[i][j] = cur;
                int i2 = i, j2 = j;
                while (i2 < m && j2 < n && get(i, j2+1) > cur 
                        && canExtend(i, j, i2, j2)
                        && a[i2+1][j-1] != cur
                        && a[i-1][j2+1] != cur) {
                    FOR(v,j,j2+1) a[i2+1][v] = cur;
                    FOR(u,i,i2+1) a[u][j2+1] = cur;
                    ++i2; ++j2;
                }
            }

        FOR(i,1,m) {
            FOR(j,1,n) cout << a[i][j];
            cout << endl;
        }
    }
    return 0;
}
