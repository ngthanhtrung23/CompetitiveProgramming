#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct Permutation {
    vector<int> x;

    Permutation(int n = 0) {
        x.resize(n);
    }

    void print() {
        REP(i,x.size()) cout << x[i] << ' ';
        cout << endl;
    }
};

Permutation identity(int n) {
    Permutation res(n);
    REP(i,n) res.x[i] = i;
    return res;
}

Permutation rotate(int n) {
    Permutation res(n);
    REP(i,n) res.x[i] = (i+1) % n;
    return res;
}

Permutation sort(int n, int k, int d) {
    Permutation res;
    REP(start,d) {
        for(int i = start; i < k; i += d) {
            res.x.push_back(i);
        }
    }
    for(int i = k; i < n; ++i) {
        res.x.push_back(i);
    }
    return res;
}

Permutation operator * (const Permutation &a, const Permutation &b) {
    Permutation res(a.x.size());
    REP(i,res.x.size())
        res.x[i] = a.x[b.x[i]];
    return res;
}

Permutation power(Permutation C, int k) {
    Permutation res = identity(C.x.size());
    while (k > 0) {
        if (k & 1) res = res * C;
        C = C * C;
        k >>= 1;
    }
    return res;
}

string s;
int q;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s >> q) {
        int n = s.length();
        while (q--) {
            int k, d; cin >> k >> d;
            if (n == 1) {
                cout << s << "\n";
                continue;
            }
            Permutation S = sort(n, k, d);
            Permutation R = rotate(n);

            Permutation C = S * R;
            // C.print();

            C = power(C, n - k + 1);
            // C.print();

            string t = "";
            for(int i = k - 1, turn = 0; turn < n; ++turn, i = (i+1) % n) {
                t += s[C.x[i]];
            }
            cout << t << "\n";
            s = t;
        }
    }
    return 0;
}
