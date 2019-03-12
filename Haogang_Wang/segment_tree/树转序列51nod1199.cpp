/*
 * 同一个子树的点在一个连续的序列中
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
const int maxn=50005;
vector<int> G[maxn];
int P[maxn],sz[maxn],Id[maxn],idx[maxn];
lolo allW[maxn<<2],W[maxn],lazy[maxn<<2];
int p,L,R,add;
template<class T>
void read(T& x) {
	x=0;char ch;
	do { ch=getchar(); }while(ch>'9'||ch<'0');
	do { x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
}
void dfs(int root) {
	Id[++Id[0]]=root;idx[root]=Id[0];
	sz[root]=1;
	for(int i=G[root].size()-1;i>=0;i--) {
		int& child=G[root][i];
		dfs(child);
		sz[root]+=sz[child];
	}
}
void build(int o,int l,int r) {
	lazy[o]=-1;
	if(l==r) {
		allW[o]=W[Id[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	allW[o]=allW[o<<1]+allW[o<<1|1];
}
void push_down(int o,int l,int r) {
	if(lazy[o]==-1) return;
	if(lazy[o<<1]!=-1) lazy[o<<1]+=lazy[o];else lazy[o<<1]=lazy[o];
	if(lazy[o<<1|1]!=-1) lazy[o<<1|1]+=lazy[o];else lazy[o<<1|1]=lazy[o];
	int mid=(l+r)>>1;
	allW[o<<1]+=lazy[o]*(mid-l+1);allW[o<<1|1]+=lazy[o]*(r-mid);
	lazy[o]=-1;
}
void updateS(int o,int l,int r) {
	if(l==r) {
		allW[o]+=add;
		return;
	}
	push_down(o,l,r);
	int mid=(l+r)>>1;
	p<=mid?updateS(o<<1,l,mid):updateS(o<<1|1,mid+1,r);
	allW[o]=allW[o<<1]+allW[o<<1|1];
}
void updateA(int o,int l,int r) {
	if(L<=l&&R>=r) {
		if(lazy[o]==-1) lazy[o]=add;else lazy[o]+=add;
		allW[o]+=1LL*add*(r-l+1);
		return;
	}
	push_down(o,l,r);
	int mid=(l+r)>>1;
	if(L<=mid) updateA(o<<1,l,mid);
	if(R>mid) updateA(o<<1|1,mid+1,r);
	allW[o]=allW[o<<1]+allW[o<<1|1];
}
lolo queryA(int o,int l,int r) {
	if(L<=l&&R>=r) return allW[o];
	push_down(o,l,r);
	int mid=(l+r)>>1;
	lolo ret=0;
	if(L<=mid) ret+=queryA(o<<1,l,mid);
	if(R>mid) ret+=queryA(o<<1|1,mid+1,r);
	return ret;
}
lolo queryS(int o,int l,int r) {
	if(l==r) return allW[o];
	push_down(o,l,r);
	int mid=(l+r)>>1;
	return p<=mid?queryS(o<<1,l,mid):queryS(o<<1|1,mid+1,r);
}
int main() {
    memset(lazy,-1, sizeof(lazy));
	int n,m,x,y;
	read(n);read(m);
	for(int i=2;i<=n;i++) {
		read(P[i]);read(W[i]);
		P[i]++;
		G[P[i]].push_back(i);
	}
	dfs(1);
	build(1,1,n);
	while(m--) {
		char op=getchar();
		while(op=='\n'||op==' ') op=getchar();
		read(x);read(y);read(add);
		x++;
		if(op=='S') {
			p=idx[x];
			if(queryS(1,1,n)<y) updateS(1,1,n);
		} else {
			L=idx[x];
			R=L+sz[x]-1;
			if(queryA(1,1,n)>=1LL*y*sz[x]) continue;
			updateA(1,1,n);
		}
	}
	for(int i=1;i<=n;i++) {
		p=idx[i];
		printf("%lld\n",queryS(1,1,n));
	}
	return 0;
}
