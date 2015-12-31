
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

const int MN = 211;

vector<vector<int> > f[MN];

struct A {
    string name;
    int val;
    bool isDouble;
} a[MN];
int n;

string toString(int n) {
    stringstream ss; ss << n;
    return ss.str();
}

void initPieces() {
    FOR(i,1,20) {
        // single
        ++n;
        a[n].name = toString(i);
        a[n].val = i;
        a[n].isDouble = false;

        // double
        ++n;
        a[n].name = "D" + toString(i);
        a[n].val = i*2;
        a[n].isDouble = true;

        // triple
        ++n;
        a[n].name = "T" + toString(i);
        a[n].val = i*3;
        a[n].isDouble = false;
    }
    // bull
    ++n;
    a[n].name = "25";
    a[n].val = 25;
    a[n].isDouble = false;

    ++n;
    a[n].name = "Bull";
    a[n].val = 50;
    a[n].isDouble = true;

}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("darts.in", "r", stdin);
    freopen("darts.out", "w", stdout);

    initPieces();

    int x;
    while (cin >> x) {
        vector< vector<int> > res;
        FOR(i,1,n)
            if (a[i].isDouble && a[i].val == x) {
                res.push_back({i});
            }
        FOR(i,1,n) FOR(j,1,n)
            if (a[j].isDouble && a[i].val + a[j].val == x) {
                res.push_back({i, j});
            }
        FOR(i,1,n) FOR(j,1,n) FOR(k,1,n)
            if (a[k].isDouble && a[i].val + a[j].val + a[k].val == x) {
                res.push_back({i, j, k});
            }
        cout << SZ(res) << '\n';
        for(auto p : res) {
            for(auto x : p) cout << a[x].name << ' '; cout << '\n';
        }
        cout << '\n';
    }
}
