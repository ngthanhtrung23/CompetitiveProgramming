/**
  * Here's my approach for DIV1E. The main idea is to see which segments must be 
  * colored differently, which we approach in a greedy way.
  * First, sort the segments (first by increasing start coordinate, breaking ties 
  * by end coordinate). Now, take the first two segments, and call them A and B. 
  * Observe the following cases. I'll be using A.s to refer to the start coordinate, 
  * and A.e to refer to the end coordinate.
  *     + A.e < B.s: Segment A doesn't interact with any other segment, so we can 
  *       color it arbitrarily, so we remove A from the list of segments.
  *     + otherwise, A.e >= B.s: We want to color A and B different colors to cancel 
  *       them out, however, all we know is that they must be different, so we 
  *       remember this by adding an edge in between them. Notice that the interval 
  *       from A.s to B.s-1 will have an excess of one red or blue, but since the 
  *       segments are sorted, no other segments will touch that, so we don't have 
  *       to worry about them. Thus, the only tricky part is the left over stuff at 
  *       the right end. We deal with these in the following three subcases:
  *             + A.e == B.e: There is no left over, so remove both A and B from the 
  *               list and continue.
  *             + A.e < B.e: Everything up to A.e is good. However, we set the new 
  *               start point of B to be A.e+1, and remove A from the list of segments.
  *             + B.e < A.e: This is symmetric to the case above.
  * We repeat the following procedure until we have less than two segments. Now we 
  * have a graph, with nodes representing segments, and an edge between them if the 
  * nodes need to be colored differently. We can see we have a solution if and only 
  * if this graph is two-colorable. However, notice that the above procedure does 
  * not produce any cycles in the graph, so the graph we have is a tree, which we can 
  * always two-color, so we just go through this tree and assign colors.
  */
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;
pair<int,int> a[MN];
vector<int> ke[MN];
int color[MN];
int n;

void dfs(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        color[v] = 1 - color[u];
        dfs(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        multiset< pair<pair<int,int>,int> > s;
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
            s.insert(make_pair(a[i], i));
            ke[i].clear();
        }

        memset(color, -1, sizeof color);
        while (s.size() >= 2) {
            pair<int,int> a = s.begin()->first; int ida = s.begin()->second;
            s.erase(s.begin());
            pair<int,int> b = s.begin()->first; int idb = s.begin()->second;
            s.erase(s.begin());

            if (a.second < b.first) {
                s.insert(make_pair(b, idb));
            }
            else {
                ke[ida].push_back(idb);
                ke[idb].push_back(ida);
                if (a.second == b.second) {
                }
                else if (a.second < b.second) {
                    s.insert(make_pair(make_pair(a.second+1, b.second), idb));
                }
                else {
                    s.insert(make_pair(make_pair(b.second+1, a.second), ida));
                }
            }
        }

        FOR(i,1,n) if (color[i] < 0) {
            color[i] = 0;
            dfs(i, -1);
        }

        FOR(i,1,n) cout << color[i] << ' '; cout << endl;
    }
    return 0;
}
