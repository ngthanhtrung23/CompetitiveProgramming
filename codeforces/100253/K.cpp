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
const int oo = 27081993;

int n, a[300300], st[300300], pos[300300], l[300300], r[300300], isForward[300300]; 
int f[300300];

int main()
{
    //freopen("k.in", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i]--;

    set < pair<int,int> > s;
    set < pair<int,int> >::iterator it;
    
    int maxL = 0;
    for (int i = 1; i <= n; i++)
    {
        s.insert(make_pair(i + a[i], i));
        while (!s.empty())
        {
            it = s.begin();
            if (it -> first >= i) break;
            maxL = max(maxL, it -> second);
            s.erase(it);
        }
        l[i] = maxL + 1;
    }
    
    s.clear();
    int minR = n + 1;
    for (int i = n; i; i--)
    {
        s.insert(make_pair(i - a[i], i));
        while (!s.empty())
        {
            it = s.end();
            it--;
            if (it -> first <= i) break;
            minR = min(minR, it -> second);
            s.erase(it);
        }
        r[i] = minR - 1;
    }
    
    //for (int i = 1; i <= n; i++) cout << l[i] << ' '; puts("");
    //for (int i = 1; i <= n; i++) cout << r[i] << ' '; puts("");
    
    s.clear();
    for (int i = 1; i <= n; i++)
    {
        s.insert(make_pair(i, r[i]));
        while (!s.empty())
        {
            it = s.begin();
            if (it -> second < i) s.erase(it);
            else
            {
                if (it -> first < l[i])
                {
                    l[i] = it -> first;
                    isForward[i] = 1;
                }
                break;
            }
        }
    }
            
    //for (int i = 1; i <= n; i++) cout << l[i] << ' '; puts("");
    
    for (int i = 1; i <= n; i++) f[i] = f[l[i] - 1] + 1;
    
    cout << f[n] << endl;
    while (n)
    {
        if (isForward[n]) cout << l[n] << ' ' << n << endl;
        else cout << n << ' ' << l[n] << endl;
        n = l[n] - 1;
    }   
}
