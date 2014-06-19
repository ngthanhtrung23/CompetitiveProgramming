#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 500111;
#define left left_
#define right right_
int a[MN], res[MN], cur, left[MN], right[MN], st[MN], n;

int it[MN*3];

int better(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    if (a[x] > a[y]) return x;
    else return y;
}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)
void buildTree(int i, int l, int r) {
    if (l == r) {
        it[i] = l;
        return ;
    }
    int mid = (l + r) >> 1;
    buildTree(CT(i), l, mid);
    buildTree(CP(i), mid+1, r);

    it[i] = better(it[CT(i)], it[CP(i)]);
}

int getMin(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i];

    int res = u;
    int mid = (l + r) >> 1;
    res = better(getMin(CT(i), l, mid, u, v), res);
    res = better(getMin(CP(i), mid+1,r, u, v), res);
    return res;
}

void init() {
    int top = 0; st[0] = 0;
    FOR(i,1,n) {
        while (top && a[st[top]] < a[i]) --top;
        left[i] = st[top];
        st[++top] = i;
    }
    top = 0; st[0] = n+1;
    FORD(i,n,1) {
        while (top && a[st[top]] < a[i]) --top;
        right[i] = st[top];
        st[++top] = i;
    }
    // PR(left, n);
    // PR(right, n);
}

void solve(int l, int r) {
    if (l+1 >= r) return ;
    if (a[l] <= a[r]) {
        int u = right[l];
        if (u == r) {
            u = getMin(1, 1, n, l+1, r-1);
        }
        res[cur--] = u;

        solve(l, u);
        solve(u, r);
    }
    else {
        int u = left[r];
        if (u == l) {
            u = getMin(1, 1, n, l+1, r-1);
        }
        res[cur--] = u;
        solve(l, u);
        solve(u, r);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        init();
        buildTree(1, 1, n);
        cur = n-2;
        solve(1, n);
        // PR(res, n-2);

        set<int> s;
        FOR(i,1,n) s.insert(i);

        long long sum = 0;
        FOR(turn,1,n-2) {
            int u = res[turn];
            s.erase(u);
            __typeof(s.begin()) next = s.lower_bound(u), prev = next;
            --prev;

            sum += min(a[*next], a[*prev]);
        }
        cout << sum << endl;
    }
    return 0;
}
