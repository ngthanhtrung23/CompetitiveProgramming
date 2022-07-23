#include "bits/stdc++.h"
using namespace std;

bool check(const std::vector<int>& a, int n) {
    for (int x = 2; x <= n; x++) {
        bool has = false;

        int sz = a.size();
        for (int i = 0; i < sz; i++) {
            for (int j = i+1; j < sz; j++) {
                if (a[i] % x == a[j] % x) {
                    has = true;
                    break;
                }
            }
        }
        if (!has) return false;
    }
    return true;
}

int main() {
    int n;

    while (std::cin >> n) {
        int first_diff = n / 2 + 1;
        int cnt_diff = n - first_diff + 1;

        int best_start = 0;
        int best_len = 1000111000;
        for (int start = 1; start <= 1000 && start <= n+1; start++) {
            int len = start + (cnt_diff + start - 1) / start;
            
            if (len < best_len) {
                best_len = len;
                best_start = start;
            }
        }

        std::vector<int> res;
        for (int i = 1; i <= best_start; i++) {
            res.push_back(i);
        }
        for (int diff = first_diff; diff <= n; diff += best_start) {
            res.push_back(std::min(best_start + diff, n+1));
        }

        /*
        assert(res.size() == best_len);
        DEBUG(res);
        DEBUG(check(res, n));
        */

        std::cout << res.size() << std::endl;
        for (auto r : res) std::cout << r << ' ';
        std::cout << std::endl;
        break;
    }
    return 0;
}
