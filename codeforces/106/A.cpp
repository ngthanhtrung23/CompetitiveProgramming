
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

int value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'T') return 10;
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    if (c == 'A') return 14;
    assert(false);
}

bool win(string a, string b, char good) {
    if (a[1] == good && b[1] == good) return value(a[0]) > value(b[0]);

    if (a[1] == good) return true;
    if (b[1] == good) return false;

    if (a[1] == b[1]) return value(a[0]) > value(b[0]);
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    char good;
    while (cin >> good) {
        string a, b;
        cin >> a >> b;
        cout << (win(a, b, good) ? "YES" : "NO") << endl;
    }
}
