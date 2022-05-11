#include<bits/stdc++.h>
using namespace std;

const int MAXN=20000+10,MAXM=100000+10;
int n,m,fa[MAXN],d[MAXN];
struct node
{
	int a,b,c;
}a[MAXM];

bool cmp(const node &fir,const node &sec) {return fir.c>sec.c;}
int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
void hb(int x,int y) {if(gf(x)!=gf(y)) fa[fa[x]]=fa[y];}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++) {a[i].a=read();a[i].b=read();a[i].c=read();}
	for(int i=1;i<=n;i++) fa[i]=i;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		if(gf(a[i].a)!=gf(a[i].b))
		{
			if(!d[a[i].a]) d[a[i].a]=a[i].b;
			else hb(d[a[i].a],a[i].b);
			if(!d[a[i].b]) d[a[i].b]=a[i].a;
			else hb(d[a[i].b],a[i].a);
		}
		else {cout<<a[i].c<<"\n";return 0;}
	}
	cout<<"0\n";
	return 0;
}
