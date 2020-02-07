#include<bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 0, _n = n; i < _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }

using Temp = int;
void read(Temp& t) {
    static double val;
    scanf("%lf", &val);
    t = round(val * 1e6);
}

struct Cloth {
    Temp l, r;
};

bool operator < (const Cloth& a, const Cloth& b) {
    if (a.r != b.r) return a.r > b.r;
    return a.l < b.l;
}

int main() {
    freopen("clothes.in", "r", stdin);
    freopen("clothes.out", "w", stdout);

    int nDay; scanf("%d", &nDay);
    std::vector<Temp> days(nDay);
    for (auto& day : days) {
        read(day);
    }

    int nCloth; scanf("%d", &nCloth);
    std::vector<Cloth> clothes(nCloth);
    for (auto& cloth : clothes) {
        read(cloth.l);
        read(cloth.r);
    }

    std::sort(clothes.begin(), clothes.end());

    const int INF = 30e6;
    std::vector<int> covered;
    covered.push_back(INF);

    int cur_cloth = 0;
    while (cur_cloth < nCloth) {
        int cur_covered = covered.back();
        int next_covered = cur_covered;
        while (cur_cloth < nCloth && clothes[cur_cloth].r >= cur_covered) {
            next_covered = std::min(next_covered, clothes[cur_cloth].l);
            cur_cloth++;
        }

        if (next_covered == cur_covered) break;
        covered.push_back(next_covered);
    }

    try {
        int64_t res = 0;
        for (auto day : days) {
            if (day < covered.back()) {
                throw 1;
            }
            res += std::lower_bound(covered.begin(), covered.end(), day, std::greater<int>()) - covered.begin();
        }
        std::cout << res;
    } catch (...) {
        std::cout << -1;
    }
    std::cout << '\n';
}
