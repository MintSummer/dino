//考虑对于距离为i的点建立t[i]，表示在当前递归到的子树中，走到距离为i的顶点最少需要走多少边
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=200010,inf=0x3f3f3f3f;
    int n,k,cnt,root,sum,tot,ans;
    int size[MAXN],f[MAXN],dis[MAXN],Head[MAXN],len[MAXN],d[MAXN],t[1000010];
    bool vis[MAXN];

    struct edge
    {
		int to,next,w;
    }E[MAXN*2];

    void add(int u,int v,int w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    void find_root(int u,int fa)
    {
		size[u]=1,f[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa||vis[v]) continue;
			find_root(v,u);
			size[u]+=size[v];
			f[u]=max(f[u],size[v]);
		}
		f[u]=max(f[u],sum-size[u]);
		if(f[u]<f[root]) root=u;
    }

    void dfs(int u,int fa)
    {
		if(dis[u]<=k) ans=min(ans,t[k-dis[u]]+d[u]);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]||v==fa) continue;
			dis[v]=dis[u]+E[i].w;
			d[v]=d[u]+1;
			dfs(v,u);
		}
    }

    void update(int u,int fa,int opt)
    {
		if(dis[u]<=k)
		{
			if(opt) t[dis[u]]=min(t[dis[u]],d[u]);
			else t[dis[u]]=inf;
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]||v==fa) continue;
			update(v,u,opt);
		}
    }

    void solve(int u)
    {
		vis[u]=1;
		t[0]=0;//每次进入dfs_solve时tmp[0]=0，因为这个当前的根到自己距离为0，走过了0条边
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			dis[v]=E[i].w;
			d[v]=1;
			dfs(v,0);
			update(v,0,1);
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!vis[v]) update(v,0,0);
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			root=0,sum=size[v];
			find_root(v,0);
			solve(root);
		}
    }

    void work()
    {
		scanf("%d%d",&n,&k);
		int u,v,w;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			u++,v++;
			add(u,v,w),add(v,u,w);
		}
		for(int i=1;i<=k;i++) t[i]=inf;
		ans=inf;
		root=0,sum=n,f[0]=inf;
		find_root(1,0);
		solve(root);
		if(ans!=inf) printf("%d",ans);
		else printf("-1");
		}
}

int main()
{
    TYC::work();
    return 0;
}
