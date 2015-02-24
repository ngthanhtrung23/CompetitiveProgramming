#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 100111;
int n, k, a[MN], x[MN], nx;
bool unknown[MN], visited[MN], ok;
char tmp[111];

#define ll long long
ll sum_range(ll x, ll y) {
    if (x > y) return 0;

    if (x < 0 && y > 0) {
        return sum_range(x, -1) + sum_range(1, y);
    }
    else {
        if (x < 0) {
            x = -x;
            y = -y;
            swap(x, y);
        }
        ll len = y - x + 1;
        return (x + y) * len / 2;
    }
}

void solve() {
    int i = 0;
    x[0] = 0;
    x[nx+1] = n+1;
    unknown[n+1] = 0;
    a[0] = -1000111000;
    a[n+1] = -a[0];

    while (i <= nx) {
        int j = i+1;
        while (j <= nx+1 && unknown[x[j]]) ++j;

        int len = j - i - 1;
//        PR0((x+i), len+2);

        if (a[x[i]] > a[x[j]]) {
            ok = false;
            return ;
        }

        if (len > 0) {
            int from = a[x[i]] + 1;
            int to = a[x[j]] - 1;
            int values = to - from + 1;
            if (values < len) {
                ok = false;
                return ;
            }

            ll left = from, right = to-len+1;
            REP(turn,77) {
                ll x1 = (left + left + right) / 3;
                ll x2 = (left + right + right) / 3;

                if (x1 == x2) break;

                ll y1 = sum_range(x1, x1 + len - 1);
                ll y2 = sum_range(x2, x2 + len - 1);

                if (y1 < y2) right = x2;
                else left = x1;
            }

            ll best = left;
            FOR(i,left+1,right)
                if (sum_range(i, i + len - 1) < sum_range(best, best + len - 1))
                    best = i;

            FOR(k,i+1,j-1)
                a[x[k]] = best++;
        }

        i = j;
    }
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) {
            scanf("%s", &tmp);
            if (tmp[0] == '?') {
                unknown[i] = true;
                a[i] = 0;
            }
            else {
                unknown[i] = false;
                sscanf(tmp, "%d", &a[i]);
            }
        }
//        PR(a, n);
//        PR(unknown, n);

        memset(visited, 0, sizeof visited);
        ok = true;
        FOR(i,1,n) if (!visited[i]) {
            int u = i;
            nx = 0;
            while (u <= n) {
                visited[u] = true;
                x[++nx] = u;
                u += k;
            }
//            PR(x, nx);

            solve();
        }
        if (ok) {
            FOR(i,1,n-k+1) if (a[i] >= a[i+k]) {
                ok = false;
                break;
            }
            if (!ok) {
                puts("Incorrect sequence");
                continue;
            }
            FOR(i,1,n) printf("%d ", a[i]);
            puts("");
        }
        else {
            puts("Incorrect sequence");
        }
    }
    return 0;
}

