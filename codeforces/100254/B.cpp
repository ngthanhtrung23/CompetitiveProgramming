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
const double oo = 1e18;

double probReceive[33][33], probSuccess[33][33], f[333][33];
int s, id[256], tr[333][33];
char c[33];

string solve(string word)
{
    int n = word.size();
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < s; j++)
            f[i][j] = -oo;
            
    for (int j = 0; j < s; j++)
        f[0][j] = probReceive[j][id[word[0]]];
    
    for (int i = 0; i + 1 < n; i++)
        for (int j = 0; j < s; j++)
            for (int k = 0; k < s; k++)
            {
                double F = f[i][j] + probReceive[k][id[word[i + 1]]] + probSuccess[j][k];
                if (F > f[i + 1][k])
                {
                    f[i + 1][k] = F;
                    tr[i + 1][k] = j;
                }
            }
            
    string res = "";
    int j;
    double best = -oo;
    for (int k = 0; k < s; k++) 
        if (best < f[n - 1][k])
            best = f[n - 1][k], j = k;
            
    for (int i = n - 1; i >= 0; i--)
    {
        res = c[j] + res;
        j = tr[i][j];
    }
    
    return res;
}

int main()
{
    //freopen("b.in", "r", stdin);
    int test, w;
    string word;
    
    cin >> test;
    while (test--)
    {
        cin >> s;
        for (int i = 0; i < s; i++) cin >> c[i], id[c[i]] = i;
        
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                cin >> probReceive[i][j], probReceive[i][j] = log(probReceive[i][j]);
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                cin >> probSuccess[i][j], probSuccess[i][j] = log(probSuccess[i][j]);
                
        cin >> w;
        while (w--)
        {
            cin >> word;
            cout << solve(word) << endl;
        }
    }
}
