#include <bits/stdc++.h>
#define MP make_pair
#define PB push_back
#define st first
#define nd second
#define rd third
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define RE(i, n) FOR(i, 1, n)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define REP(i, n) for(int i = 0;i <(n); ++i)
#define VAR(v, i) __typeof(i) v=(i)
#define FORE(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
using namespace std;
template<typename TH> void _dbg(const char* sdbg, TH h) { cerr<<sdbg<<"="<<h<<"\n"; }
template<typename TH, typename... TA> void _dbg(const char* sdbg, TH h, TA... t) {
  while(*sdbg != ',')cerr<<*sdbg++; cerr<<"="<<h<<","; _dbg(sdbg+1, t...);
}
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#define debugv(x) {{cerr <<#x <<" = "; FORE(itt, (x)) cerr <<*itt <<", "; cerr <<"\n"; }}
#else
#define debug(...) (__VA_ARGS__)
#define debugv(x)
#define cerr if(0)cout
#endif
#define make(type, x) type x; cin>>x;
#define make2(type, x, y) type x, y; cin>>x>>y;
#define make3(type, x, y, z) type x, y, z; cin>>x>>y>>z;
#define make4(type, x, y, z, t) type x, y, z, t; cin>>x>>y>>z>>t;
#define next ____next
#define prev ____prev
#define left ____left
#define hash ____hash
#define sqrt ____sqrt
typedef long long ll;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<ll> VLL;
typedef vector<pair<int, int> > VPII;
typedef vector<pair<ll, ll> > VPLL;

template<class C> void mini(C&a4, C b4){a4=min(a4, b4); }
template<class C> void maxi(C&a4, C b4){a4=max(a4, b4); }
template<class T1, class T2>
ostream& operator<< (ostream &out, pair<T1, T2> pair) { return out << "(" << pair.first << ", " << pair.second << ")";}
template<class A, class B, class C> struct Triple { A first; B second; C third;
  bool operator<(const Triple& t) const { if (st != t.st) return st < t.st; if (nd != t.nd) return nd < t.nd; return rd < t.rd; } };
template<class T> void ResizeVec(T&, vector<int>) {}
template<class T> void ResizeVec(vector<T>& vec, vector<int> sz) {
  vec.resize(sz[0]); sz.erase(sz.begin()); if (sz.empty()) { return; }
  for (T& v : vec) { ResizeVec(v, sz); }
}
typedef Triple<int, int, int> TIII;
template<class A, class B, class C>
ostream& operator<< (ostream &out, Triple<A, B, C> t) { return out << "(" << t.st << ", " << t.nd << ", " << t.rd << ")"; }
template<class T> ostream& operator<<(ostream& out, vector<T> vec) { out<<"("; for (auto& v: vec) out<<v<<", "; return out<<")"; }
const int N = 1e6 + 6;
const int sqrt = 500;
struct pkt {
  int x, y, nr;
};

bool cmp(pkt a, pkt b) {
  if (a.y / sqrt != b.y / sqrt) {
    return a.y < b.y;
  }
  if ((a.y / sqrt) % 2 == 0) {
    return a.x < b.x;
  }
  return a.x > b.x;
}
int t[N];
int sito[N];
pkt zap[N];
int odp[N];
const int P = 1e9 + 7;
int cur_cnt[N];
int cur_res = 0;
int spow(int a, int b) {
  int r = 1;
  while (b) {
    if (b % 2) {
      r = (ll)a * r % P;
    }
    a = (ll)a * a % P;
    b /= 2;
  }
  return r;
}
int inv(int a) {
  return spow(a, P - 2);
}
VI lp[N];
int in[N], out[N];
void dodaj(int w) {
  cur_res = (ll)cur_res * t[w] % P;
  debug(t[w]);
  for (auto x : lp[w]) {
    cur_cnt[x]++;
    if (cur_cnt[x] == 1) {
      cur_res = (ll)cur_res * in[x] % P;
      debug(in[x]);
    }
  }
}
int inv_t[N];
void odejmij(int w) {
  if (inv_t[w] == 0) {
    debug(w);
  }
  cur_res = (ll)cur_res * inv_t[w] % P;
  debug(inv_t[w]);
  for (auto x : lp[w]) {
    cur_cnt[x]--;
    if (cur_cnt[x] == 0) {
      cur_res = (ll)cur_res * out[x] % P;
      debug(out[x]);
    }
  }
}
  
int main() {

  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(10);
  cerr << fixed << setprecision(10);
  cin.tie(0);
  //double beg_clock = 1.0 * clock() / CLOCKS_PER_SEC;
  
  for (int i = 2; i < N; i++) {
    if (sito[i] == 0) {
      in[i] = (ll)(i - 1) * inv(i) % P;
      out[i] = inv(in[i]);
      for (int j = 1; i * j < N; j++) {
        sito[i * j] = i;
      }
    }
  }
  int n;
  cin>>n;
  debug(inv(1));
  //inv_t[1] = 1;
  RE (i, n) {
    cin>>t[i];
    inv_t[i] = inv(t[i]);
    int tmp = t[i];
    while (tmp > 1) {
      int p = sito[tmp];
      debug(p, in[p], out[p]);
      lp[i].PB(p);
      while (tmp % p == 0) {
        tmp /= p;
      }
    }
    debug(t[i], inv_t[i]);
    debugv(lp[i]);
  }
  cur_res = 1;
  make(int, q);
  RE (i, q) {
    make2(int, l, r);
    zap[i].x = l;
    zap[i].y = r;
    zap[i].nr = i;
  }
  sort(zap+1, zap+1+q, cmp);
  t[0] = 1;
  inv_t[0] = 1;
  int aktl=0;
  int aktr=0;
  // cout<<sqrt<<endl;
  for(int i=1; i<=q; i++)
  {
      if(zap[i].x<aktl)
      {
          while(aktl!=zap[i].x)
          {
              aktl--;
              dodaj(aktl);
          }
      }
      else
      {
          while(aktl!=zap[i].x)
          {
              odejmij(aktl);
              aktl++;
          }
      }
      if(zap[i].y<aktr)
      {
          while(aktr!=zap[i].y)
          {
              odejmij(aktr);
              aktr--;
          }
      }
      else
      {
          while(aktr!=zap[i].y)
          {
              aktr++;
              dodaj(aktr);
          }
      }
      debug(zap[i].nr, aktl, aktr, cur_res);
      odp[zap[i].nr]=cur_res;
  }
  for(int i=1; i<=q; i++)
  {
      cout<<odp[i]<<"\n";
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  return 0;
}