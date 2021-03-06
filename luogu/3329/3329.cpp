#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int MAXN=310,inf=0x3f3f3f3f;
    int n,m,cnt,s,t,Head[MAXN],vis[MAXN],a[MAXN],cur[MAXN],dep[MAXN],flow[MAXN][MAXN],tmp[MAXN];

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int to,next,w;
    }E[2000010];

    void add(int u,int v,int w)
    {
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
    }

    void init()
    {
		cnt=1;
		memset(Head,0,sizeof(Head));
		for(int i=1;i<=150;i++)
			for(int j=1;j<=150;j++)
				flow[i][j]=inf;
    }

    void clear()
    {
		for(int i=2;i<=cnt;i++)
			E[i].w=E[i^1].w=(E[i].w+E[i^1].w)>>1;   
    }

    bool bfs()
    {
		memset(dep,-1,sizeof(dep));
		queue<int> q;
		dep[s]=0;
		q.push(s);
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dep[v]==-1)
					dep[v]=dep[u]+1,q.push(v);
			}
		}
		return dep[t]!=-1;
    }

    int dfs(int u,int mn)
    {
		if(u==t) return mn;
		int w,used=0;
		for(int &i=cur[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(E[i].w&&dep[v]==dep[u]+1)
			{
				w=dfs(v,min(mn-used,E[i].w));
				E[i].w-=w,E[i^1].w+=w;
				used+=w;
				if(used==mn) return used;
			}
		}
		if(!used) dep[u]=-1;
		return used;
    }

    int Dinic()
    {
		int ans=0;
		while(bfs())
		{
			memcpy(cur,Head,sizeof(cur));
			ans+=dfs(s,inf);
		}
		return ans;
    }

    void dfs1(int u)
    {
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(E[i].w&&!vis[v]) dfs1(v);
		}
    }

    void solve(int l,int r)
    {
		if(l==r) return;
		s=a[l],t=a[r];	
		clear();
		int f=Dinic();
		memset(vis,0,sizeof(vis));
		dfs1(s);
		for(int i=1;i<=n;i++) if(vis[i])
			for(int j=1;j<=n;j++) if(!vis[j])
				flow[i][j]=flow[j][i]=min(flow[i][j],f);
		int L=l,R=r;
		for(int i=l;i<=r;i++)
			if(vis[a[i]]) tmp[L++]=a[i];
			else tmp[R--]=a[i]; 
		for(int i=l;i<=r;i++) a[i]=tmp[i];
		solve(l,L-1),solve(R+1,r);
    }

    void work()
    {
		int T=read();
		while(T--)
		{
			init();
			n=read(),m=read();
			for(int i=1;i<=m;i++)
			{
				int u=read(),v=read(),w=read();
				add(u,v,w),add(v,u,w);
			}
			for(int i=1;i<=n;i++) a[i]=i;
			solve(1,n);
			int q=read();
			while(q--)
			{
				int x=read(),ans=0;
				for(int i=1;i<=n;i++)
					for(int j=i+1;j<=n;j++)
						if(flow[i][j]<=x) ans++;
				printf("%d\n",ans);
			}
			puts("");
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}

