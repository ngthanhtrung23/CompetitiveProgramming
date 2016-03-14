#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define SZ(x) ((int) (x).size())
#define ll long long
using namespace std;

struct Pattern {
    int n;
    vector<string> rep;
    int cached;
    string name;

    ll cntMiddle;
    ll cntTotal;
    vector<int> top, bottom, left, right;
    vector<vector< pair<int,int> > > regions;
} a[222];
map<string,int> id;

const int TOP = 0;
const int BOTTOM = 1;
const int LEFT = 2;
const int RIGHT = 3;

vector<int> merge(const vector<int>&a, const vector<int>& b) {
    vector<int> res = a;
    res.insert(res.end(), b.begin(), b.end());
    return res;
}

int vertex[4][4][1<<16];
int lab[2000111];
struct DSU {
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int regionId[2000111];

void solve(int u) {
    if (a[u].cached) return ;
    a[u].cached = 1;

    int x = id[a[u].rep[0]];
    int y = id[a[u].rep[1]];
    int z = id[a[u].rep[2]];
    int t = id[a[u].rep[3]];

    solve(x); solve(y); solve(z); solve(t);

    a[u].n = 2 * a[x].n;

    a[u].top = merge(a[x].top, a[y].top);
    a[u].bottom = merge(a[z].bottom, a[t].bottom);
    a[u].left = merge(a[x].left, a[z].left);
    a[u].right = merge(a[y].right, a[t].right);

    int nid = 0;
    REP(part,4) {
        int reg;
        if (part == 0) reg = x;
        if (part == 1) reg = y;
        if (part == 2) reg = z;
        if (part == 3) reg = t;

        REP(dir,4) REP(i,a[x].n) vertex[part][dir][i] = 0;

        REP(i,a[x].n) {
            if (a[reg].top[i]) vertex[part][TOP][i] = ++nid;
            if (a[reg].bottom[i]) vertex[part][BOTTOM][i] = ++nid;
            if (a[reg].left[i]) vertex[part][LEFT][i] = ++nid;
            if (a[reg].right[i]) vertex[part][RIGHT][i] = ++nid;
        }
    }
    REP(i,nid+1) regionId[i] = -1;

    DSU dsu; dsu.init(nid);

    int turn = 0;
    REP(turn,4) {
        int dir;
        if (turn == 0) dir = x;
        else if (turn == 1) dir = y;
        else if (turn == 2) dir = z;
        else dir = t;
        for(auto r : a[dir].regions) {
            int u = vertex[turn][r[0].first][r[0].second];
            if (!u) continue;
            for(auto p : r) {
                int v = vertex[turn][p.first][p.second];
                if (!v) continue;
                dsu.merge(u, v);
            }
        }
    }

    REP(i,a[x].n) {
        // connect x - y
        if (a[x].right[i] && a[y].left[i]) {
            dsu.merge(vertex[0][RIGHT][i], vertex[1][LEFT][i]);
        }
        // connect z - t
        if (a[z].right[i] && a[t].left[i]) {
            dsu.merge(vertex[2][RIGHT][i], vertex[3][LEFT][i]);
        }
        // connect x - z
        if (a[x].bottom[i] && a[z].top[i]) {
            dsu.merge(vertex[0][BOTTOM][i], vertex[2][TOP][i]);
        }
        // connect y - t
        if (a[y].bottom[i] && a[t].top[i]) {
            dsu.merge(vertex[1][BOTTOM][i], vertex[3][TOP][i]);
        }
    }

    // count total number of regions
    int totalRegion = 0;
    FOR(i,1,nid) if (lab[i] < 0) ++totalRegion;

    // a[x].top
    REP(i,a[x].n) if (vertex[0][TOP][i]) {
        int v = dsu.getRoot(vertex[0][TOP][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(TOP, i));
    }
    // a[y].top
    REP(i,a[x].n) if (vertex[1][TOP][i]) {
        int v = dsu.getRoot(vertex[1][TOP][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(TOP, a[x].n + i));
    }
    // a[z].bottom
    REP(i,a[x].n) if (vertex[2][BOTTOM][i]) {
        int v = dsu.getRoot(vertex[2][BOTTOM][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(BOTTOM, i));
    }
    // a[t].bottom
    REP(i,a[x].n) if (vertex[3][BOTTOM][i]) {
        int v = dsu.getRoot(vertex[3][BOTTOM][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(BOTTOM, a[x].n + i));
    }
    // a[x].left
    REP(i,a[x].n) if (vertex[0][LEFT][i]) {
        int v = dsu.getRoot(vertex[0][LEFT][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(LEFT, i));
    }
    // a[z].left
    REP(i,a[x].n) if (vertex[2][LEFT][i]) {
        int v = dsu.getRoot(vertex[2][LEFT][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(LEFT, a[x].n + i));
    }
    // a[y].right
    REP(i,a[x].n) if (vertex[1][RIGHT][i]) {
        int v = dsu.getRoot(vertex[1][RIGHT][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(RIGHT, i));
    }
    // a[t].right
    REP(i,a[x].n) if (vertex[3][RIGHT][i]) {
        int v = dsu.getRoot(vertex[3][RIGHT][i]);
        if (regionId[v] < 0) { regionId[v] = SZ(a[u].regions); vector< pair<int,int> > tmp; a[u].regions.push_back(tmp); }
        a[u].regions[ regionId[v] ].push_back(make_pair(RIGHT, a[x].n + i));
    }

    a[u].cntMiddle = a[x].cntMiddle + a[y].cntMiddle + a[z].cntMiddle + a[t].cntMiddle;
    a[u].cntTotal = totalRegion + a[u].cntMiddle;
    a[u].cntMiddle += totalRegion - SZ(a[u].regions);

//    cout << "--------------------------" << endl;
//    DEBUG(a[u].name);
//    PR0(a[u].top, SZ(a[u].top));
//    PR0(a[u].bottom, SZ(a[u].bottom));
//    PR0(a[u].left, SZ(a[u].left));
//    PR0(a[u].right, SZ(a[u].right));

//    DEBUG(a[u].cntMiddle);
//    DEBUG(a[u].cntTotal);

//    for(auto r : a[u].regions) {
//        for(auto p : r) cout << p.first << ' ' << p.second << "   "; cout << endl;
//    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    string s;

    // '0'
    id["0"] = 0;
    int n = 0;
    a[0].n = 1;
    a[0].cached = 1;
    a[0].cntMiddle = 0;
    a[0].cntTotal = 0;

    a[0].top.push_back(0);
    a[0].bottom = a[0].top;
    a[0].left = a[0].top;
    a[0].right = a[0].top;

    a[0].regions.clear();

    // '1'
    n = 1;
    id["1"] = 1;
    a[1].n = 1;
    a[1].cached = 1;
    a[1].cntMiddle = 0;
    a[1].cntTotal = 1;
    a[1].top.push_back(1);
    a[1].bottom = a[1].top;
    a[1].left = a[1].top;
    a[1].right = a[1].top;

    vector< pair<int,int> > tmp;
    a[1].regions.push_back(tmp);
    a[1].regions[0].push_back(make_pair(TOP, 0));
    a[1].regions[0].push_back(make_pair(BOTTOM, 0));
    a[1].regions[0].push_back(make_pair(LEFT, 0));
    a[1].regions[0].push_back(make_pair(RIGHT, 0));

    while (getline(cin, s)) {
        string tmp = "";
        for(char c : s) if (c != ' ') tmp += c;
        s = tmp;

        if (s == "") break;
        ++n;
        int equal = s.find('=');
        string name = s.substr(0, equal);

        tmp = s.substr(equal + 1);
        REP(i,SZ(tmp)) if (tmp[i] == ',') tmp[i] = ' ';

        stringstream ss(tmp);
        a[n].rep.resize(4);
        REP(t,4) ss >> a[n].rep[t];

        id[name] = n;
//        cout << name << ' ';
//        PR0(a[n].rep, SZ(a[n].rep));
        a[n].name = name;
    }
//    DEBUG(id["Map"]);
    solve(id["Map"]);
    cout << a[ id["Map"] ].cntTotal << endl;
}
