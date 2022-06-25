#include "bits/stdc++.h"
#define int long long

struct Package {
    std::vector<int> prizes;
    std::vector<int> sum;

    void read(int nPrizes) {
        prizes.resize(nPrizes);
        for (auto& prize : prizes) std::cin >> prize;
        std::partial_sum(prizes.begin(), prizes.end(), std::back_inserter(sum));
    }

    int sum_all() const {
        return sum.back();
    }
};
bool operator < (const Package& a, const Package& b) {
    return a.sum_all() > b.sum_all();
}

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int nPackages, nPrizes, points;
    std::cin >> nPackages >> nPrizes >> points;

    std::vector<Package> packages(nPackages);
    for (auto& package : packages) {
        package.read(nPrizes);
    }

    std::sort(packages.begin(), packages.end());

    int res = 0;
    if (points % nPrizes == 0) {
        // Case 1: k % m == 0
        int nFull = points / nPrizes;
        for (int i = 0; i < nFull; i++) {
            res += packages[i].sum_all();
        }
    } else {
        // Case 2: k % m > 0
        int nPartial = points % nPrizes;
        int nFull = points / nPrizes;

        // sum[i] = sum of biggest i packages
        std::vector<int> sum(nPackages);
        for (int i = 0; i < nPackages; i++) {
            sum[i] = packages[i].sum_all();
            if (i > 0) sum[i] += sum[i-1];
        }

        // Loop through all i = package where we take partially
        for (int i = 0; i < nPackages; i++) {
            int cur = 0;
            if (i < nFull) {
                cur = sum[nFull]
                    - packages[i].sum_all()
                    + packages[i].sum[nPartial - 1];
            } else {
                cur = sum[nFull - 1] + packages[i].sum[nPartial - 1];
            }
            res = std::max(res, cur);
        }
    }

    std::cout << res << std::endl;
    return 0;
}
