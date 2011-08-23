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
using namespace std;

const double PI = acos(-1.0);

bool in[1011], out[1011];
int next[1011], nextD[1011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    FOR(i,1,m) {
        int a, b, d;
        cin >> a >> b >> d;
        out[a] = true;
        in[b] = true;
        next[a] = b;
        nextD[a] = d;
    }
    int cnt = 0;
    FOR(i,1,n) if (out[i] && !in[i]) cnt++;
    cout << cnt << endl;
    bool ok = false;
    FOR(i,1,n) if (out[i] && !in[i]) {
        ok = true;
        int now = i, cur = nextD[i];
        while (next[now]) {
            cur = min(cur, nextD[now]);
            now = next[now];
        }
        cout << i << ' ' << now << ' ' << cur << endl;
    }
    return 0;
}
