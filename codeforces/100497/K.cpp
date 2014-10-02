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

const int MN = 1000111;
map<string,int> id;
vector<int> ke[MN];
int vao[MN], nId = 0;
char tmp[MN];
int first, last, qu[MN];

int getId(const string &s) {
    if (!id.count(s)) id[s] = ++nId;
    return id[s];
}

void addEdge(int u, int v) {
    // cout << u << ' ' << v << endl;
    ke[u].push_back(v);
    ++vao[v];
}

bool canInstall[MN];

int main() {
    ios :: sync_with_stdio(false);
    id.clear();
    while (gets(tmp)) {
        istringstream ss(tmp);

        string s; ss >> s;
        int u = getId(s);
        canInstall[u] = true;

        while (ss >> s) {
            if (s == "0") break;
            int v = getId(s);

            addEdge(v, u);
        }
    }

    first = 1; last = 0;
    FOR(i,1,nId) if (!vao[i] && canInstall[i]) qu[++last] = i;

    while (first <= last) {
        int u = qu[first++];
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            vao[v]--;

            if (!vao[v] && canInstall[v]) qu[++last] = v;
        }
    }
    int res = 0;
    FOR(i,1,last) if (canInstall[qu[i]]) ++res;

    cout << last << endl;
    // PR(qu, last);
    return 0;
}
