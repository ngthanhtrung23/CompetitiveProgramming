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
    int n, k;
    deque <int> id[10];
    string s;
    cin >> n >> k >> s;
    k = n - k;
    
    for (int i = 0; i <= n - k; i++) id[s[i] - '0'].push_back(i);
    
    int lastId = -1;
    while (k--)
    {
        for (int digit = 9; digit >= 0; digit--)
            while (!id[digit].empty() && id[digit].front() <= lastId)
                id[digit].pop_front();
                
        for (int digit = 9; digit >= 0; digit--)
            if (!id[digit].empty())
            {
                cout << digit;
                lastId = id[digit].front();
                id[digit].pop_front();
                break;
            }
            
        if (k) id[s[n - k] - '0'].push_back(n - k);
    }
}
