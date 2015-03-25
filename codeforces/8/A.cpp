#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define left __left
#define right __right
using namespace std;

const int MN = 100111;
bool left[MN], right[MN];

bool solve(string s, string a, string b) {
    memset(left, 0, sizeof left);
    memset(right, 0, sizeof right);
    FOR(i,0,s.length()-a.length()) {
        if (s.substr(i, a.length()) == a) {
            left[i+a.length()-1] = true;
        }
    }
    FOR(i,0,s.length()-b.length()) {
        if (s.substr(i, b.length()) == b) {
            right[i] = true;
        }
    }
    FOR(i,1,s.length()-1) left[i] = left[i] || left[i-1];
    FORD(i,s.length()-2,0) right[i] = right[i] || right[i+1];
    FOR(i,0,s.length()-2)
        if (left[i] && right[i+1]) return true;
    return false;
}

int main() {
    string s, a, b;
    while (cin >> s) {
        cin >> a >> b;
        bool forward = solve(s, a, b);
        reverse(s.begin(), s.end());
        bool backward = solve(s, a, b);

        if (forward && backward) cout << "both";
        else if (forward) cout << "forward";
        else if (backward) cout << "backward";
        else cout << "fantasy";
        cout << endl;
    }
    return 0;
}

