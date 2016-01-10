#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define inf 1000000005
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))
#define mod 1000000007
#define sz(a) ((int)(a).size())

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcount(s);}
#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)

typedef unsigned long long ull;
typedef long long ll;
typedef double ld;
#define eps 1e-12
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI (2 * acos(0))
#define linf (1ll << 60)

const int base = 1000000000;
const int base_digits = 9;

struct BigInt {
    int a[5];

    BigInt(){
        ms(a, 0);
    }

    BigInt(long long v) {
        *this = v;
    }

    BigInt(const string &s) {
        read(s);
    }

    BigInt operator+(const BigInt &v) const {
        BigInt res;
        for(int i = 0; i < 5; i++) res.a[i] = v.a[i];

        for (int i = 0, carry = 0; i < 5 || carry; i++) {
            res.a[i] += carry + a[i];
            carry = res.a[i] >= base;
            if (carry)
                res.a[i] -= base;
        }
        return res;
    }


    bool operator >(const BigInt &v) const {
        for (int i = 4; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] > v.a[i];
        return false;
    }

    bool operator <(const BigInt &v) const {
        for (int i = 4; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] < v.a[i];
        return false;
    }

    bool operator==(const BigInt &v) const {
        Rep(i, 5) if(a[i] != v.a[i]) return false;
        return true;
    }

    void operator*=(int v) {
        for (int i = 0, carry = 0; i < 5 || carry; ++i) {
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / base);
            a[i] = (int) (cur % base);
            //asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
        }

    }

    BigInt operator*(int v) const {
        BigInt res = *this;
        res *= v;
        return res;
    }

    void read(const string &s) {
        ms(a, 0);
        vector<int> aa;
        aa.clear();
        int pos = 0;
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            aa.push_back(x);
        }
        Rep(i, sz(aa)) a[i] = aa[i];
    }

};


#define maxn 300005

vector<pair<BigInt, int> > A;
vector<int> V[maxn];
int color[maxn], have[maxn], cannot[maxn][10];
vector<string> RR[maxn];
int n, k;

void paint(int id, int c){
    color[id] = c;
    have[c]++;
    Rep(i, sz(V[id])){
        int u = V[id][i];
        cannot[u][c] = 1;
    }

    Rep(i, sz(V[id])){
        int u = V[id][i];
        if(color[u]) continue;
        for(int t = 1; t <= 9; t++) if(!cannot[u][t]){
            paint(u, t);
            break;
        }
    }
}

BigInt cal(string s){
    int havedot = false;
    int count = 20, len = sz(s);
    string res = "";
    for(int i = 0; i < len; i++){
        if(s[i] == '.'){
            havedot = true;
        } else{
            res.pb(s[i]);
            if(havedot) count--;
        }
    }
    Rep(i, count) res.pb('0');
    while(res[0] == '0' && sz(res) > 1) res = res.substr(1, sz(res) - 1);

    return BigInt(res);
}

string s[maxn];
char tmp[55];

int main(){
    freopen("kaleidoscope.in", "r", stdin);
    freopen("kaleidoscope.out", "w", stdout);
//  freopen("in.txt", "r", stdin);
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);

    scanf("%d %d\n", &n, &k);
    Rep(run, n){
        scanf("%s", tmp);
        s[run] = tmp;
        A.pb(mp(cal(s[run]), run));
//        for(int i = 0; i < 5; i++) cout << A[run].fi.a[i] << endl;
    }

    sort(all(A));

//    Rep(i, sz(A)) cout  << A[i].se << endl;
//    BigInt B = BigInt("1111111111111111") + BigInt("1111111111111111");
//    Rep(i, 5) cout << B.a[i] << " " << B.a[i] << endl;

//    cout <<

    BigInt add = BigInt("1");
    Rep(run, 40){
        int u = 0;
        for(int i = 0; i < n; i++){
            while(u < n && A[i].fi + add > A[u].fi) u++;
            if(u != n && A[i].fi + add == A[u].fi){
//              cout << i << " " << u << endl;
                V[i].pb(u);
                V[u].pb(i);
            }
        }
        add = add * 10;
    }

    ms(have, 0);
    ms(cannot, 0);

    Rep(i, n) if(!color[i]){
        paint(i, 1);
    }

    int now = 0;
    For(i, 1, k) if(!have[i]){
        while(have[color[now]] < 2) now++;
        int c = color[now];
        have[c]--;
        have[i]++;
        color[now] = i;
    }



    Rep(i, n){
        int c = color[i];
        string S = s[A[i].se];
//      cout << c << " " << S << endl;
        RR[c].pb(S);
    }

    For(i, 1, k){
        Rep(j, sz(RR[i])){
            printf("%s", RR[i][j].c_str());
            if(j == sz(RR[i]) - 1) puts("");
            else putchar(' ');
        }
    }

    return 0;

}
