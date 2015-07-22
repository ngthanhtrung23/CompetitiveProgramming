
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

string a, b;

string go(const string& a, int l, int r) {
    int len = r - l + 1;
    if (len % 2 == 0) {
        int mid = (l + r) / 2;
        string x = go(a, l, mid), y = go(a, mid+1, r);
        if (x <= y) return x + y;
        else return y + x;
    }
    else return a.substr(l, r - l + 1);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a >> b) {
        int n = a.length();
        string aa = go(a, 0, n-1);
        string bb = go(b, 0, n-1);

        cout << (aa == bb ? "YES" : "NO") << endl;
    }
}

