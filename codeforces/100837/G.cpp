
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

struct Node {
    int x;
    Node* next;
};

Node* createNode(int _x) {
    Node* res = new Node();
    res->x = _x;
    res->next = 0;
    return res;
}

struct List {
    Node* head, *tail;

    List() { head = tail = 0; }

    void print() {
        Node* p = head;
        while (p) {
            cout << p->x << ' ';
            p = p->next;
        }
        cout << endl;
    }
};

const int MN = 100111;
int lab[MN];
List cur[MN];
int n, nHor, q;

struct Hor {
    int y;
    vector<int> x;

    friend istream& operator >> (istream& cin, Hor& a) {
        cin >> a.y;
        int l; cin >> l;
        a.x.resize(l);
        REP(i,l) cin >> a.x[i];
        return cin;
    }
} hors[MN];

bool operator < (const Hor& a, const Hor& b) {
    return a.y > b.y;
}

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    if (u == v) return ;

    if (u > v) swap(u, v);
    // u < v
    lab[u] += lab[v];
    lab[v] = u;
}

int res[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("g.in", "r", stdin);
    freopen("g.out", "w", stdout);
    while (cin >> n >> nHor >> q) {
        FOR(i,1,nHor) cin >> hors[i];
        sort(hors+1, hors+nHor+1);

        FOR(i,1,n) {
            lab[i] = -1;
            Node* p = createNode(i);
            cur[i].head = cur[i].tail = p;
        }
        FOR(i,1,nHor) {
//            DEBUG(hors[i].y);
            vector<int> x;
            for(int u : hors[i].x) {
                x.push_back(getRoot(u));
            }
            sort(x.begin(), x.end());
            int u0 = x[0];

            FOR(i,1,SZ(x)-1) {
                int u = x[i];
                merge(u, u0);
                cur[u0].tail->next = cur[u].head;
                cur[u0].tail = cur[u].tail;
            }
//            PR0(x, SZ(x));
//            cur[u0].print();
        }
        int t = 0;
        FOR(i,1,n) if (lab[i] < 0) {
            Node* p = cur[i].head;
            while (p) {
                res[++t] = p->x;
                p = p->next;
            }
        }
        while (q--) {
            int id; cin >> id;
            cout << res[id] << '\n';
        }
        cout << '\n';
    }
}
