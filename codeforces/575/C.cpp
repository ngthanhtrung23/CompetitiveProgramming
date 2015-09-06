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
typedef long double ld;
#define eps 1e-9
typedef pair<int, int> II;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
#define PI 2 * acos(0)

#define maxn 21

struct Hungary {
    int nx, ny, cost[maxn][maxn], fx[maxn], fy[maxn], maty[maxn], which[maxn], dist[maxn], maxmat;
    bool used[maxn], sw;

    void init(int _nx, int _ny) {
        sw = 0; if (_nx > _ny) { swap(_nx, _ny); sw = 1; } // Because nx <= ny
        nx = _nx; ny = _ny; ms(fx, 0); ms(fy, 0); ms(maty, 0);
        For(i, 0, nx) For(j, 0, ny) cost[i][j] = inf;
    }

    void add(int x, int y, int c) { if (sw) swap(x, y); cost[x][y] = c; }

    int mincost() {
        For(x, 1, nx) {
            int y0 = 0; maty[0] = x;
            For(y, 0, ny) { dist[y] = inf + 1; used[y] = false; }

            do {
                used[y0] = true;
                int x0 = maty[y0], delta = inf + 1, y1;

                For(y, 1, ny) if (!used[y]) {
                    int curdist = cost[x0][y] - fx[x0] - fy[y];
                    if (curdist < dist[y]) {
                        dist[y] = curdist;
                        which[y] = y0;
                    }
                    if (dist[y] < delta) {
                        delta = dist[y];
                        y1 = y;
                    }
                }

                For(y, 0, ny) if (used[y]) {
                    fx[maty[y]] += delta;
                    fy[y] -= delta;
                } else dist[y] -= delta;

                y0 = y1;
            } while (maty[y0] != 0);

            do {
                int y1 = which[y0];
                maty[y0] = maty[y1];
                y0 = y1;
            } while (y0);
        }
        int ret = 0; maxmat = 0;
        For(y, 1, ny) {
            int x = maty[y];
            if (cost[x][y] < inf) { ret += cost[x][y]; ++maxmat; }
        }
        return ret;
    }

    int fix(vector<int> V) {
        Rep(i, sz(V)) {

            int x = V[i] + 1;
//            cout << "tt " << x << endl;
            int y0 = 0; maty[0] = x;
            For(y, 0, ny) { dist[y] = inf + 1; used[y] = false; }

            do {
                used[y0] = true;
                int x0 = maty[y0], delta = inf + 1, y1;

                For(y, 1, ny) if (!used[y]) {
                    int curdist = cost[x0][y] - fx[x0] - fy[y];
                    if (curdist < dist[y]) {
                        dist[y] = curdist;
                        which[y] = y0;
                    }
                    if (dist[y] < delta) {
                        delta = dist[y];
                        y1 = y;
                    }
                }

                For(y, 0, ny) if (used[y]) {
                    fx[maty[y]] += delta;
                    fy[y] -= delta;
                } else dist[y] -= delta;

                y0 = y1;
            } while (maty[y0] != 0);

            do {
                int y1 = which[y0];
                maty[y0] = maty[y1];
                y0 = y1;
            } while (y0);
        }
        int ret = 0; maxmat = 0;
        For(y, 1, ny) {
            int x = maty[y];
            if (cost[x][y] < inf) {
                ret += cost[x][y]; ++maxmat;
//              cout << x << " " << y << " " << cost[x][y] << endl;
            }
        }
        return ret;
    }
} hungary;

int n, a[maxn][maxn], b[maxn][maxn], flag[maxn];

int cal(int mask){
    hungary.init(n, n);
    Rep(i, n) Rep(j, n){
        if(getbit(mask, i)) hungary.add(i + 1, j + 1, -a[i][j]);
        else hungary.add(i + 1, j + 1, -b[i][j]);
    }
    return -hungary.mincost();
}

int main() {
//  freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n;
    Rep(i, n) Rep(j, n) cin >> a[i][j];
    Rep(i, n) Rep(j, n) cin >> b[i][j];
    int res = 0;
    int nho = 0;
    Rep(mask, (1 << n)) if(cntbit(mask) == n / 2){
//      cout << mask << endl;
        if(!nho){
            hungary.init(n, n);
            Rep(i, n) Rep(j, n){
                if(getbit(mask, i)) hungary.add(i + 1, j + 1, -a[i][j]);
                else hungary.add(i + 1, j + 1, -b[i][j]);
            }
            res = max(res, -hungary.mincost());
        } else{
            vector<int> temp;
            ms(flag, 0);
            Rep(i, n) {
                if(getbit(nho, i) != getbit(mask, i)) {
                    temp.pb(i);
                    flag[i + 1] = 1;
                }
            }

//          cout << nho << " " << mask << " " << sz(temp) << endl;
            Rep(i, n) if(flag[hungary.maty[i + 1]]){

//              cout << i + 1 << " zz " << hungary.maty[i + 1] << endl;

//                hungary.fx[hungary.maty[i + 1]] = 0;
//                hungary.fy[i + 1] = 0;
//                hungary.which[i + 1] = 0;
                hungary.maty[i + 1] = 0;
            }
            Rep(i, sz(temp)) Rep(j, n){
//              cout << temp[i] + 1 << " vdsfsd " << j + 1 << " " << b[temp[i]][j] << endl;
                hungary.add(temp[i] + 1, j + 1, getbit(mask, temp[i]) ? -a[temp[i]][j] : -b[temp[i]][j]);
            }

            int A = -hungary.fix(temp);
//            int B = cal(mask);
//            cout << "fix " << A << endl;
            res = max(res, A);
        }
//        cout << mask << endl;
//        For(i, 1, n){
//          cout << i << " " << hungary.maty[i] << " " << hungary.fx[hungary.maty[i]] << " " << hungary.fy[i] << endl;
//        }

        nho = mask;
    }
    cout << res << endl;

    return 0;
}
