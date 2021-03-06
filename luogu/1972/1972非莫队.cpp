#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int MAXN=500010;
    int n,c,m,ans,Ans[200010],col[MAXN],nxt[MAXN],pos[1000010],C[1000010];

    inline int read()
    {
        int x=0,f=0;
        char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct query
    {
        int id,l,r;
        bool operator < (const query &a) const
        {
            return (l<a.l)||(l==a.l&&r<a.r);
        }
    }q[MAXN];
    
    int lowbit(int x) {return x&(-x);}

    void add(int x,int d)
    {
        for(;x<=n;x+=lowbit(x)) C[x]+=d;
    }

    int query(int x)
    {
        int sum=0;
        for(;x;x-=lowbit(x)) sum+=C[x];
        return sum;
    }

    void change(int x)
    {
        add(x,-1);
        if(nxt[x]) add(nxt[x],1);
    }	

    void work()
    {
        n=read();
		int mx=0;
        for(int i=1;i<=n;i++) 
	    col[i]=read(),mx=max(mx,col[i]);
        for(int i=n;i;i--) 
        {
            nxt[i]=pos[col[i]];
            pos[col[i]]=i;
        }
        for(int i=1;i<=mx;i++)
            if(pos[i]) add(pos[i],1);
		m=read();
        for(int i=1;i<=m;i++)
        {
            q[i].id=i;
            q[i].l=read(),q[i].r=read();
        }
        sort(q+1,q+1+m);
        int lt=1;
        for(int i=1;i<=m;i++)
        {
            while(lt<q[i].l) change(lt),lt++;
            Ans[q[i].id]=query(q[i].r)-query(q[i].l-1);
        }
        for(int i=1;i<=m;i++) printf("%d\n",Ans[i]);
    }	
}

int main()
{
    TYC::work();
    return 0;
}
