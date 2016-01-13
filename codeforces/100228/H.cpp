#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GElong doubleCHAR(INP) { \
   if(!*inp && !REACHEOF) { \
      memset(BUF,0,sizeof BUF);\
      int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
      if (inpzzz != BUFSIZE) REACHEOF = true;\
      inp=BUF; \
   } \
   INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
   AM=0;\
   GElong doubleCHAR(INP); while(!DIG(INP) && INP!='-') GElong doubleCHAR(INP);\
   if (INP=='-') {AM=1;GElong doubleCHAR(INP);} \
   j=INP-'0'; GElong doubleCHAR(INP); \
   while(DIG(INP)){j=10*j+(INP-'0');GElong doubleCHAR(INP);} \
   if (AM) j=-j;\
}
//End of buffer reading

const long double EPS = 1e-6;

int cmp(long double x, long double y) {
   return (x < y+EPS) ? (x > y-EPS) ? 0 : -1 : 1;
}

struct Point {
   long double x, y;
   Point(long double x = 0, long double y = 0) : x(x), y(y) {}
   Point operator + (Point a) { return Point(x+a.x, y+a.y); }
   Point operator - (Point a) { return Point(x-a.x, y-a.y); }
   Point operator * (long double k) { return Point(x*k, y*k); }
   Point operator / (long double k) { return Point(x/k, y/k); }

   long double operator * (Point a) { return x*a.x + y*a.y; } // dot product
   long double operator % (Point a) { return x*a.y - y*a.x; } // cross product
   int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

   #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
   Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
   #undef Comp

   Point conj() { return Point(x, -y); }
   long double norm() { return x*x + y*y; }

   void read() { cin >> x >> y; }
};

int ccw(Point a, Point b, Point c) {
   return cmp((b-a)%(c-a),0); 
}

struct Line {
   Point A, B;
   long double a, b, c;
   Line(Point A, Point B) : A(A), B(B) {
     a = B.y - A.y;
     b = A.x - B.x;
     c = - (a*A.x + b*A.y);
   }
   long double f(Point A) {
     return a*A.x + b*A.y + c;
   }
};

typedef vector<Point> Polygon;

double area(Polygon &p) {
   double s = 0.0;
   FOR(i,1,(int)p.size()-1) s+= (p[i]-p[0])%(p[(i+1)%p.size()]-p[0]);
   return fabs(s) / 2.0;
}

Point crossPoint(Line l, Line m) {
   double A = (l.B - l.A) % (m.B - m.A);
   double B = (l.B - l.A) % (l.B - m.A);
   if (abs(A) < EPS && abs(B) < EPS) return m.A;
   return m.A + (m.B - m.A) * (B / A);
}

Polygon convex_cut(Polygon P, Line l) {
   Polygon Q;
   REP(i,P.size()) {
      Point A = P[i], B = (i == P.size()-1) ? P[0] : P[i+1];
      if (ccw(l.A, l.B, A) != -1) Q.push_back(A);
      if (ccw(l.A, l.B, A)*ccw(l.A, l.B, B) < 0)
         Q.push_back(crossPoint(Line(A, B), l));
   }
   return Q;
}

Polygon P;

bool read() {
   bool ok = false;
   REP(i,4) {
      cin >> P[i].x >> P[i].y;
      if (P[i].x || P[i].y) ok = true;
   }
   return ok;
}

Point a[111];

int main() {
   // freopen("input.txt", "r", stdin);
   ios :: sync_with_stdio(false);

   P.resize(4);

   cout << (fixed) << setprecision(3);

   int test = 0;
   while (read()) {
      int n = 0;
      REP(i,4) a[n++] = P[i];
      REP(i,4) {
         int j = (i + 1) % 4;
         a[n++] = (P[i] + P[j]) * 0.5;
      }

      long double A = -1, B = -1, res = 1e50;

      long double sp = area(P);
      REP(i,n) FOR(j,i+1,n-1) {
         Line l(a[i], a[j]);
         Polygon Q = convex_cut(P, l);

         long double a = area(Q), b = sp - a;
         if (fabs(a - b) < res) {
            res = fabs(a - b);
            A = a;
            B = b;
         }
      }
      cout << "Cake " << ++test << ": " << min(A, B) << ' ' << max(A, B) << endl;
   }
   return 0;
}