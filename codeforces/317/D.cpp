#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
using namespace std;

const int g[] = {
0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12,14};
map<int,int> f;

int get(int mask, int n) {
    if (f.count(mask)) return f[mask];
    if (mask == 0) {
        return f[mask] = 0;
    }
    else {
        set<int> s;
        REP(i,n) if (CONTAIN(mask,i)) {
            int u = i+1;
            int newMask = mask;
            while (u <= n) {
                if (CONTAIN(newMask, u-1)) newMask -= TWO(u-1);
                u += i + 1;
            }

            s.insert(get(newMask, n));
        }
        int res = 0;
        while (s.count(res)) ++res;
        return f[mask] = res;
    }
}

void init() {
    FOR(n,1,30) {
        f.clear();
        cerr << n << ' ' << get(TWO(n)-1, n) << endl;
        cout << f[TWO(n)-1] << ',';
    }
}

int mark[1000111];

int main() {
//    init();
    int n;
    while (cin >> n) {
        memset(mark, 0, sizeof mark);
        int other = 1;
        long long gh = 1;
        while ((gh+1) * (gh+1) <= n) ++gh;
        other += n - gh;

        int sum = other % 2;
        FOR(i,2,gh) if (!mark[i]) {
            long long u = i;
            int cnt = 1;
            while (u*i <= n) {
                u *= i;
                if (u <= gh) mark[u] = 1;
                else sum ^= 1;
                ++cnt;
            }
            sum ^= g[cnt];
        }
        if (sum == 0) cout << "Petya"; else cout << "Vasya";
        cout << endl;
    }
    return 0;
}

