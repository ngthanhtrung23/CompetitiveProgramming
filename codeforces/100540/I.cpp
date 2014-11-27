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

string brail[10][3] = {
    {".*", "**", ".."}, //0
    {"*.", "..", ".."}, //1
    {"*.", "*.", ".."}, //2
    {"**", "..", ".."}, //3
    {"**", ".*", ".."}, //4
    {"*.", ".*", ".."}, //5
    {"**", "*.", ".."}, //6
    {"**", "**", ".."}, //7
    {"*.", "**", ".."}, //8
    {".*", "*.", ".."}, //9
};

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n && n) {
        char typ; cin >> typ;
//        DEBUG(n);
//        DEBUG(typ);
        if (typ == 'S') {
            string a[3];
            REP(t,3) a[t] = "";

            string dig; cin >> dig;
            REP(i,dig.size()) {
                int u = dig[i] - '0';
                REP(t,3) {
                    if (i) a[t] += ' ';
                    a[t] += brail[u][t];
                }
            }
            REP(t,3) cout << a[t] << endl;
        }
        else {
            string a[3];
            REP(t,3) {
                a[t] = "";
                REP(i,2*n) {
                    char c; cin >> c;
                    a[t] += c;
                }
            }
//            PR0(a, 3);
            REP(turn,n) {
                int start = 2 * turn;
                REP(dig,10) {
                    if (brail[dig][0] == a[0].substr(start,2)
                            && brail[dig][1] == a[1].substr(start, 2)
                            && brail[dig][2] == a[2].substr(start, 2)) {
                        cout << dig;
                        break;
                    }
                }
            }
            cout << endl;
        }
    }
    return 0;
}
