#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

struct triple
{
    int i, j, k;
    
    triple() {}
    triple(int _i, int _j, int _k): i(_i), j(_j), k(_k) {}
} tr[10100][33][33];

int isWindow[10100], n, s[33], t[33], id[33], f[10100][33][33];
vector <int> problems, timeSolve;

void trace(int i, int j, int k)
{
    if (!i || !j) return;
    triple t = tr[i][j][k];
    if (t.i < i && t.j < j) 
    {
        problems.push_back(j);
        if (t.k >= k)
        {
            int need = t.k - k + 1;
            for (int u = i; u > t.i; u--)
                if (isWindow[u] > isWindow[u - 1])
                {
                    timeSolve.push_back(u - 1);
                    if (!--need) break;
                }
        }
    }
    else
        if (t.j == j && t.k > k) timeSolve.push_back(i - 1);
    
    trace(t.i, t.j, t.k);
}

int main()
{
    //freopen("j.in", "r", stdin);
    int m, l, r;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i] >> t[i], id[i] = i;
    for (int i = 1; i <= m; i++)
    {
        cin >> l >> r;
        for (int i = l + 1; i <= r; i++) isWindow[i] = 1;
    }
    
    for (int i = 1; i <= 10000; i++) isWindow[i] += isWindow[i - 1];
    
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (t[i] > t[j] || (t[i] == t[j] && s[i] < s[j]))
                swap(s[i], s[j]), swap(t[i], t[j]), swap(id[i], id[j]);
                
    for (int i = 1; i <= 10000; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 0; k <= j; k++)
            {
                // do nothing
                f[i][j][k] = f[i - 1][j][k];
                tr[i][j][k] = triple(i - 1, j, k);
                
                if (f[i][j - 1][k] > f[i][j][k])
                {
                    f[i][j][k] = f[i][j - 1][k];
                    tr[i][j][k] = triple(i, j - 1, k);
                }
                
                // submit 1
                if (isWindow[i] > isWindow[i - 1] && f[i - 1][j][k + 1] > f[i][j][k]) 
                {
                    f[i][j][k] = f[i - 1][j][k + 1];
                    tr[i][j][k] = triple(i - 1, j, k + 1);
                }
                
                if (!k) continue;
                
                // solve a new problem + submit kk 
                for (int kk = 0; kk + k <= j; kk++)
                    if (i >= kk + t[j])
                    {
                        int ii = i - kk - t[j];
                        int available = isWindow[i] - isWindow[ii];
                        if (available < kk) continue;
                        if (f[ii][j - 1][k + kk - 1] + s[j] > f[i][j][k])
                        {
                            f[i][j][k] = f[ii][j - 1][k + kk - 1] + s[j];
                            tr[i][j][k] = triple(ii, j - 1, k + kk - 1);
                        }
                    }
                    
                //if (f[i][j][k]) cout << i << ' ' << j << ' ' << k << " = " << f[i][j][k] << endl;
            }
            
    int ans = -1, ri, rj;
    for (int i = 0; i <= 10000; i++)
        for (int j = 0; j <= n; j++)
            if (f[i][j][0] > ans)
            {
                ans = f[i][j][0];
                ri = i; rj = j;
            }
            
    cout << ans << ' ';
    trace(ri, rj, 0);
    int P = problems.size();
    cout << P << endl;
    for (int i = P - 1; i >= 0; i--) cout << id[problems[i]] << ' ' << timeSolve[i] << endl;
}
