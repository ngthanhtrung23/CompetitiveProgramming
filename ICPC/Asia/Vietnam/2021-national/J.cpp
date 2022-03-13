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

int n;
using State = std::array<int, 9>;

struct Move {
    std::array<int, 4> pins;
    int c;
    int rot;
};
std::ostream& operator << (std::ostream& cout, const Move& m) {
    for (auto pin : m.pins) cout << pin << ' ';
    cout << m.c + 1 << ' ' << m.rot;
    return cout;
}

std::map<int, int> CLOCK_TO_PIN {
    {0, 0},
    {2, 1},
    {6, 2},
    {8, 3},
};
std::map<int, std::vector<int>> PIN_TO_CLOCKS {
    {0, {0, 1, 3, 4}},
    {1, {1, 2, 4, 5}},
    {2, {3, 4, 6, 7}},
    {3, {4, 5, 7, 8}},
};

State apply(Move move, State s) {
    std::set<int> affected_clocks;

    affected_clocks.insert(move.c);
    auto first_pin = CLOCK_TO_PIN[move.c];

    if (move.pins[first_pin]) {
        for (int pin = 0; pin < 4; pin++) {
            if (move.pins[pin]) {
                for (int clock : PIN_TO_CLOCKS[pin]) {
                    affected_clocks.insert(clock);
                }
            }
        }
    }

    State new_state = s;
    for (int clock : affected_clocks) {
        new_state[clock] = (new_state[clock] + move.rot) % n;
    }
    return new_state;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    // read input
    std::cin >> n;
    State start;
    for (int& c : start) std::cin >> c;

    //
    std::cout << "YES\n";
    std::vector<Move> moves;

    auto rotate = [&] (int clock, std::array<int, 4> pins, int from, int to) {
        int rot = (to + n - from) % n;
        if (!rot) {
            return;
        }

        Move move{ pins, clock, rot };
        moves.push_back(move);
        start = apply(move, start);
    };

    // make 1 & 4 same
    rotate(8, {0, 0, 0, 1}, start[4], start[1]);
    // make 1 & 4 & 3 same
    rotate(2, {0, 1, 0, 0}, start[1], start[3]);
    // make 1 & 4 & 3 & 5 same
    rotate(0, {1, 0, 0, 0}, start[3], start[5]);
    // make 1 & 4 & 3 & 5 & 7 same
    rotate(0, {1, 1, 0, 0}, start[5], start[7]);

    // move 1 4 3 5 7 to 0
    rotate(0, {1, 1, 1, 1}, start[7], 0);

    // Fix corners
    for (int clock : {0, 2, 6, 8}) {
        rotate(clock, {0, 0, 0, 0}, start[clock], 0);
    }

    std::cout << moves.size() << '\n';
    for (auto move : moves) std::cout << move << '\n';
    return 0;
}
