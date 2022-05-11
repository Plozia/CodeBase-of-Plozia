#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e5+10;
typedef long long LL;
int n,m,a[MAXN],b[MAXN],block,ys[MAXN],lastn,bnum;
LL total,ans[MAXN];
map<int,int>cnt,cnt2;
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

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) cnt[a[i]=read()]=0;
	block=sqrt(n);bnum=ceil((double)n/block);
	for(int i=1;i<=n;i++) ys[i]=(i-1)/block+1;
	for(int i=1;i<=m;i++) {q[i].l=read();q[i].r=read();q[i].id=i;}
	sort(q+1,q+m+1,cmp);
	int j=1;
	for(int i=1;i<=bnum;i++)
	{
		cnt.clear();
		int l=i*block+1,r=l-1;
		LL tmp=0;total=0;
		for(;ys[q[j].l]==i;j++)
		{
			if(ys[q[j].l]==ys[q[j].r])
			{
				cnt2.clear();tmp=0;
				for(int k=q[j].l;k<=q[j].r;k++) {cnt2[a[k]]++;tmp=max(tmp,1ll*a[k]*cnt2[a[k]]);}
				ans[q[j].id]=tmp;
				continue;
			}
			while(r<q[j].r) {++r;cnt[a[r]]++;total=max(total,1ll*a[r]*cnt[a[r]]);}
			tmp=total;
			while(l>q[j].l) {--l;cnt[a[l]]++;total=max(total,1ll*a[l]*cnt[a[l]]);}
			ans[q[j].id]=total;
			while(l<i*block+1) {cnt[a[l]]--;l++;}
			total=tmp;
		}
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
