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

const int MN = 100111;
struct People {
    int resp, age, id;
} a[MN];
bool operator < (const People& a, const People& b) {
    return a.resp < b.resp;
}
int newId[MN], n, q, k, cage[MN], nage, can[MN], res[MN];
pair<int,int> queries[MN];
vector< pair<int,int> > ask[MN];

void RR() {
    FOR(i,1,n) cage[i] = a[i].age;
    sort(cage+1, cage+n+1);
    nage = unique(cage+1, cage+n+1) - cage - 1;

    FOR(i,1,n) a[i].age = lower_bound(cage+1, cage+nage+1, a[i].age) - cage;
}

int it_cnt[MN * 8], it_max[MN * 8];
#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void update_cnt(int i, int l, int r, int u) {
    if (u < cage[l] || cage[r] < u) return ;
    if (l == r) {
        it_cnt[i] += 1;
        return ;
    }
    int mid = (l + r) >> 1;
    update_cnt(CT(i), l, mid, u);
    update_cnt(CP(i), mid+1, r, u);
    it_cnt[i] = it_cnt[CT(i)] + it_cnt[CP(i)];
}

void update_max(int i, int l, int r, int u, int val) {
    if (u < cage[l] || cage[r] < u) return ;
    if (l == r) {
        it_max[i] = max(it_max[i], val);
        return ;
    }
    int mid = (l + r) >> 1;
    update_max(CT(i), l, mid, u, val);
    update_max(CP(i), mid+1, r, u, val);
    it_max[i] = max(it_max[CT(i)], it_max[CP(i)]);
}

int get_cnt(int i, int l, int r, int u, int v) {
    if (v < cage[l] || cage[r] < u) return 0;
    if (u <= cage[l] && cage[r] <= v) return it_cnt[i];
    int mid = (l + r) >> 1;
    return get_cnt(CT(i), l, mid, u, v) + get_cnt(CP(i), mid+1, r, u, v);
}

int get_max(int i, int l, int r, int u, int v) {
    if (v < cage[l] || cage[r] < u) return 0;
    if (u <= cage[l] && cage[r] <= v) return it_max[i];
    int mid = (l + r) >> 1;
    return max(get_max(CT(i), l, mid, u, v), get_max(CP(i), mid+1, r, u, v));
}

void init() {
//    PR(cage, nage);
    memset(it_cnt, 0, sizeof it_cnt);
    memset(it_max, 0, sizeof it_max);
    int j = 0;
    FOR(i,1,n) {
        while (j < n && a[j+1].resp <= a[i].resp) {
            ++j;
            update_cnt(1, 1, nage, cage[a[j].age]);
        }
        can[i] = get_cnt(1, 1, nage, cage[a[i].age] - k, cage[a[i].age] + k);
    }
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) scanf("%d", &a[i].resp);
        FOR(i,1,n) scanf("%d", &a[i].age);
        FOR(i,1,n) a[i].id = i;
        sort(a+1, a+n+1);
        RR();
        FOR(i,1,n) newId[a[i].id] = i;
//        FOR(i,1,n) cout << a[i].resp << ' ' << a[i].age << ' ' << a[i].id << endl;
        init();

        scanf("%d", &q);
        FOR(i,1,n) ask[i].clear();
        FOR(i,1,q) {
            int u, v; scanf("%d%d", &u, &v);
            u = newId[u]; v = newId[v];
            if (u > v) swap(u, v);
            ask[v].push_back(make_pair(u, i));
        }
        memset(it_max, 0, sizeof it_max);

        int j = n+1;
        FORD(i,n,1) {
            while (j > 1 && a[j-1].resp >= a[i].resp) {
                --j;
                update_max(1, 1, nage, cage[a[j].age], can[j]);
            }
            for(auto x : ask[i]) {
                // leader_age - k <= min(a[i].age, a[x.first].age)
                // leader_age + k >= max(a[i].age, a[x.first].age)
                int from = cage[max(a[i].age, a[x.first].age)] - k;
                int to   = cage[min(a[i].age, a[x.first].age)] + k;
                res[x.second] = get_max(1, 1, nage, from, to);
                if (res[x.second] == 0) res[x.second] = -1;
            }
        }

        FOR(i,1,q) printf("%d\n", res[i]);
    }
    return 0;
}

