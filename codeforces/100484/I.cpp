#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int oo = 1000111000;

int n;
map<string,int> id;
int start;
int c[111][111];
double cnt[111][111];

void init() {
    id.clear();
    FOR(i,1,100) FOR(j,1,100) {
        if (i == j) {
            c[i][j] = 0;
            cnt[i][j] = 1;
        } else {
            c[i][j] = oo;
            cnt[i][j] = 0;
        }
    }
}

int add_vertex(string name) {
    if (!id.count(name)) {
        id[name] = ++n;
    }
    return id[name];
}

pair< pair<int,int>, int> edges[111];

bool canGo(int start, int to) {
    return start != to && c[start][to] < oo && cnt[start][to];
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    cout << (fixed) << setprecision(7);
    FOR(test,1,ntest) {
        n = 0;
        init();
        string start_name;
        int m;
        cin >> m >> start_name;
        start = add_vertex(start_name);

        FOR(i,1,m) {
            int cur;
            string u, v; cin >> u >> v >> cur;

            int x = add_vertex(u);
            int y = add_vertex(v);

            edges[i] = make_pair(make_pair(x, y), cur);

            if (cur < c[x][y]) {
                c[x][y] = cur;
                cnt[x][y] = 1;
            } else if (cur == c[x][y]) {
                cnt[x][y] += 1;
            }
        }

        FOR(k,1,n)
            FOR(i,1,n)
            FOR(j,1,n)
            if (k != i && k != j) {
                if (c[i][j] > c[i][k] + c[k][j]) {
                    c[i][j] = c[i][k] + c[k][j];
                    cnt[i][j] = cnt[i][k] * cnt[k][j];
                } else if (c[i][j] == c[i][k] + c[k][j]) {
                    cnt[i][j] += cnt[i][k] * cnt[k][j];
                }
            }

        int nDest = 0;
        FOR(i,1,n)
        if (canGo(start, i)) {
            ++nDest;
        }

        cout << "Case #" << test << ":";

        double weight = 1.0 / (double) nDest;
        FOR(i,1,m) {
            cout << ' ';
            int x = edges[i].first.first, y = edges[i].first.second, cur = edges[i].second;
            if (cur > c[x][y]) {
                cout << 0.0;
                continue;
            }

            double res = 0;
            FOR(to,1,n) if (canGo(start, to)) {
                if (c[start][x] + cur + c[y][to] == c[start][to]) {
                    res += cnt[start][x] * cnt[y][to] / cnt[start][to] * weight;
                }
            }
            cout << res;
        }
        cout << endl;
    }
    return 0;
}
