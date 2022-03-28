#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    std::map<int, int> cnt;
    std::set<int> uniques;

    int n; std::cin >> n;
    while (n--) {
        int x; std::cin >> x;
        cnt[x] += 1;
        if (cnt[x] == 1) {
            uniques.insert(x);
        } else {
            if (uniques.count(x)) uniques.erase(x);
        }
        std::cout << (uniques.empty() ? -1 : *uniques.begin()) << '\n';
    }
    return 0;
}
