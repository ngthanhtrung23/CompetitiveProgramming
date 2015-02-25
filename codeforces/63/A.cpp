
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

pair<int,int> x[111];
string name[111];

int main() {
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            string tmp;
            cin >> name[i] >> tmp;

            int u;
            if (tmp == "rat") u = 0;
            else if (tmp == "woman" || tmp == "child") u = 1;
            else if (tmp == "man") u = 2;
            else u = 3;
            x[i] = make_pair(u, i);
        }
        sort(x+1, x+n+1);
        FOR(i,1,n) cout << name[x[i].second] << endl;
    }
    return 0;
}
