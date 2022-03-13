#include "bits/stdc++.h"
using namespace std;

#define int long long
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

// ModInt
inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
    unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
    asm(
        "divl %4; \n\t"
        : "=a" (d), "=d" (m)
        : "d" (xh), "a" (xl), "r" (y)
    );
#else
    __asm {
        mov edx, dword ptr[xh];
        mov eax, dword ptr[xl];
        div dword ptr[y];
        mov dword ptr[d], eax;
        mov dword ptr[m], edx;
    };
#endif
    out_d = d; out_m = m;
}

template<int MOD>
struct ModInt {
    unsigned x;

    constexpr ModInt() : x(0) { }
    constexpr ModInt(signed long long sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }

#define COMPAREOP(OP) bool constexpr operator OP(ModInt b) const { return x OP b.x; }
    COMPAREOP(==) COMPAREOP(!=) COMPAREOP(<) COMPAREOP(>) COMPAREOP(<=) COMPAREOP(>=)
#undef COMPAREOP

    ModInt operator-() const { return ModInt(x ? MOD - x : 0); }

    ModInt constexpr& operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
    ModInt constexpr& operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
    ModInt &operator*=(ModInt that) {
        unsigned dummy;
        fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, x);
        return *this;
    }
    ModInt operator*(ModInt that) const {
        ModInt res;
        unsigned dummy;
        fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, res.x);
        return res;
    }
    ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
    ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }

    // Below: copied from user202729_, not tested.
    ModInt inv() const {
        int a = x, b = MOD, ax = 1, bx = 0;
        while (b) {
            int q = a/b, t = a%b;
            a = b; b = t;
            t = ax - bx*q;
            ax = bx; bx = t;
        }
        assert(a == 1);
        if (ax < 0) ax += MOD;
        return ax;
    }
    ModInt& operator /= (ModInt m) { return (*this) *= m.inv(); }
    ModInt operator / (ModInt that) const { return ModInt(*this) /= that; }
};

template<int MOD>
ModInt<MOD> power(ModInt<MOD> n, long long k) {
    if (k == 0) return ModInt<MOD> (1);
    ModInt<MOD> res(1);
    while (k > 0) {
        if (k & 1) res = res * n;
        n = n * n;
        k >>= 1;
    }
    return res;
}

const int MOD = 998244353;
using modular = ModInt<MOD>;

std::ostream& operator << (std::ostream& cout, const modular& m) {
    cout << m.x;
    return cout;
}
std::istream& operator >> (std::istream& cin, modular& m) {
    cin >> m.x;
    return cin;
}

// Splay node
template<class K, class S, class F>
struct node_t {
    using Node = node_t<K, S, F>;

    std::array<Node*, 2> child;
    Node *father;
    
    // Whether we will need to reverse this subtree.
    // Handling reverse operations requires some specialized code,
    // so I couldn't put this in F
    bool reverse;

    K key;
    S data;
    F lazy;
};

// Aggregate data
struct S {
    modular sum_square;
    long long size;
    bool same_color;

    int left_color; long long left_size;
    int right_color; long long right_size;
};
ostream& operator << (ostream& cout, const S& s) {
    if (s.same_color) {
        cout << '[' << s.left_color << 'x' << s.size << ']';
    } else {
        cout << '[' << "? " << s.sum_square << ']';
    }
    return cout;
}

char to_char(int c) {
    if (c == 0) return 'W';
    return 'B';
}
int to_color(char c) {
    return c == 'W' ? 0 : 1;
}


S from(char c, int k) {
    int color = to_color(c);
    return S {
        modular(k) * modular(k),
        k,
        true,
        color, k,
        color, k,
    };
}

S empty() {
    return {
        0LL,   // sum sq
        0LL,   // size
        true,  // same_color
        -1, 0, // left
        -1, 0, // right
    };
}

// flip color?
using F = bool;

modular sqr(modular x) { return x*x; }

