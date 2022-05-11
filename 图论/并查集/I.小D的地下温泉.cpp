#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+10;
int n,m,fa[MAXN<<1],size[MAXN<<1],q,ys[MAXN<<1],tmp;
int Next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
char a[MAXN];

int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
void hb(int x,int y) {if(gf(x)!=gf(y)) {if(size[fa[y]]>size[fa[x]]) swap(x,y);size[fa[y]]+=size[fa[x]];fa[fa[x]]=fa[y];}}
int turn(int x,int y) {return (x-1)*m+y;}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();m=read();tmp=n*m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[turn(i,j)];
	for(int i=1;i<=n*m;i++) {fa[i]=i;size[i]=((a[i]=='.')?1:0);}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ys[turn(i,j)]=turn(i,j);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(i!=1)
			{
				if(a[turn(i,j)]=='.'&&a[turn(i-1,j)]=='.') hb(turn(i,j),turn(i-1,j));
			}
			if(j!=1)
			{
				if(a[turn(i,j)]=='.'&&a[turn(i,j-1)]=='.') hb(turn(i,j),turn(i,j-1));
			}
		}
	q=read();
	for(int i=1;i<=q;i++)
	{
		int op,w;
		op=read();w=read();
		if(op==1)
		{
			int flag=1,ans=0;
			for(int j=1;j<=w;j++)
			{
				int x,y;
				x=read();y=read();
				if(a[turn(x,y)]=='.'&&size[gf(ys[turn(x,y)])]>ans)
				{
					ans=size[gf(ys[turn(x,y)])];
					flag=j;
				}
			}
			cout<<flag<<"\n";
		}
		else
		{
			for(int j=1;j<=w;j++)
			{
				int x,y;
				x=read();y=read();
				if(a[turn(x,y)]=='.')
				{
					a[turn(x,y)]='*';
					size[gf(ys[turn(x,y)])]--;
				}
				else
				{
					ys[turn(x,y)]=++tmp;
					a[turn(x,y)]='.';fa[ys[turn(x,y)]]=ys[turn(x,y)];size[ys[turn(x,y)]]=1;
					for(int k=0;k<4;k++)
					{
						int tx=x+Next[k][0];
						int ty=y+Next[k][1];
						if(tx>0&&ty>0&&tx<=n&&ty<=m&&a[turn(tx,ty)]=='.') hb(ys[turn(x,y)],ys[turn(tx,ty)]);
					}
				}
			}
		}
	}
	return 0;
}
