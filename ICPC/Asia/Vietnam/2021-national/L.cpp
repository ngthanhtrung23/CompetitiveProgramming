// Let b[i] = product of prime factors of a[i]
//     (a[i]^k + a[j]^k) % a[i]a[j] = 0
// <=> (a[i] + a[j])^k % a[i]a[j] = 0
// <=> (b[i] + b[j])^k % b[i]b[j] = 0
// <=> b[i] = b[j]

#include <bits/stdc++.h>
using namespace std;

const int MV = 1e7;

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n;

    std::vector<int> prime_prod(MV + 1, 1);
    for (int i = 2; i <= MV; i++) {
        if (prime_prod[i] == 1) {
            // i is prime
            for (int j = i; j <= MV; j += i) {
                prime_prod[j] *= i;
            }
        }
    }

    std::map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        cnt[prime_prod[x]] += 1;
    }

    long long res = 0;
    for (auto [val, c] : cnt) {
        res += c * (c - 1LL) / 2;
    }
    std::cout << res << std::endl;

    return 0;
}
