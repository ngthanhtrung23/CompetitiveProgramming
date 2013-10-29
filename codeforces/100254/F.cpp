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

int a[10100], minBet, maxBet, f[10100], sumHigh[10100], sumLow[10100], pos[10010][23][3], C;
int hh[10010][23][3];
char s[10100];

int conv(char ch)
{
    if (ch >= '2' && ch <= '9') return ch - '0';
    if (ch == 'A') return 1;
    return 10;
}

int getLow(int l, int r)
{
    return sumLow[r] - sumLow[l - 1];
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        cin >> C >> minBet >> maxBet;
        for (int i = 0; i < (C + 59) / 60; i++) 
        {
            scanf("%s", s);
            int len = strlen(s);
            for (int j = 0; j < len; j++) a[j + i * 60 + 1] = conv(s[j]);
        }
        
        for (int i = 1; i <= C; i++) 
        {
            sumHigh[i] = sumHigh[i - 1] + a[i] + (a[i] == 1) * 10;
            sumLow[i] = sumLow[i - 1] + a[i];
        }
        
        for (int i = C + 1; i; i--)
            for (int h = 2; h <= 22; h++)
                for (int o = 0; o < 3; o++)
                {
                    int high = h, one = o;
                    pos[i][h][o] = i;
                    while (high < 17 && pos[i][h][o] <= C)
                    {
                        high += a[pos[i][h][o]] + (a[pos[i][h][o]] == 1) * 10;
                        one += (a[pos[i][h][o]] == 1);
                        pos[i][h][o]++;
                        while (high > 21 && one) high -= 10, one--;
                    }
                    hh[i][h][o] = high;
                }
            
        for (int i = 0; i <= C; i++) f[i] = -oo;
        for (int i = C + 1; i >= C - 2 && i >= 0; i--) f[i] = 0;
        
        for (int i = C - 3; i; i--)
        {
            int lowMe = a[i] + a[i + 2], highMe = lowMe + (a[i] == 1) * 10 + (a[i + 2] == 1) * 10;
            int oneMe = (a[i] == 1) + (a[i + 2] == 1);
            int lowU = a[i + 1] + a[i + 3], highU = lowU + (a[i + 1] == 1) * 10 + (a[i + 3] == 1) * 10;
            int oneU = (a[i + 1] == 1) + (a[i + 3] == 1);
            
            while (highMe > 21 && oneMe) highMe -= 10, oneMe--;
            while (highU > 21 && oneU) highU -= 10, oneU--;
            
            // stand
            int ii = pos[i + 4][highU][oneU], low = lowU + getLow(i + 4, ii - 1), high = hh[i + 4][highU][oneU];
            if (high < 17) f[i] = f[ii];
            else if (low > 21 || highMe > high) f[i] = f[ii] + maxBet;
            else if (highMe == high) f[i] = f[ii];
            else f[i] = f[ii] - minBet;
            
            // draw
            for (int j = i + 4; j <= C && lowMe < 22; j++)
            {
                lowMe += a[j];
                highMe += a[j] + (a[j] == 1) * 10;
                oneMe += (a[j] == 1);
                while (highMe > 21 && oneMe) highMe -= 10, oneMe++;
                int ii = pos[j + 1][highU][oneU], low = lowU + getLow(j + 1, ii - 1), high = hh[j + 1][highU][oneU];
                
                if (lowMe > 21) f[i] = max(f[i], f[j + 1] - minBet);
                else if (high < 17) f[i] = max(f[i], f[ii]);
                else if (low > 21 || highMe > high) f[i] = max(f[i], f[ii] + maxBet);
                else if (highMe == high) f[i] = max(f[i], f[ii]);
                else f[i] = max(f[i], f[ii] - minBet);
            }
            
            if (lowMe < 22) f[i] = max(f[i], 0);
        }
        
        cout << f[1] << endl;
    }
}
