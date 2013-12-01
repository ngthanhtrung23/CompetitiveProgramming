#include <bits/stdc++.h>
using namespace std;

int a[33][33], color[33], len[33], ans, next[33];
vector <int> path;

void visit(int x)
{
    path.push_back(x);
    color[x] = 1;
    len[x] = 1;
    
    for (int y = 0; y < 26; y++)
        if (a[x][y])
        {
            if (color[y] == 1) 
            {
                while (path[0] != y) path.erase(path.begin());
                ans = 1;
                return;
            }
            
            if (!color[y]) visit(y);
            if (ans) return;
            
            if (len[y] + 1 > len[x]) len[x] = len[y] + 1, next[x] = y;
        }
        
    color[x] = 2;
    path.pop_back();
}

int main()
{
    //freopen("k.in", "r", stdin);
    int test, pairs;
    cin >> test;
    while (test--)
    {
        cin >> pairs;
        memset(a, -1, sizeof(a));
        memset(color, 0, sizeof(color));
        path.clear();
        ans = 0;
        
        while (pairs--)
        {
            string s;
            cin >> s;
            a[s[0] - 'a'][s[1] - 'a'] = 0;
        }
        
        int best = 0, id = -1;
        visit(26);
        for (int i = 0; i < 26; i++)
            if (len[i] > best) best = len[i], id = i;
            
        if (ans) // cycle
        {
            int P = path.size();
            for (int i = P; i < 39; i++) path.push_back(path[i - P]);
        }
        else // longest path
        {
            path.clear();
            path.push_back(id);
            while (len[id] > 1)
            {
                id = next[id];
                path.push_back(id);
            }
        }
        
        int P = path.size();
        if (P % 2 == 0) P--;
        
        int n = (P + 1) / 2;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cout << char(path[i + j] + 'a') << (j == n - 1 ? "\n" : "");
    }
}
