#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <complex>
#include <iomanip>
#include <cstring>
using namespace std;
#define For(i,a,b) for(int i=a;i<=b;i++)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;i++)
#define Ford(i,a,b) for(int i=a;i>=b;i--)
#define fi first
#define se second
#define sr(x) (int)x.size()
#define BUG(x) {cout << #x << " = " << x << endl;}
#define PR(x,a,b) {cout << #x << " = "; For(_,a,b) cout << x[_] << ' '; cout << endl;}
#define Bit(s,i) ((s&(1<<i))>0)
#define Two(x) (1<<x)
const int modul = 1000000007;
const int nmax = 1000;
const double e = 1e-8;
const double pi = acos(-1);
typedef long long ll;
typedef pair<int,int> pii;

int n;
char s[1000111];
int f[1000111][2];

void update(int &a, int b) {
    if (a < 0) a = b;
    else a = min(a, b);
}

int main() {
//    freopen("input.txt", "r", stdin);
    while (scanf("%d\n", &n) == 1) {
        gets(s);
        memset(f, -1, sizeof f);
        f[0][0] = 0; f[0][1] = 1;
        
        FOR(i,0,n-1) {
            if (f[i][0] >= 0) {
                if (s[i] == 'A') {
                    update(f[i+1][0], f[i][0]);
                    update(f[i+1][1], f[i][0] + 2);
                }
                else {
                    update(f[i+1][0], f[i][0] + 1);
                    update(f[i+1][1], f[i][0] + 2);
                }
            }
            if (f[i][1] >= 0) {
                if (s[i] == 'A') {
                    update(f[i+1][1], f[i][1] + 1);
                    update(f[i+1][0], f[i][1]);
                }
                else {
                    update(f[i+1][1], f[i][1]);
                    update(f[i+1][0], f[i][1] + 1);
                }
            }
        }
        cout << min(f[n][0], f[n][1]) << endl;
    }
    return 0;
}
