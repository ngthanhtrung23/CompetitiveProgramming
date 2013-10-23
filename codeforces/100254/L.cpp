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
const int ROLL_DOWN[] = {4, 0, 2, 3, 5, 1};
const int ROLL_LEFT[] = {2, 1, 5, 0, 4, 3};
const int ROLL_RIGHT[] = {3, 1, 0, 5, 4, 2};

void roll(int dice[], const int ROLL[])
{
    int tmp[6];
    for (int i = 0; i < 6; i++) tmp[i] = dice[i];
    for (int i = 0; i < 6; i++) dice[i] = tmp[ROLL[i]];
}

int main()
{
    int dice[] = {1, 2, 3, 4, 5, 6}, m, n;
    long long ans = 0;
    cin >> m >> n;
    n--;
    
    for (int i = 1; i <= m; i++)
    {
        int each = 0;
        for (int j = 0; j < 4; j++) 
        {
            if (i % 2) roll(dice, ROLL_RIGHT);
            else roll(dice, ROLL_LEFT);
            each += dice[0];
        }
        
        ans += 1LL * n / 4 * each;
        ans += dice[0];
        
        for (int j = 0; j < n % 4; j++)
        {
            if (i % 2) roll(dice, ROLL_RIGHT);
            else roll(dice, ROLL_LEFT);
            ans += dice[0];
        }
            
        roll(dice, ROLL_DOWN);
    }
    
    cout << ans << endl;
}