S op(S left, S right) {
    if (left.size == 0) return right;
    if (right.size == 0) return left;

    S res;
    res.sum_square = left.sum_square + right.sum_square;
    if (left.right_color == right.left_color) {
        res.sum_square -= sqr(left.right_size);
        res.sum_square -= sqr(right.left_size);
        res.sum_square += sqr(left.right_size + right.left_size);
    }

    res.size = left.size + right.size;
    res.same_color = left.same_color && right.same_color && left.left_color == right.left_color;

    res.left_color = left.left_color;
    res.left_size = left.left_size;
    if (left.same_color && left.left_color == right.left_color) {
        res.left_size += right.left_size;
    }

    res.right_color = right.right_color;
    res.right_size = right.right_size;
    if (right.same_color && right.right_color == left.right_color) {
        res.right_size += left.right_size;
    }

    if (res.same_color) {
        assert(res.left_color == res.right_color);
        assert(res.left_size == res.right_size);
        assert(res.left_size == res.size);
    }
    return res;
}

S op(S left, S mid, S right) {
    return op(op(left, mid), right);
}

std::pair<S, S> e() {
    return {empty(), empty()};
}

S mapping(F f, S cur) {
    if (!f) return cur;
    return S {
        cur.sum_square,
        cur.size,
        cur.same_color,

        1 - cur.left_color, cur.left_size,
        1 - cur.right_color, cur.right_size,
    };
}

std::pair<S, S> mapping(F f, node_t<S, S, F>* node) {
    return {
        mapping(f, node->key),
        mapping(f, node->data),
    };
}

bool composition(F f, F g) {
    return f ^ g;
}

F id() {
    return false;
}


using Node = node_t<S, S, F>;

Node* nil;
Node *root;

// private:
static void initNil() {
    nil = new Node();
    nil->child[0] = nil->child[1] = nil->father = nil;
    nil->reverse = false;
    std::tie(nil->key, nil->data) = e();
    nil->lazy = id();
}
void pushUp(Node* x) {
    if (x == nil) return;
    x->data = op(x->child[0]->data, x->key, x->child[1]->data);
}
void pushDown(Node* x) {
    if (x == nil) return;

    if (x->reverse) {
        for (auto c : x->child) {
            if (c != nil) {
                c->reverse ^= 1;
            }
        }
        std::swap(x->child[0], x->child[1]);
        x->reverse = false;
    }

    for (auto c : x->child) {
        if (c != nil) {
            std::tie(c->key, c->data) = mapping(x->lazy, c);
            c->lazy = composition(x->lazy, c->lazy);
        }
        // For problem like UPIT, where we want to push different
        // lazy tags to left & right children, may need to modify
        // code here
        // (query L R X: a(L) += X, a(L+1) += 2X, ...)
        // e.g. for UPIT:
        // x->lazy.add_left += (1 + c->size) * x->lazy.step;
    }

    x->lazy = id();
}
Node* createNode(S key) {
    Node *res = new Node();
    res->child[0] = res->child[1] = res->father = nil;
    res->key = key;
    res->data = e().second;
    res->lazy = id();
    return res;
}
void setChild(Node *x, Node *y, int d) {
    x->child[d] = y;
    if (y != nil) y->father = x;
}

// Assumption: x is father of y
int getDirection(Node *x, Node *y) {
    assert(y->father == x);
    return x->child[0] == y ? 0 : 1;
}
// create subtree from keys[l, r-1]
Node* createNode(const vector<S>& keys, int l, int r) {
    if (l >= r) {  // empty
        return nil;
    }
    int mid = (l + r) / 2;
    Node *p = createNode(keys[mid]);
    Node *left = createNode(keys, l, mid);
    Node *right = createNode(keys, mid + 1, r);

    setChild(p, left, 0);
    setChild(p, right, 1);

    pushUp(p);
    return p;
}
void traverse(Node* x, vector<S>& keys) {
    if (x == nil) return;
    pushDown(x);
    traverse(x->child[0], keys);
    keys.push_back(x->key);
    traverse(x->child[1], keys);
}
vector<S> getKeys(Node* r) {
    vector<S> keys;
    traverse(r, keys);
    return keys;
}

/**
    * Before:
    *    y
    *    |
    *    x
    *  /
    * z
    *  \
    *  zchild
    *
    * After:
    *    y
    *    |
    *    z
    *     \
    *      x
    *     /
    *  zchild
    */
void rotate(Node *x, int d) {
    Node *y = x->father;
    Node *z = x->child[d];
    setChild(x, z->child[d ^ 1], d);
    setChild(y, z, getDirection(y, x));
    setChild(z, x, d ^ 1);
    pushUp(x);
    pushUp(z);
}
// Make x root of tree
Node *splay(Node *x) {
    if (x == nil) return nil;
    while (x->father != nil) {
        Node *y = x->father;
        Node *z = y->father;
        int dy = getDirection(y, x);
        int dz = getDirection(z, y);
        if (z == nil) {
            rotate(y, dy);
        } else if (dy == dz) {
            rotate(z, dz);
            rotate(y, dy);
        } else {
            rotate(y, dy);
            rotate(z, dz);
        }
    }
    return x;
}

