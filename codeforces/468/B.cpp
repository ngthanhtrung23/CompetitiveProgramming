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

const int MN = 100111;
int n, a, b, x[MN], lab[MN];
map<int,int> id;
bool notA[MN], notB[MN];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    if (u == v) return ;
    lab[u] += lab[v];
    lab[v] = u;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> a >> b) {
        id.clear();
        memset(lab, -1, sizeof lab);
        
        FOR(i,1,n) {
            cin >> x[i];
            id[x[i]] = i;
        }

        memset(notA, false, sizeof notA);
        memset(notB, false, sizeof notB);

        FOR(i,1,n) {
            if (!id.count(a - x[i])) notA[i] = true;
            else merge(i, id[a-x[i]]);

            if (!id.count(b - x[i])) notB[i] = true;
            else merge(i, id[b - x[i]]);
        }

        FOR(i,1,n) {
            notA[getRoot(i)] |= notA[i];
            notB[getRoot(i)] |= notB[i];
        }

        bool ok = true;
        FOR(i,1,n) {
            notA[i] = notA[getRoot(i)];
            notB[i] = notB[getRoot(i)];

            if (notA[i] && notB[i]) ok = false;
        }

        if (!ok) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            FOR(i,1,n) {
                if (notA[i]) cout << 1;
                else cout << 0;
                cout << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}
