#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MAXV = 11000111;
bool isPrime[MAXV];

bool check(int p1, int p2, int p3) {
    return ((p1 + p2) * (p1 + p2) - 1) % p3 == 0;
}

int32_t main() {
    ios::sync_with_stdio(0);
    memset(isPrime, true, sizeof isPrime);
    isPrime[1] = false;

    vector<int> primes;
    for (int i = 2; i < MAXV; i++) {
        if (!isPrime[i]) continue;
        primes.push_back(i);

        for (int j = i*i; j < MAXV; j += i) {
            isPrime[j] = false;
        }
    }

    int k; cin >> k;

    int cnt = 0;
    for (int p1 : primes) {
        int p2 = p1;
        for (int p3 = 2*p1 - 1; p3 <= 2*p1 + 1; p3 += 2) {
            if (p3 < MAXV && isPrime[p3]
                    && check(p1, p2, p3)
                    && check(p2, p3, p1)
                    && check(p3, p1, p2)) {
                cnt++;
                if (cnt == k) {
                    cout << p1 << ' ' << p2 << ' ' << p3 << endl;
                    return 0;
                }
            }
        }
    }

    return 0;

    for (int i1 = 0; i1 < SZ(primes); i1++) {
        for (int i2 = i1; i2 < SZ(primes); i2++) {
            for (int i3 = i2; i3 < SZ(primes); i3++) {
                int p1 = primes[i1];
                int p2 = primes[i2];
                int p3 = primes[i3];

                if (check(p1, p2, p3)
                        && check(p2, p3, p1)
                        && check(p3, p1, p2)) {
                    assert(p1 == p2);
                    assert(p3 == 2*p1 + 1 || p3 == 2*p1 - 1);
                    cout << p1 << ' ' << p2 << ' ' << p3 << endl;
                }
            }
        }
    }

    // d1 = d2
    // (d1 + d2)^2 = 4d1^2 - 1
    // (2d1 - 1) * (2d1 + 1)
    // --> d3 = 2d1 - 1 hoac 2d1 + 1
    // d1 = 2
    // --> (d2 + d3): odd
    // --> d2 = 2
    // --> (d3 + d1): odd
    //
    // (d1+d2)^2 - 1 = 15
    // --> d3 in {3, 5}
    //
    // d1 = 3
    // --> (d2 + d3)^2 - 1 = 0 mod 3
    // --> (d2 + d3) != 0 mod 3

    return 0;
}

/*

x1, x2, x3 >= 0, int

(d1 + d2)^2 - 1 = x3 * d3
(d2 + d3)^2 - 1 = x1 * d1
(d3 + d1)^2 - 1 = x2 * d2

 */
