
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

const int di[] = {0,1,1,0,-1,-1};
const int dj[] = {1,0,-1,-1,0,1};

map< pair<int,int>, string > board;
set< pair<int,int> > candidates, forced;

void init() {
    board.clear();
    forced.clear();
    candidates.clear();
}

int countNeighbours(int u, int v) {
    int res = 0;
    REP(dir,6) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (board.count(make_pair(uu, vv))) ++res;
    }
    return res;
}

void generateCandidates() {
    for(auto pp : board) {
        auto cur = pp.first;
        REP(dir,6) {
            auto next = make_pair(cur.first + di[dir], cur.second + dj[dir]);
            if (!board.count(next)) {
                int t = countNeighbours(next.first, next.second);

                if (t == 3) forced.insert(next);
                else candidates.insert(next);
            }
        }
    }
}

int getColor(char c) {
    if (c == 'G') return 0;
    if (c == 'R') return 1;
    if (c == 'B') return 2;
    if (c == 'Y') return 3;
    assert(0);
}

bool canPlace(int u, int v, string s) {
    if (countNeighbours(u, v) == 0) return false;

    REP(dir,6) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (board.count(make_pair(uu, vv))) {
            char mine = s[dir];
            char hers = board[make_pair(uu, vv)][ (dir + 3) % 6 ];

            if (mine != hers) return false;
        }
        else {
            char mine = s[dir];
            int cnt[4]; memset(cnt, 0, sizeof cnt);

            cnt[getColor(mine)]++;

            REP(dir2,6) {
                int x = uu + di[dir2], y = vv + dj[dir2];
                if (board.count(make_pair(x, y))) {
                    char hers = board[make_pair(x, y)][ (dir2 + 3) % 6 ];
                    cnt[getColor(hers)]++;
                }
            }


            REP(t,4) if (cnt[t] > 2) return false;
        }
    }
    return true;
}

char tmp[100111];

int getForced(vector<string> pieces) {
    int res = 0;
    for(auto piece : pieces) {
        for(auto p : forced) {
            if (canPlace(p.first, p.second, piece)) {
//                cout << p.first << ' ' << p.second << ' ' << piece << endl;
                ++res;
            }
        }
    }
    return res;
}

void removeControlled() {
    for(auto p : forced) {
        int u = p.first, v = p.second;
        REP(dir,6) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (!board.count(make_pair(uu, vv))) {
                while (countNeighbours(uu, vv) > 0 && !board.count(make_pair(uu, vv))) {
                    candidates.erase(make_pair(uu, vv));

                    uu += di[dir], vv += dj[dir];
                }
            }
        }
    }
}

int getNormal(vector<string> pieces) {
    int res = 0;
    for(auto piece : pieces) {
        for(auto p : candidates) {
            if (canPlace(p.first, p.second, piece)) {
                ++res;
            }
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        init();

        int n; scanf("%d\n", &n);
        FOR(i,1,n) {
            int u, v; string s;
            scanf("%d %d %s\n", &u, &v, &tmp);
            s = string(tmp);
            board[make_pair(u, v)] = s;
        }
        generateCandidates();

        gets(tmp);
        stringstream ss(tmp);
        string t;
        vector<string> pieces;
        while (ss >> t) {
            REP(rot,6) {
                pieces.push_back(t.substr(rot) + t.substr(0, rot));
            }
        }

        int res = getForced(pieces);
        removeControlled();
        if (res == 0) res = getNormal(pieces);

//        for(auto s : pieces) cout << s << ' '; cout << endl;

        cout << res << endl;
//        cout << "----" << endl;
    }
}
