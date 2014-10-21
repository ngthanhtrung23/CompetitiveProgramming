#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

int t,n;
int le[100005], ri[100005];
int key[100005];
int dp[100005];
int i;
set <pair<int, int> > *pq[100005];

void removestree(int x, int y) {
  if (x == -1)
    return;
  if (pq[y]->find(mp(key[x], x)) == pq[y]->end())
    return;
  pq[y]->erase(mp(key[x], x));
  removestree(le[x], y);
  removestree(ri[x], y);
}
int maxi;

void dfs(int x) {
  if (le[x] != -1)
    dfs(le[x]);
  if (ri[x] != -1)
    dfs(ri[x]);
    
    
  int lefsz,rigsz;
  if (le[x] != -1) {
    while (pq[le[x]]->size() > 0 && (pq[le[x]]->rbegin())->fi >= key[x]) {
      removestree((pq[le[x]]->rbegin())->se, le[x]);
    }
    lefsz = pq[le[x]]->size();
  } else {
    lefsz = 0;
  }
  if (ri[x] != -1) {
    while (pq[ri[x]]->size() > 0 && (pq[ri[x]]->begin())->fi <= key[x]) {
      removestree((pq[ri[x]]->begin())->se, ri[x]);
    }
    rigsz = pq[ri[x]]->size();
  } else {
    rigsz = 0;
  }
  maxi = max(maxi, 1 + lefsz + rigsz);
  if (le[x] == -1 && ri[x] == -1) {
    pq[x] = new set<pair<int,int> >();
  } else if (le[x] == -1) {
    pq[x] = pq[ri[x]];
  } else if (ri[x] == -1) {
    pq[x] = pq[le[x]];
  } else {
    if (lefsz > rigsz) {
      while (pq[ri[x]]->size() > 0) {
        pq[le[x]]->insert(*(pq[ri[x]]->begin()));
        pq[ri[x]]->erase(pq[ri[x]]->begin());
      }
      delete pq[ri[x]];
      pq[x] = pq[le[x]];
    } else {      
      while (pq[le[x]]->size() > 0) {
        pq[ri[x]]->insert(*(pq[le[x]]->begin()));
        pq[le[x]]->erase(pq[le[x]]->begin());
      }
      delete pq[le[x]];
      pq[x] = pq[ri[x]];
    }
  }
  pq[x]->insert(mp(key[x], x));
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    maxi = -1;
    for (i=0;i<n;i++) {
      scanf("%d %d %d", &le[i], &ri[i], &key[i]);
      --le[i];
      --ri[i];
    }
    dfs(0);
    printf("%d\n", maxi);
    delete pq[0];
  }
}