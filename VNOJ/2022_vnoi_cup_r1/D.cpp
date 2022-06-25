#include "bits/stdc++.h"

const int MOD = 1e9 + 7;

int two(int x) {
    return 1LL<<x;
}
int contains(int s, int x) {
    return (s >> x) & 1;
}

// Given array D[i]
// Calculate D'[i] = sum( D[j] : j is superset of i )
void magic(std::vector<int>& D, int K) {
    std::reverse(D.begin(), D.end());
    for (int i = 0; i < K; ++i)
        for (int mask = 0; mask < (1 << K); ++mask)
            if ((mask >> i) & 1) D[mask] += D[mask ^ (1 << i)];
    std::reverse(D.begin(), D.end());
}

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    std::vector<int> p2(1000111);
    p2[0] = 1;
    for (int i = 1; i < (int) p2.size(); i++) {
        p2[i] = p2[i-1] * 2 % MOD;
    }

    int nCities, nFriends; std::cin >> nCities >> nFriends;
    std::vector<int> a(nCities, two(nFriends) - 1);
    std::vector<int> b(nCities, two(nFriends) - 1);
    
    for (int i = 0; i < nFriends; i++) {
        int k; std::cin >> k;

        for (int t = 0; t < k; t++) {
            int x; std::cin >> x;
            if (x > 0) {
                a[x - 1] -= two(i);
            } else {
                b[-x - 1] -= two(i);
            }
        }
    }

    // a[i] = set of requirements NOT containing +i
    // b[i] = set of requirements NOT containing -i
    // a[i] & b[i] = set of requirements NOT containing +i NOR -i

    std::vector<int> cnt_a(two(nFriends));
    std::vector<int> cnt_b(two(nFriends));
    std::vector<int> cnt_a_and_b(two(nFriends));
    for (int i = 0; i < nCities; i++) {
        cnt_a[a[i]]++;
        cnt_b[b[i]]++;
        cnt_a_and_b[a[i] & b[i]]++;
    }

    magic(cnt_a, nFriends);
    magic(cnt_b, nFriends);
    magic(cnt_a_and_b, nFriends);

    // cnt_a[mask] = how many +i NOT in submask of mask
    // cnt_b[mask] = how many -i NOT in submask of mask

    int res = 0;
    for (int mask = 0; mask < two(nFriends); mask++) {
        int pos = nCities - cnt_a[mask];
        int neg = nCities - cnt_b[mask];
        int common = pos + neg - (nCities - cnt_a_and_b[mask]);

        if (common == 0) {
            int cur = p2[nCities - pos - neg];
            if (__builtin_popcount(mask) % 2) {
                res = (res - cur + MOD) % MOD;
            } else {
                res = (res + cur) % MOD;
            }
        }
    }
    std::cout << res << std::endl;
    return 0;
}
