#include<bits/stdc++.h>
using namespace std;

const int MAXN=500+10;
int t,n,m,a[MAXN][MAXN],b[MAXN][MAXN],fa[MAXN*MAXN],size[MAXN*MAXN],tmp,cnt[MAXN*MAXN];
typedef long long LL;
LL ans;
struct node
{
	int a,b,c;
}dis[2*MAXN*MAXN];

int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
int turn(int x,int y) {return (x-1)*m+y;}
bool cmp(const node &fir,const node &sec) {return fir.c<sec.c;}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();m=read();t=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			b[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(j!=m)
			{
				tmp++;
				dis[tmp].a=turn(i,j);dis[tmp].b=turn(i,j+1);dis[tmp].c=abs(a[i][j]-a[i][j+1]);
			}
			if(i!=n)
			{
				tmp++;
				dis[tmp].a=turn(i,j);dis[tmp].b=turn(i+1,j);dis[tmp].c=abs(a[i][j]-a[i+1][j]);
			}
			if(b[i][j]==1) cnt[turn(i,j)]=1;
		}
	for(int i=1;i<=n*m;i++) fa[i]=i,size[i]=1;
	sort(dis+1,dis+tmp+1,cmp);
	for(int i=1;i<=tmp;i++)
	{
		int fx=gf(dis[i].a),fy=gf(dis[i].b);
		if(fx==fy) continue;
		if(size[fy]+size[fx]>=t)
		{
			if(size[fy]<t) ans+=(LL)dis[i].c*cnt[fy];
			if(size[fx]<t) ans+=(LL)dis[i].c*cnt[fx];
		}
		if(size[fx]>size[fy]) swap(fx,fy);
		fa[fx]=fy;
		size[fy]+=size[fx];cnt[fy]+=cnt[fx];
	}
	cout<<ans<<"\n";
	return 0;
}
