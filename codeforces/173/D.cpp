#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define SZ(X) ((int) (X).size())
using namespace std;

const int MN = 100111;
int n, m, k;
set<int> ke[MN];
int color[MN], res[MN];

void dfs(int u, int c) {
    color[u] = c;
    for(int v : ke[u]) {
        if (color[v] < 0) {
            dfs(v, 1-c);
        }
    }
}

#define left _left
#define right _right
vector<int> left, right;

void solve() {
    int now = 0;
    for(int i = 0; i < SZ(left); i += 3) {
        ++now;
        res[left[i]] = res[left[i+1]] = res[left[i+2]] = now;
    }
    for(int i = 0; i < SZ(right); i += 3) {
        ++now;
        res[right[i]] = res[right[i+1]] = res[right[i+2]] = now;
    }

    puts("YES");
    FOR(i,1,n) printf("%d ", res[i]);
    puts("");
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].insert(v);
            ke[v].insert(u);
        }
        memset(color, -1, sizeof color);
        FOR(i,1,n) if (color[i] < 0) {
            dfs(i, 0);
        }

        left.clear(); right.clear();
        FOR(i,1,n) {
            if (color[i]) right.push_back(i);
            else left.push_back(i);
        }

        if (SZ(left) % 3 == 0) {
            solve();
            continue;
        }
        else {
            if (SZ(left) % 3 == 2) swap(left, right);
            bool ok = false;
            REP(i,SZ(left)) {
                int x = left[i];
                if (SZ(ke[x]) <= SZ(right) - 2) {
                    ok = true;
                    int y = -1, z = -1;
                    REP(t,SZ(right)) if (!ke[x].count(right[t])) {
                        if (y < 0) y = t;
                        else if (z < 0) z = t;
                        else break;
                    }

                    int k = n/3;
                    res[left[i]] = res[right[y]] = res[right[z]] = k;

                    left.erase(left.begin() + i);
                    if (y < z) swap(y, z);
                    right.erase(right.begin() + y);
                    right.erase(right.begin() + z);
                    break;
                }
            }
            if (ok) {
                solve();
                continue;
            }
            else {
                int i1 = -1, i2 = -1;
                REP(i,SZ(right)) {
                    int x = right[i];
                    if (SZ(ke[x]) <= SZ(left) - 2) {
                        if (i1 < 0) i1 = i;
                        else if (i2 < 0) i2 = i;
                        else break;
                    }
                }

                if (i1 >= 0 && i2 >= 0) {
                    int x1 = right[i1], x2 = right[i2];
                    int y1 = -1, y2 = -1, y3 = -1, y4 = -1;
                    REP(t,SZ(left)) {
                        if (!ke[x1].count(left[t])) {
                            if (y1 < 0) y1 = t;
                            else if (y2 < 0) y2 = t;
                            else break;
                        }
                    }
                    int k = n / 3;
                    if (y1 >= 0 && y2 >= 0) {
                        res[right[i1]] = res[left[y1]] = res[left[y2]] = k;
                        --k;

                        REP(t,SZ(left)) if (!ke[x2].count(left[t])) {
                            if (y3 < 0) y3 = t;
                            else if (y4 < 0) y4 = t;
                            else break;
                        }
                        if (y3 >= 0 && y4 >= 0) {
                            res[right[i2]] = res[left[y3]] = res[left[y4]] = k;
                            if (i1 < i2) swap(i1, i2);
                            right.erase(right.begin() + i1);
                            right.erase(right.begin() + i2);

                            int yy[4] = {y1, y2, y3, y4};
                            sort(yy, yy+4);

                            left.erase(left.begin() + yy[3]);
                            left.erase(left.begin() + yy[2]);
                            left.erase(left.begin() + yy[1]);
                            left.erase(left.begin() + yy[0]);
                            solve();
                            continue;
                        }
                    }
                }
            }
        }
        puts("NO");
    }
    return 0;
}

