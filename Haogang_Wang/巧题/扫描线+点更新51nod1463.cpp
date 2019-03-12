/*
 * 两个长度为n的数列A 、B
 * 一个有m个元素的集合K
 * 询问Q次,每次询问[l,r]，输出区间内满足|Bi-Bj|∈K 的最大Ai+Aj
 *
 * 将询问按左边界从大到小排序，每次询问增加一段要考虑的区间，从右向左遍历，
 * 看与其配对（即相加后在K中）的数是不是存在且在右边，更新这个配对数位置
 * j的最大值为max(原值，a[l]+a[j])，同时完成区间更新。查询时就查1~r中的
 * 最大值即可。
*/
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x)&(-(x))
typedef long long lolo;
const int maxn=100005;
template <class T>
void read(T& x) {
	x=0;char ch;
	do { ch=getchar(); }while(ch>'9'||ch<'0');
	do { x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
}

int a[maxn],b[maxn],K[12],C[maxn];
int pos[maxn];
struct Node {
	int l,r,id;
}qs[maxn];
bool cmp(const Node& a,const Node& b) {
	return a.l>b.l;
}
int ans[maxn];
int n,m,q;
void add(int x,int d,int i) {
	if(x<0||x>n||pos[x]<i) return;
	int p=a[pos[x]];x=pos[x];
	while(x<=n) {
		C[x]=max(C[x],p+d);
		x+=lowbit(x);
	}
}
int query(int x) {
	int _max=0;
	while(x>0) {
		_max=max(C[x],_max);
		x-=lowbit(x);
	}
	return _max;
}
int main(){
	read(n);read(q);read(m);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) read(b[i]),pos[b[i]]=i;
	for(int i=1;i<=m;i++) read(K[i]);
	for(int i=0;i<q;i++) {
		read(qs[i].l);read(qs[i].r);qs[i].id=i;
	}
	sort(qs,qs+q,cmp);
	int l=n+1;
	for(int i=0;i<q;i++) {
		for(int j=l-1;j>=qs[i].l;j--) {
			for(int k=1;k<=m;k++) {
				add(b[j]-K[k],a[j],j);
				add(b[j]+K[k],a[j],j);
			}
		}
		l=qs[i].l;
		ans[qs[i].id]=query(qs[i].r);
	}
	for(int i=0;i<q;i++) printf("%d\n",ans[i]);
	return 0;
}
