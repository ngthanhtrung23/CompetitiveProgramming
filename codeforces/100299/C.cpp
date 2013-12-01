#include <bits/stdc++.h>
using namespace std;

long long a[100100], g[100100][30];
int n, lg2[100100];

long long gcd(long long x, long long y)
{
    return x && y ? gcd(y, x % y) : x + y;
}

long long calcGCD(int l, int r)
{
    int lg = lg2[r - l + 1];
    return gcd(g[r][lg], g[l + (1 << lg) - 1][lg]);
}

int main()
{
    ios::sync_with_stdio(0);
    
    for (int i = 1; i <= 100000; i++)
    {
        int x = i;
        while (x) x /= 2, lg2[i]++;
        lg2[i]--;
    }
    
    int test;
    cin >> test;
    while (test--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i], g[i][0] = a[i];
        
        for (int j = 1; 1 << j <= n; j++)
            for (int i = 1 << j; i <= n; i++)
                g[i][j] = gcd(g[i][j - 1], g[i - (1 << (j - 1))][j - 1]);
                
        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int bound = i;

            while (bound)
            {
                int low = 1, high = bound - 1, res = bound;
                long long curGCD = calcGCD(bound, i);
                
                while (low <= high)
                {
                    int mid = (low + high) / 2;
                    long long u = calcGCD(mid, i);
                    if (u == curGCD) res = mid, high = mid - 1;
                    else low = mid + 1;
                }
                
                bound = res;
                ans = max(ans, curGCD * (i - bound + 1));
                bound--;
            }
        }
        
        cout << ans << endl;
    }
}
