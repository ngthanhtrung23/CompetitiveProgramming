// template {{{
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& out, const Con& con) {
    out << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        out << (it == beg ? "" : ", ") << *it;
    }
    return out << '}';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {
    return uniform_int_distribution<long long> (l, r)(rng);
}

template<typename T>
vector<T> read_vector(int n) {
    vector<T> res(n);
    for (int& x : res) cin >> x;
    return res;
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) solve();
    return 0;
}

// }}}

void solve() {
    int nRow, nCol; cin >> nRow >> nCol;
    int a, b; cin >> a >> b;

#define CHECK(s1, s2, r1, c1, r2, c2) if (a == s1 && b == s2) { cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl; return; }
#define GO(s1, s2, r1, c1, r2, c2) { CHECK(s1, s2, r1, c1, r2, c2); CHECK(s2, s1, r2, c2, r1, c1); }

    // aaaABbb
    // aaaabbb
    FOR(i,1,nCol-1) {
        int s1 = nRow * i;
        int s2 = nRow * (nCol - i);
        GO(s1, s2, 1, i, 1, i+1);
    }
    // aaaA.Bbbbb
    // aaaa.bbbbb
    FOR(i,1,nCol-2) {
        int s1 = nRow * i;
        int s2 = nRow * nCol - s1 - nRow;
        GO(s1, s2, 1, i, 1, i+2);
    }

    // aa
    // aa
    // Aa
    // Bb
    // bb
    // bb
    // bb
    FOR(i,1,nRow-1) {
        int s1 = nCol * i;
        int s2 = nCol * (nRow - i);
        GO(s1, s2, i, 1, i+1, 1);
    }
    FOR(i,1,nRow-2) {
        int s1 = nCol * i;
        int s2 = nCol * (nRow - i - 1);
        GO(s1, s2, i, 1, i+2, 1);
    }

    // aaaa.....
    // aaaA.....
    // ....Bbbbb
    // ....bbbbb
    auto sum_range = [&] (int l, int r) {  // returns l + (l+1) + ... + r
        if (l > r) return 0LL;
        return (r + l) * (r - l + 1) / 2;
    };
    for (int d = 1; d <= min(nRow, nCol) - 1; d += 2) {
        FOR(i,1,nRow-d) FOR(j,1,nCol-d) {
            int s1 = (i+d/2) * (j+d/2) + sum_range(i, i+d/2 - 1) + sum_range(j, j+d/2 - 1);
            int u = nRow - (i+d) + 1;
            int v = nCol - (j+d) + 1;
            int s2 = (u+d/2) * (v+d/2) + sum_range(u, u+d/2 - 1) + sum_range(v, v+d/2 - 1);
            GO(s1, s2, i, j, i+d, j+d);
        }
    }

    // aaaaabbbb
    // aaaAabbbb
    // aaaabBbbb
    // aaaabbbbb
    FOR(i,1,nRow-1) FOR(j,1,nCol-2) {
        int s1 = nRow * j + i;
        int s2 = nRow * nCol - s1;
        GO(s1, s2, i, j, i+1, j+2);
    }
    // aaaaa.bbb
    // aaaAa.bbb
    // aaaa.bBbb
    // aaaa.bbbb
    FOR(i,1,nRow-1) FOR(j,1,nCol-3) {
        int s1 = nRow * j + i;
        int s2 = nRow * nCol - s1 - nRow;
        GO(s1, s2, i, j, i+1, j+3);
    }

    // aaaaaaaaa
    // aaaAaaaaa
    // aaaabbbbb
    // bbbbBbbbb
    // bbbbbbbbb
    FOR(i,1,nRow-2) FOR(j,1,nCol-1) {
        int s1 = nCol * i + j;
        int s2 = nRow * nCol - s1;
        GO(s1, s2, i, j, i+2, j+1);
    }
    // aaaaaaaaa
    // aaaAaaaaa
    // aaaa.....
    // ....bbbbb
    // bbbbBbbbb
    // bbbbbbbbb
    FOR(i,1,nRow-3) FOR(j,1,nCol-1) {
        int s1 = nCol * i + j;
        int s2 = nRow * nCol - s1 - nCol;
        GO(s1, s2, i, j, i+3, j+1);
    }

    // aaaaa....
    // aaaAa....
    // aaaa.bbbb
    // ....bBbbb
    // ....bbbbb
    for (int d = 2; d <= min(nRow, nCol); d += 2) {
        FOR(i,1,nRow-d) FOR(j,1,nCol-d) {
            int s1 = (i+d/2) * (j+d/2) - 1 + sum_range(i, i+d/2-2) + sum_range(j, j+d/2-2);

            int u = nRow - (i+d) + 1;
            int v = nCol - (j+d) + 1;
            int s2 = (u+d/2) * (v+d/2) - 1 + sum_range(u, u+d/2-2) + sum_range(v, v+d/2-2);
            GO(s1, s2, i, j, i+d, j+d);
        }
    }
    
    FOR(i,1,nRow-4) FOR(j,1,nCol-4) {
        int s1 = (i+2) * (j+2) - 1 + i + j;
        int s2 = (nRow-i-1) * (nCol-j-1) - 1 + (nRow-i-3) + (nCol-j-3);
        GO(s1, s2, i, j, i+4, j+4);
    }

    // aaaaaabbb
    // aaaAaabbb
    // aaaaabbbb
    // aaaabbBbb
    // aaaabbbbb
    FOR(i,1,nRow-2) FOR(j,1,nCol-3) {
        int s1 = nRow * j + (i+1) + i;
        int s2 = nRow * nCol - s1;
        GO(s1, s2, i, j, i+2, j+3);
    }

    cout << "-1 -1 -1 -1\n";
}
