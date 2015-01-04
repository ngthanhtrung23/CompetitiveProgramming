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

const int MN = 600111;
const long long oo = 1000111000111000111LL;

struct Node {
    int cnt;
    long long sum;
} it[4 * MN];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

int n, w, c[MN], s;
pair<pair<int,int>,int> a[MN];

void insert(int i, int l, int r, int u, bool rem = false) {
    if (u < c[l] || c[r] < u) return ;

    if (rem) {
        it[i].cnt--;
        it[i].sum -= u;
    }
    else {
        it[i].cnt++;
        it[i].sum += u;
    }
    if (l == r) return ;

    int mid = (l + r) >> 1;
    insert(CT(i), l, mid, u, rem);
    insert(CP(i), mid+1, r, u, rem);
}

long long get(int i, int l, int r, int k) {
    if (k <= 0) return 0;
    if (k == it[i].cnt) return it[i].sum;
    if (l == r) {
        return c[l] * k;
    }
    
    int mid = (l + r) >> 1;
    if (it[CT(i)].cnt >= k) return get(CT(i), l, mid, k);
    else return it[CT(i)].sum + get(CP(i), mid+1, r, k - it[CT(i)].cnt);
}


int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> w) {
        FOR(i,1,n) {
            cin >> a[i].first.second >> a[i].first.first;
            a[i].second = i - 1;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) swap(a[i].first.first, a[i].first.second);

        s = 0;
        FOR(i,1,n) {
            c[++s] = a[i].first.first;
            c[++s] = a[i].first.second - a[i].first.first;
        }
        sort(c+1, c+s+1);
        s = unique(c+1, c+s+1) - c - 1;

//        PR(c, s);

        memset(it, 0, sizeof it);
        FOR(i,1,n) insert(1, 1, s, a[i].first.first);

        long long prefix = 0, res = oo;
        int savex = -1;
        FOR(x,0,n) {
            if (x > 0) {
                insert(1, 1, s, a[x].first.first, true);
                insert(1, 1, s, a[x].first.second - a[x].first.first);
                prefix += a[x].first.first;
            }
            if (it[1].cnt >= w - x) {
                long long cur = prefix + get(1, 1, s, w - x);
                if (cur < res) {
                    res = cur;
                    savex = x;
                }
            }
        }
        cout << res << endl;
        string trace = "";
        FOR(i,1,n) trace += '0';

        FOR(i,1,savex) trace[a[i].second] = '1';
        set< pair<int,int> > all;
        FOR(i,1,savex) all.insert(make_pair(a[i].first.second - a[i].first.first, a[i].second));
        FOR(i,savex+1,n) all.insert(make_pair(a[i].first.first, a[i].second));
        w -= savex;
        while (w--) {
            auto cur = *all.begin();
            trace[cur.second]++;
            all.erase(all.begin());
        }
        cout << trace << endl;
    }
    return 0;
}

