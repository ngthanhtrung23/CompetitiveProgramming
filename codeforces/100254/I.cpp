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

int n, a[444][444], s1[444][444], s2[444][444];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", a[i] + j);
            
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            s1[i][j] = s1[i - 1][j - 1] + a[i][j];
            s2[i][j] = s2[i - 1][j + 1] + a[i][j];
        }
        
    int ans = - (1 << 29);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= i && k <= j; k++)
                ans = max(ans, s1[i][j] - s1[i - k][j - k] - s2[i][j - k + 1] + s2[i - k][j + 1]);
                
    cout << ans << endl;
}
