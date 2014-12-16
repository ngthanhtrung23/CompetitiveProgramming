#ifdef SU1
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <iomanip>

#include <cassert>
#include <ctime>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forl(i, n) for (int i = 1; i <= int(n); i++)
#define fore(i, l, r) for (int i = int(l); i <= int(r); i++)
#define ford(i, n) for (int i = int(n - 1); i >= 0; i--)
#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()
#define x first
#define y second
#define ft first
#define sc second
#define pb push_back

typedef long long li;
typedef double ld;
typedef pair<int, int> pt;

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9, PI = acos(-1.0);

const int N = 225 + 3;
const int SN = 15 + 3;

int n, m;
vector<int> g[SN];
vector<int> comp;
int V1, V2;
int used[SN];
int newNum[SN];

void dfs (int v)
{
    used[v] = true;
    forn(i, sz(g[v]))
    {
        int to = g[v][i];
        if (!used[to]) dfs(to);
    }
}

inline bool read()
{
    if (scanf("%d%d", &n, &m) != 2) return false;
    //n = 15;
    
    forn(i, n) g[i].clear();
    
    forn(i, m)
    {
        int a, b;
        assert(scanf("%d%d", &a, &b) == 2);
        --a, --b;
        g[a].pb(b);
        g[b].pb(a);
    }
    
    //forn(i, n) forn(j, n) if (i != j) g[i].pb(j);
    
    assert(scanf("%d%d", &V1, &V2) == 2);
    //V1 = 1, V2 = 15;
    --V1, --V2;
    
    return true;
}

inline bool prepare ()
{
    memset(used, 0, sizeof(used));
    dfs(V1);
    if (!used[V2]) return false;
    memset(newNum, -1, sizeof(newNum));
    comp.clear();
    forn(i, n) if (used[i])
    {
        newNum[i] = sz(comp);
        comp.pb(i);
    }
    return true;
}

int sza;
ld a[N][N];

inline void gauss ()
{
    forn(k, sza)
    {
        int idx = k;
        fore(i, k, sza - 1) if (abs(a[i][k]) > abs(a[idx][k])) idx = i;
        forn(j, sza + 1) swap(a[idx][j], a[k][j]);
        
        assert(abs(a[k][k]) > EPS);
        
        ld val = a[k][k];
        forn(j, sza + 1) a[k][j] /= val;
        
        fore(i, k + 1, sza - 1)
        {
            if (i == k) continue;
            ld x = a[i][k];
            forn(j, sza + 1) a[i][j] -= a[k][j] * x;
        }
    }
}

ld x[N];

inline void solve(int test)
{
    if (!prepare())
    {
        printf("Case #%d:", test);
        forn(i, n) printf(" N/A");
        puts("");
        return;
    }
    
    forn(i, n) g[i].pb(i);
    
    sza = sz(comp) * sz(comp);
    cerr << sza << endl;

    printf("Case #%d:", test);
    
    //const int MAGIC = 1000; 
        
    forn(ver, n)
    {
        if (newNum[ver] == -1)
        {
            printf(" N/A");
            continue;
        }
        
        forn(i, sza) forn(j, sza + 1) a[i][j] = 0;
        
        forn(i, sz(comp)) forn(j, sz(comp))
        {
            int row = i * sz(comp) + j;
            a[row][row] = 1;
            
            if (i == j && comp[i] == ver) continue;
            
            a[row][sza] = 1;
            
            int v1 = comp[i], v2 = comp[j];         
            ld p = 1.0 / (sz(g[v1]) * sz(g[v2]));
            
            forn(ii, sz(g[v1])) forn(jj, sz(g[v2]))
            {
                int nv1 = g[v1][ii], nv2 = g[v2][jj];
                int nrow = newNum[nv1] * sz(comp) + newNum[nv2];
                a[row][nrow] -= p;
            }
        }
        
//        forn(i, sza) { forn(j, sza + 1) cerr << a[i][j] << ' '; cerr << endl; }
        
        gauss();
        
        forn(i, sza) a[i][i] += 1.0;
        
//        cerr << endl; forn(i, sza) { forn(j, sza + 1) cerr << a[i][j] << ' '; cerr << endl; }
        
        ford(i, sza)
        {
            x[i] = a[i][sza];
            fore(j, i + 1, sza - 1)
                x[i] -= x[j] * a[i][j];
        }
        
        int row = newNum[V1] * sz(comp) + newNum[V2];
        printf(" %.10lf", double(x[row]));
    }
    puts("");
}

int main()
{
    cerr << setprecision(5) << fixed;

    int testCount;
    cin >> testCount;
    
    forn(test, testCount)
    {
        assert(read());
        solve(test + 1);
    }
    
    return 0;
}
