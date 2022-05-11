#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+10;
int n,m,total,ans[MAXN],block,ys[MAXN],a[MAXN],cnt[MAXN];
struct node
{
	int l,r,id;
}q[MAXN];

int read()
{
	int sum=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum;
}

bool cmp(const node &fir,const node &sec)
{
	if(ys[fir.l]^ys[sec.l]) return ys[fir.l]<ys[sec.l];
	if(ys[fir.l]&1) return fir.r<sec.r;
	return fir.r>sec.r;
}

void del(int x)
{
	if(a[x]>n) return ;
	if(cnt[a[x]]==a[x]) total--;
	cnt[a[x]]--;
	if(cnt[a[x]]==a[x]) total++;
}
void add(int x)
{
	if(a[x]>n) return ;
	if(cnt[a[x]]==a[x]) total--;
	cnt[a[x]]++;
	if(cnt[a[x]]==a[x]) total++;
}

int main()
{
	n=read();m=read();block=317;
	for(int i=1;i<=n;i++) {ys[i]=(i-1)/block+1;a[i]=read();}
	for(int i=1;i<=m;i++) {q[i].l=read();q[i].r=read();q[i].id=i;}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].l) del(l++);
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		ans[q[i].id]=total;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
