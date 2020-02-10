#include<bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 0, _n = n; i < _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }
 
int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    std::array<int, 4> a;
    for (size_t i = 0; i < 4; i++) {
        std::cin >> a[i];
    }
    int sum = std::accumulate(a.begin(), a.end(), 0);
    int need; std::cin >> need;
 
    bool can = std::any_of(
            a.begin(), a.end(),
            [sum, need] (int val) { return sum - val >= need; });
    std::cout << (can ? "WAW" : "AWW") << std::endl;
}