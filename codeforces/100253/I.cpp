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

int main()
{
    int n, A, B, x, s[4][5555] = {0}, type;
    vector < pair<int,int> > a[4];
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) 
    {
        cin >> type >> x;
        a[type].push_back(make_pair(x, i));
    }
    
    for (int i = 1; i <= 3; i++) 
    {
        sort(a[i].begin(), a[i].end());
        for (int j = 0; j < int(a[i].size()); j++)
            s[i][j + 1] = s[i][j] + a[i][j].first;
    }
        
    pair <int,int> ans(0, 0);
    int ri, rj, rk;
    
    for (int i = 0; i <= int(a[1].size()) && i <= A; i++)
        for (int j = 0; j <= int(a[2].size()) && j <= B; j++)
        {
            int plugged = i + j, rest = A + B - plugged;
            int k = min(rest, int(a[3].size()));
            plugged += k;
            int power = s[1][i] + s[2][j] + s[3][k];
            pair <int,int> value = make_pair(plugged, -power);
            if (value > ans) ans = value, ri = i, rj = j, rk = k;
        }
        
    cout << ans.first << ' ' << -ans.second << endl;
    for (int i = 0; i < ri; i++) cout << a[1][i].second << ' ' << i + 1 << endl;
    for (int j = 0; j < rj; j++) cout << a[2][j].second << ' ' << A + j + 1 << endl;
    for (int k = 0; k < rk; k++)
    {
        cout << a[3][k].second << ' ';
        if (k + 1 <= A - ri) cout << ri + k + 1 << endl;
        else cout << A + (++rj) << endl;
    }
}
