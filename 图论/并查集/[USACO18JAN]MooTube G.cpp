#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+10;
int n,t,fa[MAXN],size[MAXN],j,ans[MAXN];
struct node1
{
	int p,q,r;
}a[MAXN];
struct node2
{
	int k,v,i;
}q[MAXN];

int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
void hb(int x,int y) {if(gf(x)!=gf(y)) {size[fa[y]]+=size[fa[x]];fa[fa[x]]=fa[y];}}
bool cmp1(const node1 &fir,const node1 &sec) {return fir.r>sec.r;}
bool cmp2(const node2 &fir,const node2 &sec) {return fir.k>sec.k;}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();t=read();j=1;
	for(int i=1;i<n;i++) {a[i].p=read();a[i].q=read();a[i].r=read();}
	for(int i=1;i<=t;i++) {q[i].k=read();q[i].v=read();q[i].i=i;}
	for(int i=1;i<=n;i++) {fa[i]=i;size[i]=1;}
	sort(a+1,a+n,cmp1);
	sort(q+1,q+t+1,cmp2);
	for(int i=1;i<=t;i++)
	{
		while(j<n&&a[j].r>=q[i].k) {hb(a[j].p,a[j].q);j++;}
		ans[q[i].i]=size[gf(q[i].v)];
	}
	for(int i=1;i<=t;i++) cout<<ans[i]-1<<"\n";
	return 0;
}
