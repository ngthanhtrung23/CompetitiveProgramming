#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-1, -1, 1, 1};
const int dy[] = {-1, 1, 1, -1};

string a[10];
int ans;

int inside(int x, int y)
{
    return x >= 0 && x < 10 && y >= 0 && y < 10;
}

void visit(int x, int y, int step)
{
    ans = max(ans, step);
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];
        if (inside(xx, yy) && a[xx][yy] == 'B')
        {
            int xxx = xx + dx[i], yyy = yy + dy[i];
            if (inside(xxx, yyy) && a[xxx][yyy] == '#') 
            {
                a[xx][yy] = '#';
                a[xxx][yyy] = 'W';
                a[x][y] = '#';
                visit(xxx, yyy, step + 1);
                a[xx][yy] = 'B';
                a[xxx][yyy] = '#';
                a[x][y] = 'W';
            }
        }
    }
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        for (int i = 0; i < 10; i++) cin >> a[i];
        ans = 0;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (a[i][j] == 'W')
                    visit(i, j, 0);
        cout << ans << endl;
    }
}
