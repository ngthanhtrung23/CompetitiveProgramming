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
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct State {
    int x, y, z;
    State() {}
    State(int x, int y, int z) : x(x), y(y), z(z) {}

    void read() { cin >> x >> y >> z; }
} start;
int n;
char a[77][77];

bool operator < (const State &a, const State &b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

State tr[77][77][77];
#define move move_
pair<int,int> move[77][77][77];

queue<State> qu;
void go(State v, State u, pair<int,int> t) {
    if (!move[v.x][v.y][v.z].first) {
        tr[v.x][v.y][v.z] = u;
        move[v.x][v.y][v.z] = t;
        qu.push(v);
    }
}

vector< pair<int,int> > res;
void print(State u) {
    if (u.x < 0) return ;
    if (move[u.x][u.y][u.z].first > 0) {
        print(tr[u.x][u.y][u.z]);
        res.push_back(move[u.x][u.y][u.z]);
    }
}

void bfs() {
    memset(move, 0, sizeof move);
    while (!qu.empty()) qu.pop();
    qu.push(start);
    tr[start.x][start.y][start.z] = State(-1, -1, -1);
    move[start.x][start.y][start.z] = make_pair(-1, -1);
    while (!qu.empty()) {
        State u = qu.front(); qu.pop();
        if (u.x + u.y + u.z == 6) {
            res.clear();
            print (u);
            cout << res.size() << endl;
            REP(i,res.size()) {
                cout << res[i].first << ' ' << res[i].second << "\n";
            }
            return ;
        }
        FOR(w,1,n) if (w != u.x && w != u.y && w != u.z) {
            // x --> w
            if (a[u.x][w] == a[u.y][u.z]) {
                State v = u; v.x = w;
                go(v, u, make_pair(u.x, w));
            }
            // y --> w
            if (a[u.y][w] == a[u.x][u.z]) {
                State v = u; v.y = w;
                go(v, u, make_pair(u.y, w));
            }
            // z --> w
            if (a[u.z][w] == a[u.x][u.y]) {
                State v = u; v.z = w;
                go(v, u, make_pair(u.z, w));
            }
        }
    }
    cout << -1 << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        start.read();
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];

        bfs();
    }
    return 0;
}
