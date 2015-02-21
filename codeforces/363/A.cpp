
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

string get(int u) {
    string res = "";
    if (u < 5) res += "O-";
    else {
        res += "-O";
        u -= 5;
    }
    switch (u) {
        case 0: return res + "|-OOOO";
        case 1: return res + "|O-OOO";
        case 2: return res + "|OO-OO";
        case 3: return res + "|OOO-O";
        case 4: return res + "|OOOO-";
    }
}

int main() {
    string n;
    while (cin >> n) {
        reverse(n.begin(), n.end());
        for(char c : n)
            cout << get(c - '0') << endl;
    }
    return 0;
}
