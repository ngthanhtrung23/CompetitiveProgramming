
//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
const int MN = 1000111;

int a[MN], b[MN];
char s1[1011], s2[1011];

bool win(char a, char b) {
    if (a == 'R' && b == 'S') return true;
    if (a == 'S' && b == 'P') return true;
    if (a == 'P' && b == 'R') return true;
    return false;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d\n", &n);
    gets(s1); gets(s2);
    int n1 = strlen(s1), n2 = strlen(s2);
    int i = 0, j = 0;
    FOR(turn,1,n1*n2) {
        if (win(s1[i], s2[j])) a[turn] = a[turn-1] + 1;
        else a[turn] = a[turn-1];
        if (win(s2[j], s1[i])) b[turn] = b[turn-1] + 1;
        else b[turn] = b[turn-1];
        i++; j++;
        if (i >= n1) i = 0;
        if (j >= n2) j = 0;
    }
    int sl = n / (n1*n2);
    int A = a[n1*n2] * sl, B = b[n1*n2] * sl;
    n -= sl * (n1*n2);
    A += a[n]; B += b[n];
    swap(A, B);
    printf("%d %d\n", A, B);
    return 0;
}
