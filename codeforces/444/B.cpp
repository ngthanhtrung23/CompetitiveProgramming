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

const int MN = 100111;
long long x;
int n, d, a[MN], b[MN];

long long getNextX() {
    x = (x * 37 + 10007) % 1000000007;
    return x;
}

void initAB() {
    for(int i = 0; i < n; i = i + 1){
        a[i] = i + 1;
    }
    for(int i = 0; i < n; i = i + 1){
        swap(a[i], a[getNextX() % (i + 1)]);
    }
    for(int i = 0; i < n; i = i + 1){
        if (i < d)
            b[i] = 1;
        else
            b[i] = 0;
    }
    for(int i = 0; i < n; i = i + 1){
        swap(b[i], b[getNextX() % (i + 1)]);
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> d >> x) {
        initAB();
        // PR0(a, n);
        // PR0(b, n);

        set<pair<int,int> >s;
        vector<int> pos1;
        REP(i,n) {
            s.insert(make_pair(-a[i], i));
            if (b[i] == 1) pos1.push_back(i);

            int res = 0;
            if (pos1.size() < 1000) {
                REP(x,pos1.size()) {
                    res = max(res, a[i-pos1[x]]);
                }
            }
            else {
                vector< pair<int,int> > tmp;
                while (!s.empty()) {
                    pair<int,int> cur = *s.begin();
                    tmp.push_back(cur);
                    s.erase(s.begin());
                    if (b[i-cur.second] == 1) {
                        res = -cur.first;
                        break;
                    }
                }
                REP(i,tmp.size()) s.insert(tmp[i]);
            }

            cout << res << "\n";
        }
    }
    return 0;
}

