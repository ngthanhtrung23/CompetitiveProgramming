#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef pair<ii,int> i3;
map<int,int> code;
set<int> color[200005];
vector<int> cnt;
int n,k,BIT[200005],ans;
i3 jewel[200005];
void update(int x,int w) { for(; x<=n; x+=(x&(-x))) BIT[x]+=w; }
int query(int x)
{
    int res=0;
    for(; x>0; x-=(x&(-x))) res+=BIT[x];
    return res;
}
void add(int l,int r)
{
    for(int i=l; i<=r; i++)
    {
        update(jewel[i].first.second,1);
        color[jewel[i].second].insert(jewel[i].first.second);
    }
}
void cal(int l,int r)
{
    for(int i=l; i<=r; i++)
    {
        int u,v;
        if(color[jewel[i].second].count(jewel[i].first.second)) continue;
        set<int>::iterator it = color[jewel[i].second].lower_bound(jewel[i].first.second);
        it--; u = *it;
        it++; v = *it;
        ans = max(ans,query(v-1)-query(u));
    }
}
void execute()
{
    ans = 0;
    code.clear(); cnt.clear();
    memset(BIT,0,sizeof(BIT));
    scanf("%d %d",&n,&k);
    for(int i=1; i<=k; i++)
    {
        color[i].clear();
        color[i].insert(0);
        color[i].insert(n+1);
    }
    for(int i=1; i<=n; i++)
    {
        scanf("%d %d %d",&jewel[i].first.second,&jewel[i].first.first,&jewel[i].second);
        cnt.push_back(jewel[i].first.second);
    }
    sort(jewel+1,jewel+n+1);
    sort(cnt.begin(),cnt.end());
    cnt.assign(cnt.begin(),unique(cnt.begin(),cnt.end()));
    for(int i=0; i<cnt.size(); i++) code[cnt[i]] = i+1;
    for(int i=1; i<=n; i++) jewel[i].first.second = code[jewel[i].first.second];
    for(int i=1; i<=n; i++)
    {
        int j = i;
        while(j+1<=n && jewel[j+1].first.first == jewel[i].first.first) j++;
        cal(i,j);
        add(i,j);
        i = j;
    }
    for(int i=1; i<=k; i++)
    {
        set<int>::iterator it = color[i].begin();
        int last = *it; it++;
        for(; it!=color[i].end(); it++)
        {
            int cur = *it;
            ans = max(ans,query(cur-1)-query(last));
            last = cur;
        }
    }
    printf("%d\n",ans);
}
int main()
{
    //freopen("G.inp","r",stdin);
    //freopen("G.out","w",stdout);
    int test;
    scanf("%d",&test);
    while(test--) execute();
    return 0;
}