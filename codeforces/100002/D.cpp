
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int toNum(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}
int toNum(char c, char d) {
    return toNum(c) * 16 + toNum(d);
}

char toChar(int u) {
    assert(u < 16);
    if (u < 10) return (char) ('0' + u);
    return (char) ('A' + u - 10);
}

void print(int u) {
    assert(u < 256);
    cout << toChar(u / 16) << toChar(u % 16);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("decode.in", "r", stdin);
    freopen("decode.out", "w", stdout);
    string a, b;
    while (cin >> a >> b) {
        int key = toNum(b[0], b[1]) ^ 32;

        for(int i = 0; i < SZ(a); i += 2) {
            int u = toNum(a[i], a[i+1]);
            int text = key ^ u;
            print(key);

            int v = toNum(b[i+2], b[i+3]);
            key = v ^ text;
        }
        print(key);
        cout << endl;
    }
}
