
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
const ll base = 1000000000ll * 1000000000;
const int base_digits = 18;

struct BigInt {
    vector<ll> a;

    BigInt() {
    }

    BigInt(long long v) {
        *this = v;
    }

    void operator=(const BigInt &v) {
        a = v.a;
    }

    void operator=(long long v) {
        for (; v > 0; v = v / base)
            a.push_back(v % base);
    }


    BigInt operator+(const BigInt &v) const {
        BigInt res = v;

        for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int) res.a.size())
                res.a.push_back(0);
            res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
            carry = res.a[i] >= base;
            if (carry)
                res.a[i] -= base;
        }
        return res;
    }

    void operator+=(const BigInt &v) {
        *this = *this + v;
    }
    bool operator<(const BigInt &v) const {
        if (a.size() != v.a.size())
            return a.size() < v.a.size();
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] < v.a[i];
        return false;
    }

    bool operator>(const BigInt &v) const {
        return v < *this;
    }

    friend ostream& operator<<(ostream &stream, const BigInt &v) {
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }
};

const int MN = 1011;

int sigma, start, K, len;
bool target[MN];

int to[MN][33], x[MN][33];
int qu[MN], visited[MN];

vector<int> ke[MN][33];

void init() {
}

BigInt f[66][MN];
BigInt solve() {
    f[0][start] = 1;
    FOR(i,0,len-1) FOR(cur,1,K) if (f[i][cur] > 0) {
        FOR(c,1,sigma) {
            for(int next : ke[cur][c]) {
                f[i+1][next] += f[i][cur];
            }
        }
    }
    BigInt res = 0;
    FOR(t,1,K) if (target[t]) res += f[len][t];
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("dfa.in", "r", stdin);
    freopen("dfa.out", "w", stdout);
    int nTarget;
    string alpha;
    cin >> alpha >> K >> start >> nTarget;
    sigma = alpha.length();
    init();
    while (nTarget--) {
        int u; cin >> u;
        target[u] = true;
    }
    FOR(i,1,K) FOR(c,1,sigma) cin >> to[i][c];
    FOR(i,1,K) FOR(c,1,sigma) cin >> x[i][c];
    cin >> len;

    // build adjacency list
    FOR(i,1,K) FOR(c,1,sigma) {
        // first, BFS using x
        int first = 1, last = 1;
        memset(visited, 0, sizeof visited);
        visited[i] = true;
        qu[1] = i;

        while (first <= last) {
            int u = qu[first++];
            if (x[u][c] == 0) continue;

            int v = to[u][c];

            if (!visited[v]) {
                visited[v] = true;
                qu[++last] = v;
            }
        }

        // init ke[i][c]
        FOR(id,1,last) {
            int u = qu[id];
            if (x[u][c] == 0)
                ke[i][c].push_back(to[u][c]);
        }
//            cout << "i = " << i << ", c = " << c << endl;
//            PR0(ke[i][c], ke[i][c].size());
    }

    cout << solve() << endl;
}
