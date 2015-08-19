#include <bits/stdc++.h>
using namespace std;

int a[9][9], b[9][9], flagRow[10][10], flagCol[10][10], flagSquare[3][3][10], found;
vector < vector <int> > pers;

void rotate()
{
  int c[9][9];
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      c[i][j] = a[i][j];
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      a[i][j] = c[j][8 - i];
}

void mark(int x, int y, int v, int z)
{
  flagRow[x][v] = z;
  flagCol[y][v] = z;
  flagSquare[x / 3][y / 3][v] = z;
}

void solve(int iter)
{
  int minCnt = 10, rx = 0, ry = 0;

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
    {
      if (b[i][j]) continue;
      int d[10] = {0};
      for (int ii = 0; ii < 9; ii++) d[b[ii][j]] = 1;
      for (int jj = 0; jj < 9; jj++) d[b[i][jj]] = 1;
      for (int ii = 0; ii < 3; ii++)
        for (int jj = 0; jj < 3; jj++)
          d[b[i / 3 * 3 + ii][j / 3 * 3 + jj]] = 1;

      int cnt = 0;
      for (int v = 1; v < 10; v++)
        if (!d[v]) cnt++;

      if (cnt < minCnt)
      {
        minCnt = cnt;
        rx = i;
        ry = j;
      }
    }

  if (minCnt == 10)
  {
    found = 1;
    return;
  }

  for (int v = 1; v < 10; v++)
    if (!flagRow[rx][v] && !flagCol[ry][v] && !flagSquare[rx / 3][ry / 3][v])
    {
      mark(rx, ry, v, 1);
      b[rx][ry] = v;
      solve(iter + 1);
      if (found) return;
      b[rx][ry] = 0;
      mark(rx, ry, v, 0);
    }
}

void my_sort(vector<int>& x) {
    auto y = x;
    if (y[0] < y[1] && y[0] < y[2]) {
        x[0] = y[0];
        
        x[1] = y[1];
        x[2] = y[2];

        if (x[1] > x[2]) swap(x[1], x[2]);
    }
    else if (y[1] < y[2]) {
        x[0] = y[1];

        x[1] = y[0];
        x[2] = y[2];
        if (x[1] > x[2]) swap(x[1], x[2]);
    }
    else {
        x[0] = y[2];
        x[1] = y[0];
        x[2] = y[1];
        if (x[1] > x[2]) swap(x[1], x[2]);
    }
}
void my_sort(vector<vector<int> >& x) {
    auto y = x;
    if (y[0] < y[1] && y[0] < y[2]) {
        x[0] = y[0];
        
        x[1] = y[1];
        x[2] = y[2];

        if (x[1] > x[2]) swap(x[1], x[2]);
    }
    else if (y[1] < y[2]) {
        x[0] = y[1];

        x[1] = y[0];
        x[2] = y[2];
        if (x[1] > x[2]) swap(x[1], x[2]);
    }
    else {
        x[0] = y[2];
        x[1] = y[0];
        x[2] = y[1];
        if (x[1] > x[2]) swap(x[1], x[2]);
    }
}

int isGood(vector <int> pCol, int firstRow)
{
  int d[10] = {0}, c[10][10];
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      c[i][j] = b[i][pCol[j]];

  for (int col = 0; col < 9; col++)
  {
    int oldVal = a[0][col], newVal = c[firstRow][col];
    d[oldVal] = newVal;
  }

  vector < vector <int> > sa(3), sb(3);
  for (int i = 0; i < 3; i++)
  {
    vector <int> ta(9), tb(9);
    for (int row = i * 3; row < i * 3 + 3; row++)
    {
      int ua = 0, ub = 0;
      for (int col = 0; col < 9; col++)
      {
        ua = ua * 10 + d[a[row][col]];
        ub = ub * 10 + c[row][col];
      }
      ta[row] = ua;
      tb[row] = ub;
    }
    sort(ta.begin(), ta.end());
    sort(tb.begin(), tb.end());
//    my_sort(ta);
//    my_sort(tb);
    sa[i] = ta;
    sb[i] = tb;
  }
  sort(sa.begin(), sa.end());
  sort(sb.begin(), sb.end());
//  my_sort(sa);
//  my_sort(sb);
  
  return sa == sb;
}

int main()
{
  ios::sync_with_stdio(0);

  vector <int> per;
  for (int i = 0; i < 9; i++) per.push_back(i);
  do
  {
    int pos[9];
    for (int i = 0; i < 9; i++) pos[per[i]] = i / 3;
    int ok = 1;
    for (int i = 0; i < 9; i += 3)
    {
      for (int j = 1; j < 3; j++)
        if (pos[i + j] != pos[i + j - 1])
          ok = 0;
    }  
    if (ok) pers.push_back(per);
  } while (next_permutation(per.begin(), per.end()));

  int test;
  cin >> test;
  while (test--)
  {
    string s;
    memset(flagRow, 0, sizeof flagRow);
    memset(flagCol, 0, sizeof flagCol);
    memset(flagSquare, 0, sizeof flagSquare);
    for (int i = 0; i < 9; i++) 
    {
      cin >> s;
      for (int j = 0; j < 9; j++) a[i][j] = s[j] - '0';
    }
    for (int i = 0; i < 9; i++) 
    {
      cin >> s;
      for (int j = 0; j < 9; j++) 
      {
        b[i][j] = s[j] - '0';
        if (b[i][j]) mark(i, j, b[i][j], 1);
      }
    }

    found = 0;
    solve(0);
    assert(found);

    int ans = 0;
    for (int turn = 0; turn < 4 && !ans; turn++)
    {
      for (auto pRow : pers)
        for (int firstCol = 0; firstCol < 9; firstCol++)
          if (isGood(pRow, firstCol))
            ans = 1;

      rotate();
    }

//    if (test == 0) cout << "Yes\nNo\n";
    cout << (ans ? "Yes" : "No") << endl;
  }  
}