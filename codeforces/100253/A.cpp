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
const int oo = 1 << 29;

vector <int> a[666], b[666], id[666], type, order[666]; 
int n, sz[666], f[666][666], F[666][666], numType, dp[666][666], tr[666][666];
int bestSum, useB[666], isType[666];
vector <int> trA[666][666];

void initialize(int n, vector <int> a, vector <int> b, int F[])
{
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            f[i][j] = -oo;
        
    f[0][0] = 0;
    
    for (int i = 0; i < n; i++)
        for (int j = i; j >= 0; j--)
            for (int k = i - j; k >= 0; k--)
            {
                f[j + 1][k] = max(f[j + 1][k], f[j][k] + a[i]);
                f[j][k + 1] = max(f[j][k + 1], f[j][k] + b[i]);
            }
            
    for (int k = 0; k <= n; k++)
    {
        F[k] = -oo;
        for (int j = 0; j <= n; j++) F[k] = max(F[k], f[j][k]);
    }
    F[0] = 0;
}

int calc(int maxB)
{
    for (int i = 0; i <= numType; i++)
        for (int sum = 0; sum <= n; sum++) 
            dp[i][sum] = -oo, tr[i][sum] = 0;
    
    dp[0][0] = 0;
    for (int i = 0, curSum = 0; i < numType; i++)
    {
        int t = type[i];
        
        for (int sum = 0; sum <= curSum; sum++)
        {
            if (dp[i][sum] > dp[i + 1][sum])
            {
                dp[i + 1][sum] = dp[i][sum];
                tr[i + 1][sum] = 0;
            }
            
            int lim = min(sz[t], maxB);
            
            for (int k = 1; k <= lim; k++)
                if (F[t][k] + dp[i][sum] > dp[i + 1][sum + k])
                {
                    dp[i + 1][sum + k] = dp[i][sum] + F[t][k];
                    tr[i + 1][sum + k] = k;
                }
        }
        
        curSum += sz[t];
    }
    
    int res = 0;
    for (int sum = maxB * 2 - 1; sum <= n; sum++) 
        if (dp[numType][sum] > res)
            res = dp[numType][sum], bestSum = sum;
    //cout << maxB << " = " << res << endl;
    return res;
}

void trace(int numType, int sum)
{
    //cout << numType << ' ' << sum << endl;
    if (!numType) return;
    int t = type[numType - 1];
    useB[t] = tr[numType][sum];
    trace(numType - 1, sum - useB[t]);
}

vector <int> traceA(int n, vector <int> a, vector <int> b, int useB, vector <int> id)
{
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= useB + 5; j++)
            trA[i][j] = vector <int> (n - useB + 5, 0);
    
    for (int i = 0; i <= useB; i++)
        for (int j = 0; j <= n - useB; j++)
            f[i][j] = -oo;
        
    f[0][0] = 0;
    
    for (int i = 0; i < n; i++)
        for (int j = useB; j >= 0; j--)
            for (int k = n - useB; k >= 0; k--)
            {
                if (f[j][k] + b[i] > f[j + 1][k])
                {
                    f[j + 1][k] = f[j][k] + b[i];
                    trA[i + 1][j + 1][k] = 1;
                }
                if (f[j][k] + a[i] > f[j][k + 1])
                {
                    f[j][k + 1] = f[j][k] + a[i];
                    trA[i + 1][j][k + 1] = 2;
                }
            }
    
    int best = -oo, rk;     
    for (int k = 0; k + useB <= n; k++)
        if (f[useB][k] > best)
        {
            best = f[useB][k];
            rk = k;
        }
        
    vector <int> res;
    for (int i = n, j = useB, k = rk; i; i--)
    {
        if (trA[i][j][k] == 1)
        {
            res.push_back(id[i - 1]);
            j--;
        }
        else 
            if (trA[i][j][k] == 2)
            {
                res.push_back(-id[i - 1]);
                k--;
            }
    }
    
    return res;
}

int main()
{
    //freopen("a.in", "r", stdin);
    int A, B, t;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> t >> A >> B;
        a[t].push_back(A);
        b[t].push_back(B);
        id[t].push_back(i);
    }
    
    int maxSz = 0;
    
    for (int i = 1; i <= n; i++)
        if (!a[i].empty())
        {
            sz[i] = a[i].size();
            maxSz = max(maxSz, sz[i]);
            initialize(sz[i], a[i], b[i], F[i]);
            type.push_back(i);
            numType++;
        }
        
    maxSz = min(maxSz, (n + 1) / 2);
        
    int ans = 0, rmaxB = 0;
    for (int maxB = 1; maxB <= maxSz; maxB++) 
    {
        int val = calc(maxB);
        if (val > ans) ans = val, rmaxB = maxB;
    }
    
    if (!ans) puts("0 0");
    else
    {
        cout << ans << ' ';
        calc(rmaxB);
        trace(numType, bestSum);
        
        //cout << "bestSum = " << bestSum << endl;
        
        int cur = 1, total = 0;
        for (int i = 1; i <= n; i++)
            if (useB[i])
            {
                //cout << i << " use " << useB[i] << endl;
                vector <int> programs = traceA(sz[i], a[i], b[i], useB[i], id[i]);
                total += programs.size();
                
                vector <int> isA, isB;
                for (int j = 0; j < int(programs.size()); j++)
                    if (programs[j] < 0) isA.push_back(-programs[j]);
                    else isB.push_back(programs[j]);
                    
                order[cur].push_back(isB[0]);
                for (int j = 0; j < int(isA.size()); j++) order[cur].push_back(isA[j]);
                isType[cur] = i;
                
                cur += 2;
                if (cur > bestSum) cur = 2;
                
                for (int j = 1; j < int(isB.size()); j++)
                {
                    order[cur].push_back(isB[j]);
                    isType[cur] = i;
                    cur += 2;
                    if (cur > bestSum) cur = 2;
                }
            }
            
        for (int i = 1; i < bestSum; i++)
            if (isType[i] == isType[i + 1])
            {
                rotate(order + 1, order + i + 1, order + bestSum + 1);
                break;
            }
            
        cout << total << endl;
        for (int i = 1; i <= bestSum; i++)
            for (int j = 0; j < int(order[i].size()); j++)
                cout << order[i][j] << ' ';
    }
}
