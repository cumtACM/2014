/*
 * 首先，我们默认要拉所有选民，然后开始减少要拉的选民数。这是中心思想。
 * 具体的实现方式是，我们先对每个人的选民进行代价排序，然后扫描出来每
 * 个候选人的选民的代价 rank，同等 rank 的放在一起，你要是问什么是
 * rank 的话，举个最简单的例子，有 A、B、C 三个候选人，选民叛变的代
 * 价从大到小排序后分别是 11，10，9、8，7，3，1、15，2，那么根据
 * rank 分组我们可以分为四组，rank1 的组有 11，8，15，rank2 的组
 * 有 10，7，2，rank3 的组有 9，3，rank4 的组有 1。这就是扫描线的
 * 过程，我想不难理解吧……然后呢？我们开始考虑剔除一些不必要的选民，
 * 当然是优先剔除每个候选人的叛变代价最大的选民，也就是说逐次剔除
 * rank：1、2、3、4 的选民，每次剔除一组选民后，我们都要判断，此时
 * 剩下的选民和其他候选人目前拥有的最多的选民数目，这个数目是多少呢？
 * 自然是我们剔除的次数了。如果说，我们此时的选民小于等于其他候选人目
 * 前拥有最多的选民数目，我们怎么办？这个部分很好想，当然是从剔除的所
 * 有选民中选取最小的若干个选民喽，那么这部分就是需要用到线段树来处理了
*/
#include<bits/stdc++.h>
using namespace std;
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r

typedef long long lolo;
const int maxn=100005;
const int maxm=10005;
template <class T>
void read(T& x) {
	x=0;char ch;
	do { ch=getchar(); }while(ch>'9'||ch<'0');
	do { x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
}
int n;
int m;
int add;
vector<int> vt[maxn];
vector<int> rk[maxn];
int num[maxm<<2],C[maxn<<2];
void update(int o,int l,int r) {
	if(l==r) {
		num[o]++;
		C[o]+=l;
		return;
	}
	int mid=(l+r)>>1;
	add<=mid?update(lson):update(rson);
	num[o]=num[o<<1]+num[o<<1|1];
	C[o]=C[o<<1]+C[o<<1|1];
}
int query(int o,int l,int r,int prex) {
	if(prex==num[o]) return C[o];
	if(l==r)
		return l*prex;
	int mid=(l+r)>>1;
	if(prex>num[o<<1]) return C[o<<1]+query(rson,prex-num[o<<1]);
	else return query(lson,prex);
}
int main(){
	read(n);
	int mx_a=0,mx_b=0,sum=0,ans;
	for(int i=1;i<=n;i++) {
		int a,b;
		read(a);read(b);
		if(b==0) continue;
		vt[a].push_back(b);
		sum+=b;
		if(a>mx_a) mx_a=a;
		if(b>mx_b) mx_b=b;
	}
	int mx_r=0;
	for(int i=1;i<=mx_a;i++) {
		sort(vt[i].begin(),vt[i].end(),greater<int>());
		int sz=vt[i].size();
		if(sz>mx_r) mx_r=sz;
		for(int j=0;j<sz;j++) {
			rk[j].push_back(vt[i][j]);
		}
	}
	int k=n;
	ans=sum;
	for(int i=0;i<mx_r;i++) {
		int sz=rk[i].size();
		k-=sz;
		for(int j=0;j<sz;j++) {
			add=rk[i][j];
			update(1,1,mx_b);
			sum-=add;
		}
		int tmp=0;
		if(k<=i+1) {
			tmp=query(1,1,mx_b,min(i+2-k,n));
		}
//		cout<<k<<" "<<sum<<" "<<tmp<<endl;
		ans=min(ans,sum+tmp);
	}
	printf("%d\n",ans);
	return 0;
}
