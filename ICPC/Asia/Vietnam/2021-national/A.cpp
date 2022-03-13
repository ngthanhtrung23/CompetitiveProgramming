#include <bits/stdc++.h>
using namespace std;

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& out, const Con& con) {
    out << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        out << (it == beg ? "" : ", ") << *it;
    }
    return out << '}';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    // read input
    int n; std::cin >> n;
    std::vector<std::vector<int>> ids_of(n+1);
    for (int i = 0; i < n*n; i++) {
        int color; std::cin >> color;
        --color;
        ids_of[color].push_back(i);
    }

    // process each row
    std::vector<int> res(n*n);
    for (int row = 1; row <= n; row++) {
        // find remaining colors
        std::set< std::pair<int,int> > remainings;
        for (int color = 0; color <= n; color++) {
            if (!ids_of[color].empty()) {
                remainings.insert({ids_of[color].size(), color});
            }
        }

        // 
        if (remainings.begin()->first >= n) {
            int color = remainings.begin()->second;
            int k = ids_of[color].size();
            assert(k >= n);
            for (int i = k-1; i >= k-n; i--) {
                res[ids_of[color][i]] = row;
            }
            ids_of[color].resize(k - n);
        } else {
            int color1 = remainings.begin()->second;
            int color2 = remainings.rbegin()->second;

            // all color1 -> this row
            for (int id : ids_of[color1]) {
                res[id] = row;
            }

            int need = n - ids_of[color1].size();
            ids_of[color1].clear();

            int k = ids_of[color2].size();
            for (int i = k-1; i >= k-need; i--) {
                res[ids_of[color2][i]] = row;
            }
            ids_of[color2].resize(k - need);
        }
    }

    std::cout << "YES\n";
    for (int r : res) std::cout << r << ' ';
    std::cout << std::endl;
    return 0;
}
