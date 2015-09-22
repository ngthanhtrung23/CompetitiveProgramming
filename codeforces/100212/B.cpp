
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

struct Node {
    Node* child[10];
    int townId;

    Node() {
        memset(child, 0, sizeof child);
        townId = 0;
    }
} *root;

struct Region {
    string code;
    int sup;

    void read() {
        cin >> sup >> code;
    }
} regions[222];
bool covered[222];

struct Town {
    vector<string> codes;
    int reg;

    void read(int id) {
        int k;
        cin >> reg >> k;
        codes.resize(k);

        Node*p = root;
        for(char c : regions[reg].code) {
            int t = c - '0';
            if (!p->child[t]) {
                p->child[t] = new Node();
            }
            p = p->child[t];
        }

        if (!k) p->townId = id;

        auto savep = p;
        
        REP(i,k) {
            cin >> codes[i];
            p = savep;

            for(char c : codes[i]) {
                int t = c - '0';
                if (!p->child[t]) p->child[t] = new Node();
                p = p->child[t];
            }

            p->townId = id;
        }
    }
} towns[10111];

int nSuper, nRegion, homeRegion, nTown;

void init() {
    memset(covered, 0, sizeof covered);
}

int cost[4][4];
int d;

int getTown(const string& phoneNum) {
    Node*p = root;
    for(char c : phoneNum) {
        p = p->child[c - '0'];
        if (!p) return -1;
        if (p->townId) return p->townId;
    }
    return -1;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("called.in", "r", stdin);
    freopen("called.out", "w", stdout);

    root = new Node();

    cin >> nTown >> nRegion >> nSuper >> d;
    FOR(i,1,nRegion) regions[i].read();
    FOR(i,1,nTown) towns[i].read(i);

    int k;
    cin >> homeRegion >> k;
    REP(i,k) {
        int reg; cin >> reg;
        covered[reg] = true;
    }
    assert(covered[homeRegion]);
    REP(i,4) REP(j,4) cin >> cost[i][j];

    ll sum = 0;
    int q; cin >> q;
    while (q--) {
        int fromTown; string phoneNum; int len;
        cin >> fromTown >> phoneNum >> len;
//        DEBUG(phoneNum);

        int a, b;
        if (towns[fromTown].reg == homeRegion) a = 0;
        else if (covered[towns[fromTown].reg]
                && regions[towns[fromTown].reg].sup == regions[homeRegion].sup) a = 1;
        else if (covered[towns[fromTown].reg]) a = 2;
        else a = 3;

        int toTown = getTown(phoneNum);
        if (toTown < 0) continue;
//        DEBUG(toTown);

        if (toTown == fromTown) b = 0;
        else if (towns[toTown].reg == towns[fromTown].reg) b = 1;
        else if (covered[ towns[toTown].reg ]) b = 2;
        else b = 3;

        sum += cost[a][b] * (ll) len;
//        DEBUG(sum);
    }
    cout << sum << endl;
}

