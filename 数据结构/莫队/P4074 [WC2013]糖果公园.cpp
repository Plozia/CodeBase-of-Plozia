#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
int n, m, que, v[MAXN], w[MAXN], c[MAXN], fir[MAXN], las[MAXN], ys[MAXN], block, fa[MAXN][21], eular[MAXN << 1], dep[MAXN], cntq, cntc, vis[MAXN];
typedef long long LL;
LL ans[MAXN], total, cnt[MAXN];
vector <int> Next[MAXN];
struct query
{
	int l, r, id, lca, Time;
}q[MAXN];
struct change
{
	int pos, val;
}cha[MAXN];

int read()
{
	int sum = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') { sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar(); }
	return sum;
}

void dfs(int x)
{
	eular[++eular[0]] = x;
	fir[x] = eular[0];
	for(int i = 0; i < Next[x].size(); ++i)
	{
		int u=Next[x][i];
		if(dep[u]) continue;
		dep[u]=dep[x]+1;
		fa[u][0]=x;
		dfs(u);
	}
	eular[++eular[0]]=x;
	las[x]=eular[0];
}

void st()
{
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++)
			fa[j][i]=fa[fa[j][i-1]][i-1];
}

int getlca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	int d=dep[x]-dep[y],tmp=-1;
	while(d)
	{
		tmp++;int p=d&1;d>>=1;
		if(p) x=fa[x][tmp];
	}
	if(x==y) return x;
	for(int i=20;i>=0;i--)
		if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

bool cmp(const query &fir,const query &sec)
{
	if(ys[fir.l]^ys[sec.l]) return ys[fir.l]<ys[sec.l];
	if(ys[fir.r]^ys[sec.r]) return ys[fir.r]<ys[sec.r];
	return fir.Time<sec.Time;
}

void add(int x)
{
	total+=1ll*v[c[x]]*w[++cnt[c[x]]];
}
void del(int x)
{
	total-=1ll*v[c[x]]*w[cnt[c[x]]--];
}

void work(int x)
{
	vis[x]?del(x):add(x);
	vis[x]^=1;
}

void deal(int t)
{
	if(vis[cha[t].pos])
	{
		work(cha[t].pos);
		swap(c[cha[t].pos],cha[t].val);
		work(cha[t].pos);
	}
	else swap(c[cha[t].pos],cha[t].val);
}

int main()
{
	n=read();m=read();que=read();
	for(int i=1;i<=m;i++) v[i]=read();
	for(int i=1;i<=n;i++) w[i]=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		Next[x].push_back(y);
		Next[y].push_back(x);
	}
	for(int i=1;i<=n;i++) c[i]=read();
	fa[1][0]=1;dep[1]=1;dfs(1);st();block=ceil(pow(eular[0],2.0/3.0));
	for(int i=1;i<=(n<<1);i++) ys[i]=(i-1)/block+1;
	for(int i=1;i<=que;i++)
	{
		int opt=read(),zzh1=read(),zzh2=read();
		if(opt)
		{
			q[++cntq].id=cntq;
			q[cntq].Time=cntc;
			if(fir[zzh1]>fir[zzh2]) swap(zzh1,zzh2);
			int qlca=getlca(zzh1,zzh2);
			if(zzh1==qlca) q[cntq].l=fir[zzh1],q[cntq].r=fir[zzh2];
			else q[cntq].l=las[zzh1],q[cntq].r=fir[zzh2],q[cntq].lca=qlca;
		}
		else
		{
			cha[++cntc].pos=zzh1;
			cha[cntc].val=zzh2;
		}
	}
	sort(q+1,q+cntq+1,cmp);
	int l=1,r=0,t=0;
	for(int i=1;i<=cntq;i++)
	{
		while(l<q[i].l) work(eular[l++]);
		while(l>q[i].l) work(eular[--l]);
		while(r<q[i].r) work(eular[++r]);
		while(r>q[i].r) work(eular[r--]);
		while(t<q[i].Time) deal(++t);
		while(t>q[i].Time) deal(t--);
		if(q[i].lca) work(q[i].lca);
		ans[q[i].id]=total;
		if(q[i].lca) work(q[i].lca);
	}
	for(int i=1;i<=cntq;i++) printf("%lld\n",ans[i]);
	return 0;
}
