#include<bits/stdc++.h>
#define MAX   1111
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
#define isNA(p) ((p).x==INF)
using namespace std;
template<class X,class Y>
    void minimize(X &x,const Y &y) {
        if (x>y) x=y;
    }
template<class X,class Y>
    void maximize(X &x,const Y &y) {
        if (x<y) x=y;
    }
struct Point {
    int x,y;
    Point() {
        x=y=0;
    }
    Point(int _x,int _y) {
        x=_x;y=_y;
    }
    Point operator - (const Point &a) const {
        return (Point(x-a.x,y-a.y));
    }
    int getArea(void) const {
        if (x>0 && y==0) return (0);
        if (x>0 && y>0) return (1);
        if (x==0 && y>0) return (2);
        if (x<0 && y>0) return (3);
        if (x<0 && y==0) return (4);
        if (x<0 && y<0) return (5);
        if (x==0 && y<0) return (6);
        if (x>0 && y<0) return (7);
        assert(false);
    }
    long long operator ^ (const Point &a) const {
        return (1LL*x*a.y-1LL*a.x*y);
    }
};
const string yes="Possible";
const string no="Impossible";
const int INF=(int)1e9+7;
const Point NA(INF,INF);
Point points[MAX];
int n;
bool CompAngle(const Point &a,const Point &b) {
    int xa=a.getArea();
    int xb=b.getArea();
    if (xa!=xb) return (xa<xb);
    return ((a^b)>0);
}
pair<Point,Point> getCurve(const Point &center,vector<Point> points) {
    FORE(it,points) *it=*it-center;
    sort(ALL(points),CompAngle);
    int n=points.size();
    if (n==1) return (make_pair(points[0],points[0]));
    int j=0;
    REP(i,n) {
        while ((j+1)%n!=i && (points[i]^points[(j+1)%n])>0) j=(j+1)%n;
        if ((j+1)%n==i) return (make_pair(points[i],points[j]));
        if (i==j) j=(j+1)%n;
    }
    return (make_pair(NA,NA));
}
bool intersect(const pair<Point,Point> &a,const pair<Point,Point> &b) {
    if ((a.fi^b.fi)>0 && (b.fi^a.se)>0) return (true);
    if ((a.fi^b.se)>0 && (b.se^a.se)>0) return (true);
    if ((b.fi^a.fi)>0 && (a.fi^b.se)>0) return (true);
    if ((b.fi^a.se)>0 && (a.se^b.se)>0) return (true);
    return (false);
}
void init(void) {
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&points[i].x,&points[i].y);
}
bool ok(int x) {
    pair<Point,Point> leftCurve=getCurve(points[x],vector<Point>(points+1,points+x));
    pair<Point,Point> rightCurve=getCurve(points[x],vector<Point>(points+x+1,points+n+1));
    if (isNA(leftCurve.fi) || isNA(rightCurve.se)) return (false);
    return (!intersect(leftCurve,rightCurve));
}
void process(void) {
    FOR(i,2,n-1) if (!ok(i)) {
        cout<<no<<endl;
        return;
    }
    cout<<yes<<endl;
}
int main(void) {
    init();
    process();
    return 0;
}
