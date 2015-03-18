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

long long power[40111][44];
int a, b, n;
int f[40111][44];

int main() {
    while (cin >> a >> b >> n) {
        FOR(i,2,40000) {
            power[i][0] = 1;
            FOR(j,1,40) {
                power[i][j] = power[i][j-1] * i;
                if (power[i][j] > n) {
                    power[i][j] = n+1;
                }
            }
        }

        FORD(i,40000,1) FORD(j,40,1) {
            if (i == 1) {
                if (j == 40) {
                    if (f[2][j] == -1) f[i][j] = 1;
                    else f[i][j] = 0;
                }
                else {
                    if (f[i+1][j] == -1 || f[i][j+1] == -1) f[i][j] = 1;
                    else if (f[i+1][j] == 0 || f[i][j+1] == 0) f[i][j] = 0;
                    else f[i][j] = -1;
                }
            }
            else {
                if (power[i][j] >= n) f[i][j] = 1;
                else if (j == 1 && i == 40000) {
                    if (f[i][j+1] < 0) f[i][j] = 1;
                    else if ((n - i) % 2 == 0) f[i][j] = 1;
                    else if (f[i][j+1] == 0) f[i][j] = 0;
                    else f[i][j] = -1;
                }
                else {
                    if (f[i+1][j] == -1 || f[i][j+1] == -1) f[i][j] = 1;
                    else if (f[i+1][j] == 0 || f[i][j+1] == 0) f[i][j] = 0;
                    else f[i][j] = -1;
                }
            }
        }
        if (f[a][b] > 0) cout << "Masha";
        else if (f[a][b] < 0) cout << "Stas";
        else cout << "Missing";
        cout << endl;
    }
    return 0;
}
