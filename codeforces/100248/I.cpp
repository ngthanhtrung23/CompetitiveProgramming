#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int ui;
typedef unsigned long long ull;

#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)
#define Fit(i,v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
#define Fitd(i,v) for(__typeof((v).rbegin()) i = (v).rbegin(); i != (v).rend(); ++i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))

template<class F, class T> T convert(F a, int p = -1) {
    stringstream ss;
    if (p >= 0)
        ss << fixed << setprecision(p);
    ss << a;
    T r;
    ss >> r;
    return r;
}
template<class T> T gcd(T a, T b) {
    T r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
template<class T> T lcm(T a, T b) {
    return a / gcd(a, b) * b;
}
template<class T> T sqr(T x) {
    return x * x;
}
template<class T> T cube(T x) {
    return x * x * x;
}
template<class T> int getbit(T s, int i) {
    return (s >> i) & 1;
}
template<class T> T onbit(T s, int i) {
    return s | (T(1) << i);
}
template<class T> T offbit(T s, int i) {
    return s & (~(T(1) << i));
}
template<class T> int cntbit(T s) {
    return s == 0 ? 0 : cntbit(s >> 1) + (s & 1);
}

typedef pair<int, int> II;
const ld PI = acos(-1.0);
const ld eps = 1e-9;
const int dr[] = { -1, 0, +1, 0 };
const int dc[] = { 0, +1, 0, -1 };
const int inf = (int) 1e9 + 5;
const ll linf = (ll) 1e16 + 5;
const ll mod = (ll) 1e9 + 7;

const int maxn = 1000000 + 5;

char a[maxn];
int n;
int f[maxn][2];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//      freopen("input.txt", "r", stdin);
    cin >> n >> (a + 1);
    For(i,1,n) a[i] -= 'A';
    For(i,1,n) {
        For(j,0,1) {
            if (a[i] == j) {
                f[i][j] = f[i-1][j];
            } else {
                f[i][j] = min(f[i-1][j], f[i-1][1-j])+ 1;
            }
        }
    }
    cout << f[n][0];
    return 0;
}