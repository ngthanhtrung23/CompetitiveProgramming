#include "bits/stdc++.h"
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

int32_t main() {
    std::ios::sync_with_stdio(false);
    // read names.
    std::map< std::pair<std::string, std::string>, int > idOf;
    std::string a1, a2, b1, b2;
    int nId = 0;
    while (std::cin >> a1) {
        if (a1[0] == '-') break;

        std::cin >> a2 >> b1 >> b2;
        idOf[make_pair(a1, a2)] = nId;
        idOf[make_pair(b1, b2)] = nId;
        nId++;
    }

    std::string query;
    std::set<int> all;
    while (std::cin >> query && query[0] != 'E') {
        if (query[0] == '+') {
            std::string q1, q2;
            std::cin >> q1 >> q2;

            all.insert(idOf[make_pair(q1, q2)]);
        } else if (query[0] == '-') {
            std::string q1, q2;
            std::cin >> q1 >> q2;

            all.erase(idOf[make_pair(q1, q2)]);
        } else if (query[0] == 'F') {
            std::string q1, q2;
            std::cin >> q1 >> q2;

            int id = idOf[make_pair(q1, q2)];
            std::cout << (all.count(id) ? "FOUND" : "404") << '\n';
        } else if (query[0] == 'U') {
            std::cout << all.size() << '\n';
        }
    }
    return 0;
}
