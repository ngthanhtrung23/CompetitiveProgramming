// Algo: simulation
// NOTE: it seems test data for this problem is broken. Reading line by
//       line resulted in MLE, but reading token by token is fine.

// template {{{
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))
#define ALL(s) (s).begin(), (s).end()

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if (i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {
    return uniform_int_distribution<long long> (l, r)(rng);
}

template<typename T>
vector<T> read_vector(int n) {
    vector<T> res(n);
    for (int& x : res) cin >> x;
    return res;
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}

// }}}

using Instruction = pair<string, int>;

Instruction read() {
    Instruction res;
    cin >> res.first;
    res.second = -1;

    if (res.first == "PUSH" || res.first == "IFZERO") {
        cin >> res.second;
    }

    return res;
}

void solve() {
    int n; cin >> n;

    vector<Instruction> program(n);
    REP(i,n) program[i] = read();

    stack<int> st;
    int pc = 0;  // program counter
    int r = 0;   // register

    while (true) {
        if (program[pc].first == "PUSH") {
            st.push(program[pc].second);
            ++pc;
        } else if (program[pc].first == "STORE") {
            r = st.top(); st.pop();
            ++pc;
        } else if (program[pc].first == "LOAD") {
            st.push(r);
            ++pc;
        } else if (program[pc].first == "PLUS") {
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            st.push(a + b);
            ++pc;
        } else if (program[pc].first == "TIMES") {
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            st.push(a * b);
            ++pc;
        } else if (program[pc].first == "IFZERO") {
            int t = st.top(); st.pop();
            if (t == 0) {
                pc = program[pc].second;
            } else {
                pc++;
            }
        } else {
            cout << st.top() << endl;
            return;
        }
    }
}
