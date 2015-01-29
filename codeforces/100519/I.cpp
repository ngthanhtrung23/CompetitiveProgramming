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

const int MN = 300111;
int sieve[MN];

string get(int x, int p) {
    string res = "";
    REP(turn,41) {
        int xx = x * 2 % p;
        if (xx < x) res += 'A';
        else res += 'B';

        x = xx;
    }
    return res;
}

int main() {
    FOR(i,2,1000) if (!sieve[i]) {
        int j = i*i;
        while (j < MN) {
            sieve[j] = i;
            j += i;
        }
    }
    int n; cin >> n;
    string all = "";
    FOR(i,1,41) {
        cout << 2 << endl;
        string c; cin >> c;
        if (c == "OK") {
            return 0;
        }
        if (c[0] == '<') all += 'A';
        else all += 'B';
    }

    FOR(p,3,n) if (!sieve[p]) {
        int l = 1, r = p-1;

        while (l <= r) {
            int mid = (l + r) >> 1;
            string cur = get(mid, p);

            if (cur == all) {
                cout << p << endl;
                return 0;
            }

            if (cur < all) r = mid - 1;
            else l = mid + 1;
        }
    }
    assert(false);
    return 0;
}
