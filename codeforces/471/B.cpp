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
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 2011;

int n, a[MN];
vector<int> ls[MN];

void solve1(int u) {
    cout << "YES" << endl;
    REP(turn,3) {
        FOR(i,1,2000) {
            if (i != u) {
                REP(x,ls[i].size()) cout << ls[i][x] << ' ';
            } else {
                if (turn == 0) cout << ls[i][0] << ' ' << ls[i][1] << ' ' << ls[i][2] << ' ';
                else if (turn == 1) cout << ls[i][0] << ' ' << ls[i][2] << ' ' << ls[i][1] << ' ';
                else cout << ls[i][1] << ' ' << ls[i][0] << ' ' << ls[i][2] << ' ';

                FOR(x,3,ls[i].size()-1) cout << ls[i][x] << ' ';
            }
        }
        cout << endl;
    }
}

void solve2(int u, int v) {
    cout << "YES" << endl;
    REP(turn,3) {
        FOR(i,1,2000) {
            if (i != u && i != v) {
                REP(x,ls[i].size()) cout << ls[i][x] << ' ';
            } else if (i == u) {
                if (turn == 0) cout << ls[i][0] << ' ' << ls[i][1] << ' ';
                else if (turn == 1) cout << ls[i][0] << ' ' << ls[i][1] << ' ';
                else cout << ls[i][1] << ' ' << ls[i][0] << ' ';

                FOR(x,2,ls[i].size()-1) cout << ls[i][x] << ' ';
            } else if (i == v) {
                if (turn == 0) cout << ls[i][0] << ' ' << ls[i][1] << ' ';
                else if (turn == 1) cout << ls[i][1] << ' ' << ls[i][0] << ' ';
                else cout << ls[i][1] << ' ' << ls[i][0] << ' ';

                FOR(x,2,ls[i].size()-1) cout << ls[i][x] << ' ';
            }
        }
        cout << endl;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,0,2000) ls[i].clear();

        FOR(i,1,n) {
            ls[a[i]].push_back(i);
        }

        bool ok = false;
        FOR(i,0,2000) if (ls[i].size() >= 3) {
            solve1(i);
            ok = true;
            break;
        }

        if (ok) continue;

        FOR(i,1,2000) {
            FOR(j,i+1,2000) if (ls[i].size() >= 2 && ls[j].size() >= 2) {
                solve2(i, j);
                ok = true;
                break;
            }
            if (ok) break;
        }

        if (!ok) cout << "NO" << endl;
    }
    return 0;
}
