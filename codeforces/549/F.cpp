
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 300111;

map<int,int> cnt[MN];
int a[MN], s[MN];
int n, MOD;
int nSet;
ll res;

pair<int,int> it[MN * 4];

void build(int i, int l, int r) {
    if (l == r) {
        it[i] = make_pair(a[l], l);
        return ;
    }
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    it[i] = max(it[i<<1], it[i<<1|1]);
}

pair<int,int> get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return make_pair(-1, 1);
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return max(get(i<<1, l, mid, u, v), get(i<<1|1, mid+1, r, u, v));
}

int go(int i, int j) {
    if (i > j) {
        return 0;
    }
    if (i == j) {
        ++nSet;
        cnt[nSet][ s[i] ] = 1;
        return nSet;
    }

    auto ln = get(1, 1, n, i, j);

    int k = ln.second;

    
    int leftSet = go(i, k-1);
    int rightSet = go(k+1, j);

//    cout << "go(" << i << ", " << j << ") --> " << k << endl;
//    cout << "left = "; for(auto p : cnt[leftSet]) cout << p.first << ' ' << p.second << "    "; cout << endl;
//    cout << "righ = "; for(auto p : cnt[rightSet]) cout << p.first << ' ' << p.second << "    "; cout << endl;

    int left = k - i;
    int right = j - k;

    if (left <= right) {
        FOR(from,i,k) {
            int need = (a[k] + s[from-1]) % MOD;

            if (cnt[rightSet].count(need)) res += cnt[rightSet][need];
            if (from < k && s[k] == need) ++res;
        }
        FOR(from,i,k) {
            cnt[rightSet][s[from]] += 1;
        }
        return rightSet;
    }
    else {
        FOR(to,k,j) {
            int need = (s[to] - a[k]%MOD + MOD) % MOD;

            if (cnt[leftSet].count(need)) res += cnt[leftSet][need];
            if (s[i-1] == need) ++res;
            if (to == k && s[k-1] == need) --res;
        }

        FOR(to,k,j) {
            cnt[leftSet][s[to]] += 1;
        }
        return leftSet;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &MOD) == 2) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            s[i] = (s[i-1] + a[i]) % MOD;
        }
        build(1, 1, n);
        res = 0;
        nSet = 0;
        go(1,n);
        cout << res << endl;

        FOR(i,1,nSet) cnt[i].clear();
    }
}

