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
using namespace std;

const ll BASE1 = 1e9 + 7;
const ll BASE2 = 1e9 + 33;

struct Hash {
    ll x, y;
    Hash() { x = y = 0; }
    Hash(ll x, ll y) : x(x), y(y) {}
};

bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}

struct Set {
    set<Hash> s;

    Set() {}

    Hash getHash() {
        Hash res(1, 1);
        for(auto a : s) {
            res.x = res.x * BASE1 + a.x;
            res.y = res.y * BASE2 + a.y;
        }
        return res;
    }
};

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        stack< Set > st;
        FOR(turn,1,n) {
            string op; cin >> op;
            if (op == "PUSH") {
                st.push(Set());
            }
            else if (op == "DUP") {
                st.push(st.top());
            }
            else if (op == "UNION") {
                Set a = st.top(); st.pop();
                Set b = st.top(); st.pop();
                Set c;
                set_union(a.s.begin(), a.s.end(), b.s.begin(), b.s.end(),
                        std::inserter(c.s, c.s.begin()));
                st.push(c);
            }
            else if (op == "INTERSECT") {
                Set a = st.top(); st.pop();
                Set b = st.top(); st.pop();
                Set c;
                set_intersection(a.s.begin(), a.s.end(), b.s.begin(), b.s.end(),
                        std::inserter(c.s, c.s.begin()));
                st.push(c);
            }
            else { // op == "ADD"
                Set a = st.top(); st.pop();
                Set b = st.top(); st.pop();
                b.s.insert(a.getHash());
                st.push(b);
            }
            printf("%d\n", st.top().s.size());
        }
        puts("***");
    }
}