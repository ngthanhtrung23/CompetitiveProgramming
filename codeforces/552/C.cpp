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

vector<long long> all;
bool can;

void attempt(int id, long long need) {
    if (can) return ;
    if (need == 0) {
        can = true;
        return ;
    }
    if (id == all.size()) return ;

    int lb;
    if (id == 0) lb = 0; else lb = -1;
    int ub = 1;
    
    FOR(mult,lb,ub) {
        attempt(id+1, need-mult*all[id]);
    }
}

bool solve(long long w, long long m) {
    if (w <= 3) return true;
    if (m == 1) return true;

    all.clear();
    long long ln = 1;
    all.push_back(1);
    while (ln <= m) {
        ln *= w;
        all.push_back(ln);
    }
    reverse(all.begin(), all.end());

    can = false;
    attempt(0, m);
    return can;
}

int main() {
    ios :: sync_with_stdio(false);
    long long w, m;
    while (cin >> w >> m) {
        cout << (solve(w, m) ? "YES" : "NO") << endl;
    }
    return 0;
}

