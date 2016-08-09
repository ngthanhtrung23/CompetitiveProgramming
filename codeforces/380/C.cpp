#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

struct Node {
    int optimal;
    int open;
    int close;

    Node() {}
    Node(int opt, int o, int c) { // Khởi tạo struct Node
        optimal = opt;
        open = o;
        close = c;
    }
};

const int MAXN = 1000111;
Node st[MAXN * 4];
string s;

Node operator + (const Node& left, const Node& right) {
    Node res;
    // min(số dấu "(" thừa ra ở cây con trái, và số dấu ")" thừa ra ở cây con phải)
    int tmp = min(left.open, right.close);

    // Để xây dựng kết quả tối ưu ở nút id, ta nối dãy ngoặc tối ưu ở 2 con, rồi thêm
    // min(số "(" thừa ra ở con trái, số ")" thừa ra ở con phải).
    res.optimal = left.optimal + right.optimal + tmp;

    res.open = left.open + right.open - tmp;
    res.close = left.close + right.close - tmp;

    return res;
}

void build(int id, int l, int r) {
    if (l == r) {
        // Đoạn [l, r] chỉ có 1 phần tử.
        if (s[l] == '(') st[id] = Node(0, 1, 0);
        else st[id] = Node(0, 0, 1);
        return ;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid+1, r);

    st[id] = st[id * 2] + st[id * 2 + 1];
}
Node query(int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
        // Trường hợp không giao nhau
        return Node(0, 0, 0);
    }
    if (u <= l && r <= v) {
        // Trường hợp [l, r] nằm hoàn toàn trong [u, v]
        return st[id];
    }

    int mid = (l + r) / 2;
    return query(id * 2, l, mid, u, v) + query(id * 2 + 1, mid+1, r, u, v);
}

char tmp[MAXN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    scanf("%s\n", &tmp[0]);
    int n = strlen(tmp);

    s = " " + string(tmp) + " ";
    build(1, 1, n);

    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        auto res = query(1, 1, n, l, r);
        printf("%d\n", res.optimal * 2);
    }
}
