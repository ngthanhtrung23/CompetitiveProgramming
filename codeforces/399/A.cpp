#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

string toStr(int i) {
    stringstream ss; ss << i;
    return ss.str();
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, p, k;
    while (cin >> n >> p >> k) {
        string s = "(" + toStr(p) + ")";
        FORD(i,p-1,max(1,p-k)) s = toStr(i) + " " + s;
        if (p-k > 1) s = "<< " + s;

        FOR(i,p+1,min(n,p+k)) s = s + " " + toStr(i);
        if (p+k < n) s = s + " >>";

        cout << s << endl;
    }
    return 0;
}
