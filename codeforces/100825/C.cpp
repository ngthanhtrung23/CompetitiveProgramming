
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

int maxVal, n, targetAdd;
ll target;
char op;
pair<int,int> a[111];
bool good[11][11], visited[11][11];
int qu[111], qv[111], first, last;
int res = 0;

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

bool usedRow[11][11], usedCol[11][11];
void attemptAdd(int i, int cur) {
    if (i > n) {
        ++res;
        return ;
    }
    int u = qu[i], v = qv[i];
    if (i == n) {
        int need = targetAdd - cur;
        if (need > 0 && need <= maxVal
                && !usedRow[u][need]
                && !usedCol[v][need]) {
            ++res;
        }
        return ;
    }
    FOR(val,1,maxVal) {
        if (!usedRow[u][val] && !usedCol[v][val]) {
            if (cur + val > targetAdd) continue;
            int left = n - i;
            if (cur + val + left > targetAdd) continue;
            if (cur + val + left*9 < targetAdd) continue;

            usedRow[u][val] = true;
            usedCol[v][val] = true;

            attemptAdd(i+1, val + cur);

            usedRow[u][val] = false;
            usedCol[v][val] = false;
        }
    }
}
void attemptMult(int i, ll cur) {
    if (i > n) {
        if (cur == target) ++res;
        return ;
    }
    int u = qu[i], v = qv[i];
    if (i == n) {
        if (target % cur) return ;
        int need = target / cur;
        if (need > 0 && need <= maxVal
                && !usedRow[u][need]
                && !usedCol[v][need]) {
            ++res;
        }
        return ;
    }
    FOR(val,1,maxVal) {
        if (!usedRow[u][val] && !usedCol[v][val]) {
            if (target % (cur * val)) continue;

            usedRow[u][val] = true;
            usedCol[v][val] = true;

            attemptMult(i+1, (op == '+') ? (val + cur) : (val * cur));

            usedRow[u][val] = false;
            usedCol[v][val] = false;
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> maxVal >> n >> target >> op) {
        memset(good, 0, sizeof good);
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
            good[a[i].first][a[i].second] = true;
        }
        random_shuffle(a+1, a+n+1);

        if (op == '-') {
            int res = 0;
            FOR(i,1,maxVal) FOR(j,1,maxVal)
                if (i != j)
                    if (i - j == target) res += 2;
            cout << res << endl;
            continue;
        }
        if (op == '/') {
            int res = 0;
            FOR(i,1,maxVal) FOR(j,1,maxVal)
                if (i != j)
                    if (i % j == 0 && i / j == target) res += 2;
            cout << res << endl;
            continue;
        }
        first = last = 1;
        qu[1] = a[1].first;
        qv[1] = a[1].second;
        memset(visited, 0, sizeof visited);
        visited[a[1].first][a[1].second] = 1;

        while (first <= last) {
            int u = qu[first], v = qv[first]; ++first;
            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (uu < 1 || uu > maxVal || vv < 1 || vv > maxVal) continue;
                if (!good[uu][vv]) continue;

                if (!visited[uu][vv]) {
                    visited[uu][vv] = 1;
                    ++last;
                    qu[last] = uu; qv[last] = vv;
                }
            }
        }

        res = 0;
        if (op == '+') {
            targetAdd = target;
            attemptAdd(1, 0);
        }
        if (op == '*') attemptMult(1, 1LL);
        cout << res << endl;
    }
}
