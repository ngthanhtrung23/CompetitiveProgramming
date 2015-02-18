#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <string>
#include <queue>
#include <fstream>

#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define FR(i,a) for(int i = 0; i < (a); i++)
#define DR(i,a) for(int i = (a)-1; i >=0; i--)
#define DOWN(i,a,b) for(int i = (a); i >= (b); i--)
#define FORD(i,a,b) for(int i = (a), _b = (b); i >= _b; i--)
#define REPD(i,n) for(int i = (n) - 1; i >= 0; i--)
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define RESET(c,x) memset(c,x,sizeof(c))
#define SIZE(c) (c).size()
#define ALL(c) (c).begin(), (c).end()

#define REP(i,a) for(int i = 0; i < (a); i++)

#define sqr(x) ((x)*(x))
#define oo 1000000009

using namespace std;
/*************************TEMPLATE**********************************/
long long convertToNum(string s)
{
    long long val = 0; FR(i,s.size()) val = val * 10 + s[i] - '0';
    return val;
}
string convertToString(long long a) {
    string res = ""; if (!a) return "0";
    while (a) { res = (char)(a % 10 + 48) + res;  a /= 10; }
    return res;
}
long long GCD(long long x,long long y)  {
    if (!x) return y; if (!y) return x;
    if (x == y) return x; if (x < y) return GCD(x,y%x); else return GCD(x%y,y);
}
long long POW(long long x,long long y,long long Base){
    if (!y) return 1; long long u = POW(x,y/2,Base);
    u = (u * u) % Base;
    if (y & 1) return (u * x) % Base; else return u;
}

//newstate = (newstate-1) & oldstate
/**************************CODE HERE*****************************/
struct Point {
    int x,y;
    Point(){x=y=0;}
    Point(int x, int y):x(x),y(y){}
    Point operator + (Point q){ return Point(x+q.x,y+q.y);}
    Point operator - (Point q){ return Point(x-q.x,y-q.y);}
    int operator *(Point q) { return x*q.x+y*q.y;}
    int getLen() { return x*x+y*y;}
};
Point p[10];
vector<int> list;
int main() {
//    freopen("test.in","r",stdin);
//    freopen("test.out","w",stdout);
    FR(i,8) cin >> p[i].x >> p[i].y;
    
    FR(state,(1<<8)) {
        int cnt = 0;
        FR(i,8)
        if (state & (1<<i)) cnt++;
        
        if (cnt != 4) continue;
        list.clear();
        
        FR(i,8)
        if (state & (1<<i)) list.push_back(i);
        
        bool correct = false;
        
        do {
            Point A = p[list[0]];
            Point B = p[list[1]];
            Point C = p[list[2]];
            Point D = p[list[3]];
            if ((B-A)*(D-A) == 0 && (A-B)*(C-B) == 0 && (B-C)*(D-C) == 0 && (C-D)*(A-D) == 0) {
                if ((B-A).getLen() == (C-B).getLen() && (C-B).getLen() == (D-C).getLen() && (D-C).getLen() == (D-A).getLen()) {
                    correct = true; 
                    break;
                }
            }
        } while (next_permutation(list.begin(),list.end()));
        if (!correct) continue;
        
        list.clear();
        FR(i,8)
        if (!(state & (1<<i))) list.push_back(i);
        
        correct = false;
        
        do {
            Point A = p[list[0]];
            Point B = p[list[1]];
            Point C = p[list[2]];
            Point D = p[list[3]];
            if ((B-A)*(D-A) == 0 && (A-B)*(C-B) == 0 && (B-C)*(D-C) == 0 && (C-D)*(A-D) == 0) {
                if ((B-A).getLen() == (D-C).getLen() && (C-B).getLen() == (A-D).getLen()) {
                    correct = true; 
                    break;
                }
            }
        } while (next_permutation(list.begin(),list.end()));
        if (!correct) continue;
        cout << "YES" << endl;
        FR(i,8)
        if (state & (1<<i)) cout << (i+1) << " ";
        cout << endl;
        FR(i,8)
        if (!(state & (1 << i))) cout << (i+1) << " ";
        cout << endl;
        return 0;
    }
    cout << "NO" << endl;
    
//    system("pause");
    return 0;
}