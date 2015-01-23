#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

long long get(int cur_level, int max_level, long long n, long long from, long long to, int pref) {
    if (cur_level == max_level) return 0;
    
    long long mid = (from + to) / 2;
    if (pref == 0) {
        if (n > mid) return (1LL << (max_level - cur_level)) + get(cur_level + 1, max_level, n, mid+1, to, 0);
        else return get(cur_level + 1, max_level, n, from, mid, 1) + 1;
    }
    else {
        if (n <= mid) return (1LL << (max_level - cur_level)) + get(cur_level + 1, max_level, n, from, mid, 1);
        else return get(cur_level + 1, max_level, n, mid+1, to, 0) + 1;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    long long h, n;
    while (cin >> h >> n) {
        cout << get(0, h, n, 1, 1LL << h, 0) << endl;
    }
    return 0;
}
