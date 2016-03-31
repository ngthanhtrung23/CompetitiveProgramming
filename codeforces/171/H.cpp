//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

pair<int,int> get(int a, int b) {
    if (a == 0) return MP(-1,-1);
    if (a == 1) {
        switch (b) {
            case 0: return MP(0,0);
            case 1: return MP(1,0);
            case 2: return MP(1,1);
            case 3: return MP(0,1);
        }
    }
    int len = (1<<(2*(a-1)));
    
    if (b < len) return get(a-1, b);
    else if (b < 2*len) {
        pair<int,int> cur = get(a-1,b-len);
        if (a % 2 == 1) return MP(cur.S + (1<<(a-1)), cur.F);
        else return MP(cur.S, cur.F + (1<<(a-1)));
    }
    else if (b < 3*len) {
        int need = b - len - len;
        need = len - need - 1;
        need += len;
        pair<int,int> cur = get(a, need);
        if (a % 2 == 1) return MP(cur.F, (1<<a) - 1 - cur.S);
        else return MP((1<<a) - 1 - cur.F, cur.S);
    }
    else {
        int need = b - len*3;
        need = len - need - 1;
        pair<int,int> cur = get(a, need);
        if (a % 2 == 0) return MP((1<<a) - 1 - cur.F, cur.S);
        else return MP(cur.F, (1<<a) - 1 - cur.S);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int a, b;
    while (cin >> a >> b) {
        pair<int,int> res =  get(a,b);
        if (a % 2 == 1) swap(res.F, res.S);
        cout << res.F << ' ' << res.S << endl;
    }
    return 0;
}