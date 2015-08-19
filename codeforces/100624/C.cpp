#include<bits/stdc++.h>
using namespace std;
string table[]= {"h", "he", "li", "be", "b", "c", "n", "o", "f", "ne", "na", "mg", "al", "si", "p", "s", "cl", "ar", "k", "ca", "sc", "ti", "v", "cr", "mn", "fe", "co", "ni", "cu", "zn", "ga", "ge", "as", "se", "br", "kr", "rb", "sr", "y", "zr", "nb", "mo", "tc", "ru", "rh", "pd", "ag", "cd", "in", "sn", "sb", "te", "i", "xe", "cs", "ba", "hf", "ta", "w", "re", "os", "ir", "pt", "au", "hg", "tl", "pb", "bi", "po", "at", "rn", "fr", "ra", "rf", "db", "sg", "bh", "hs", "mt", "ds", "rg", "cn", "fl", "lv", "la", "ce", "pr", "nd", "pm", "sm", "eu", "gd", "tb", "dy", "ho", "er", "tm", "yb", "lu", "ac", "th", "pa", "u", "np", "pu", "am", "cm", "bk", "cf", "es", "fm", "md", "no", "lr"};
//114
string S;
bool f[50005];
int n;
bool match(int pos,int t)
{
    for(int i=0; i<table[t].size(); i++)
        if(pos+i<0 || pos+i>=S.size() || table[t][i]!=S[pos+i]) return false;
    return true;
}
bool talkable()
{
    memset(f,false,sizeof(f));
    f[0] = true; n = S.size();
    for(int i=1; i<=n; i++)
        for(int j=0; j<114; j++)
            if(match(i-int(table[j].size()),j)) f[i] |= f[i-int(table[j].size())];
    return f[n];
}
void execute()
{
    cin>>S;
    if(talkable()) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    //freopen("C.inp","r",stdin);
    //freopen("C.out","w",stdout);
    int test;
    scanf("%d",&test);
    while(test--) execute();
    return 0;
}