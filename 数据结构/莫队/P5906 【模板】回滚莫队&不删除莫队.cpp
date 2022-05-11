#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e5+10;
int n,m,a[MAXN],b[MAXN],ans[MAXN],block,ys[MAXN],lastn,bnum,r[MAXN];
struct node
{
	int l,r,id;
}q[MAXN];

int read()
{
	int sum=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum;
}

bool cmp(const node &fir,const node &sec)
{
	if(ys[fir.l]^ys[sec.l]) return ys[fir.l]<ys[sec.l];
	return fir.r<sec.r;
}

void add(int x)
{
	int p=lower_bound(b+1,b+lastn+1,a[x])-(b+1);
	r[b[p]]=max(r[b[p]],x);
}
void deal(int x,int op)
{
	int p=lower_bound(b+1,b+lastn+1,a[x])-(b+1);
	ans[q[op].id]=max(ans[q[op].id],r[b[p]]-x+1);
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) b[i]=a[i]=read();
	sort(b+1,b+n+1);
	lastn=unique(b+1,b+n+1)-(b+1);
	block=sqrt(n);bnum=ceil((double)n/block);
	for(int i=1;i<=n;i++) ys[i]=(i-1)/block+1;
	for(int i=1;i<=m;i++) {q[i].l=read();q[i].r=read();q[i].id=i;}
	sort(q+1,q+m+1,cmp);
	int j=1;
	for(int i=1;i<=bnum;i++)
	{
		memset(r,0,sizeof(r));
		int l=i*block+1,r=l-1;
		for(;ys[q[j].l]==i;j++)
		{
			while(r<q[i].r) add(r++);
			while(l>q[i].l) deal(l--,j);
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
