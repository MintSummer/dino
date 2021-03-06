#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=100010;
    int n,s,cnt,Head[MAXN],leaf[MAXN];
    ll dp[MAXN];

    struct edge
    {
		int to,next;
		ll w;
    }E[MAXN*2];

    void add(int u,int v,ll w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    void dfs(int u,int fa)
    {
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			dfs(v,u);
			dp[v]=min(dp[v],E[i].w);
			dp[u]+=dp[v];
		}
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n>>s;
		int u,v;
		ll w;
		for(int i=1;i<n;i++)
		{
			cin>>u>>v>>w;
			add(u,v,w),add(v,u,w);
			leaf[u]++,leaf[v]++;
		}
		for(int i=1;i<=n;i++)
			if(leaf[i]==1&&i!=s) dp[i]=0x3f3f3f3f;
		dfs(s,0);
		cout<<dp[s];
    }
}

int main()
{
    TYC::work();
    return 0;
}
