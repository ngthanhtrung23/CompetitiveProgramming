
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

#define SECOND "Daenerys"
#define FIRST "Stannis"
int n, k;
int odd, even;

string solve() {
    if (n == k) {
        if (odd % 2) return FIRST;
        return SECOND;
    }

    int second = (n - k) / 2;
    int first = n - k - second;

    if (first > second) {
        if (k % 2) {
            if (second < odd) return FIRST;
            return SECOND;
        }
        else {
            if (second < odd && second < even) return FIRST;
            return SECOND;
        }
    } else {
        if (k % 2) {
            if (first >= even) return FIRST;
            return SECOND;
        }
        return SECOND;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        odd = 0, even = 0;
        FOR(i,1,n) {
            int a; cin >> a;
            if (a % 2) ++odd;
            else ++even;
        }

        cout << solve() << endl;
    }
}
