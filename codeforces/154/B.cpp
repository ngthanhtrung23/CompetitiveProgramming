
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

const int MN = 100111;
int sieve[MN], has[MN], state[MN];
int n, q;

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        for(int j = i*i; j < MN; j += i)
            sieve[j] = i;
    }
}

void flip(int u) {
    int saveu = u;
    while (u > 1) {
        int p = (sieve[u]) ? sieve[u] : u;
        has[p] ^= saveu;
        while (u % p == 0) u /= p;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    init();
    while (cin >> n >> q) {
        memset(has, 0, sizeof has);
        memset(state, 0, sizeof state);

        while (q--) {
            char typ; cin >> typ;
            if (typ == '+') {
                int u; cin >> u;
                if (state[u] == 1) {
                    cout << "Already on\n";
                    continue;
                }
                int saveu = u;
                int bad = 0;
                while (u > 1) {
                    int p = (sieve[u]) ? sieve[u] : u;

                    if (has[p]) {
                        bad = has[p];
                        break;
                    }
                    while (u % p == 0) u /= p;
                }
                if (!bad) {
                    cout << "Success\n";
                    flip(saveu);
                    state[saveu] = 1;
                }
                else {
                    cout << "Conflict with " << bad << '\n';
                }
            }
            else {
                int u; cin >> u;
                if (state[u] == 0) {
                    cout << "Already off\n";
                    continue;
                }
                flip(u);
                state[u] = 0;
                cout << "Success\n";
            }
        }
    }
    return 0;
}