std::pair<int, Node*> _kth(Node* p, int k) {
    assert(p->data.size > k);
    pushDown(p);
    // left: [0, left->size - 1]
    if (k < p->child[0]->data.size) {
        return _kth(p->child[0], k);
    }
    k -= p->child[0]->data.size;
    
    if (k < p->key.size) {
        return {k, p};
    }

    k -= p->key.size;
    return _kth(p->child[1], k);
}

// k in [0, n-1]
std::pair<int, Node*> kth(int k) {
    auto res = _kth(root, k);
    splay(res.second);
    root = res.second;
    return res;
}

// Return <L, R>:
// - L contains [0, k-1]
// - R contains [k, N-1]
// Modify tree
pair<Node*, Node*> cut(int k) {
    if (k == 0) {
        return {nil, root};
    } else if (k == root->data.size) {
        return {root, nil};
    } else {
        auto [start, left] = kth(k - 1);  // kth already splayed
        assert(left->key.same_color);
        if (start == left->key.size - 1) {
            Node* right = left->child[1];
            left->child[1] = right->father = nil;

            pushUp(left);
            return {left, right};
        } else {
            Node* left_root = createNode(from(to_char(left->key.left_color), start + 1));
            Node* right_root = createNode(from(to_char(left->key.left_color),
                        left->key.size - start - 1));

            setChild(left_root, left->child[0], 0);
            setChild(right_root, left->child[1], 1);
            // left_root->child[0] = left->child[0];
            // right_root->child[1] = left->child[1];

            pushUp(left_root);
            pushUp(right_root);

            return {left_root, right_root};
        }
    }
}

// Return <X, Y, Z>:
// - X contains [0, u-1]
// - Y contains [u, v-1]
// - Z contains [v, N-1]
// This is useful for queries on [u, v-1]
// Modify tree
tuple<Node*, Node*, Node*> cut(int u, int v) {
    auto [xy, z] = cut(v);
    root = xy;
    auto [x, y] = cut(u);
    return {x, y, z};
}

Node* join(Node *x, Node *y) {
    if (x == nil) {
        return y;
    }
    while (1) {
        pushDown(x);
        if (x->child[1] == nil) break;
        x = x->child[1];
    }
    splay(x);
    setChild(x, y, 1);
    pushUp(x);
    return x;
}

void apply(int u, int v, const F& f) {
    if (u == v) return;

    auto [x, y, z] = cut(u, v);
    y->lazy = composition(f, y->lazy);
    std::tie(y->key, y->data) = mapping(f, y);

    root = join(join(x, y), z);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; std::cin >> n >> q;
    assert(1 <= n && n <= 200000);
    assert(1 <= q && q <= 200000);
    std::string s; std::cin >> s;
    assert(s.size() == n);

    std::vector<S> nodes;
    int l = 0;
    while (l < n) {
        int r = l;
        while (r < n && s[r] == s[l]) ++r;

        nodes.push_back(from(s[l], r - l));

        l = r;
    }

    initNil();
    root = createNode(nodes, 0, (int) nodes.size());

    while (q--) {
        char typ; std::cin >> typ;
        if (typ == 'Q') {
            int x, k; std::cin >> x >> k;
            --x;
            int y = x + k;
            auto [t1, t2, t3] = cut(x, y);

            std::cout << t2->data.sum_square << '\n';

            root = join(join(t1, t2), t3);
        } else if (typ == 'I') {
            int x, k; char c;
            std::cin >> x >> k >> c;

            auto [t1, t3] = cut(x);
            Node* t2 = createNode(from(c, k));

            root = join(join(t1, t2), t3);
        } else if (typ == 'F') {
            int x, k; std::cin >> x >> k;
            --x;
            int y = x + k;
            apply(x, y, true);
        } else if (typ == 'D') {
            int x, k; std::cin >> x >> k;
            --x;
            int y = x + k;

            auto [t1, t2, t3] = cut(x, y);
            root = join(t1, t3);
        }
    }
    return 0;
}
