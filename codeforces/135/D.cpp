
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

char a[1011][1011];
int m, n, now, visited[1011][1011], done[1011][1011];
const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

bool outside(int u, int v) {
    return u < 1 || v < 1 || u > m || v > n;
}

pair<int,int> qu[1011*1011];
int first, last;

int bfs(int u, int v) {
    visited[u][v] = ++now;
    first = last = 1;
    qu[1] = make_pair(u, v);
    
    bool canGoOutside = false;
    while (first <= last) {
        int u = qu[first].first, v = qu[first].second; ++first;

        FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
            int uu = u + di, vv = v + dj;
            if (outside(uu, vv)) {
                canGoOutside = true;
                continue;
            }

            if (a[uu][vv] == '0' && visited[uu][vv] != now) {
                visited[uu][vv] = now;
                ++last;
                qu[last] = make_pair(uu, vv);
            }
        }
    }
    if (canGoOutside) return 0;

//    cout << "Bfs at: " << u << ' ' << v << endl;
    vector< pair<int,int> > ones;
    FOR(t,1,last) {
        int u = qu[t].first, v = qu[t].second;

        FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
            int uu = u + di, vv = v + dj;
            if (a[uu][vv] == '1') {
                if (visited[uu][vv] != now) {
                    ones.push_back(make_pair(uu, vv));
                    visited[uu][vv] = now;
                }
            }
        }
    }

//    for(auto p : ones) cout << p.first << ' ' << p.second << "     "; cout << endl;
    if (ones.empty()) return 0;

    for(auto p : ones) {
        int cnt = 0;
        REP(dir,4) {
            int u = p.first + di[dir], v = p.second + dj[dir];
            if (a[u][v] == '1' && visited[u][v] == now) ++cnt;
        }
        if (cnt != 2) return 0;
    }
//    cout << "HAS 2 NEIGHBOURS" << endl;

    queue< pair<int,int> > q;
    u = ones[0].first, v = ones[0].second;
    done[u][v] = now;
    q.push(make_pair(u, v));

    while (!q.empty()) {
        u = q.front().first, v = q.front().second; q.pop();
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (a[uu][vv] == '1' && visited[uu][vv] == now && done[uu][vv] != now) {
                done[uu][vv] = now;
                q.push(make_pair(uu, vv));
            }
        }
    }
    for(auto p : ones)
        if (done[p.first][p.second] != now) return 0;
//    cout << "CONNECTED" << endl;

    return ones.size();
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        memset(a, ' ', sizeof a);
        FOR(i,1,m) {
            string tmp; cin >> tmp;
            FOR(j,1,n) a[i][j] = tmp[j-1];
        }

//        FOR(i,1,m) {
//            FOR(j,1,n) cout << a[i][j];
//            cout << endl;
//        }

        int res = 0;
        FOR(i,1,m-1) FOR(j,1,n-1)
            if (a[i][j] + a[i][j+1] + a[i+1][j] + a[i+1][j+1] == '1' * 4) {
                res = 4;
            }

        now = 0;
        memset(visited, 0, sizeof visited);
        memset(done, 0, sizeof done);
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '0' && !visited[i][j]) {
            res = max(res, bfs(i, j));
        }
        cout << res << endl;
    }
    return 0;
}

