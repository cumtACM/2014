/*http://blog.csdn.net/buaa1306ksy/article/details/49078801
问题描述
　　C国共有n个城市。有n-1条双向道路，每条道路连接两个城市，任意两个城市之间能互相到达。小R来到C国旅行，他共规划了m条旅行的路线，第i条旅行路线的起点是si，终点是ti。在旅行过程中，小R每行走一单位长度的路需要吃一单位的食物。C国的食物只能在各个城市中买到，而且不同城市的食物价格可能不同。
　　然而，小R不希望在旅行中为了购买较低价的粮食而绕远路，因此他总会选择最近的路走。现在，请你计算小R规划的每条旅行路线的最小花费是多少。
输入格式
　　第一行包含2个整数n和m。
　　第二行包含n个整数。第i个整数wi表示城市i的食物价格。
　　接下来n-1行，每行包括3个整数u, v, e，表示城市u和城市v之间有一条长为e的双向道路。
　　接下来m行，每行包含2个整数si和ti，分别表示一条旅行路线的起点和终点。
输出格式
　　输出m行，分别代表每一条旅行方案的最小花费。
样例输入
6 4
1 7 3 2 5 6
1 2 4
1 3 5
2 4 1
3 5 2
3 6 1
2 5
4 6
6 4
5 6
样例输出
35
16
26
13
样例说明
　　对于第一条路线，小R会经过2->1->3->5。其中在城市2处以7的价格购买4单位粮食，到城市1时全部吃完，并用1的价格购买7单位粮食，然后到达终点。
评测用例规模与约定
　　前10%的评测用例满足：n, m ≤ 20, wi ≤ 20；
　　前30%的评测用例满足：n, m ≤ 200；
　　另有40%的评测用例满足：一个城市至多与其它两个城市相连。
　　所有评测用例都满足：1 ≤ n, m ≤ 105，1 ≤ wi ≤ 106，1 ≤ e ≤ 10000。
【题目分析】
题目解析开来其实模型很简单——给定一棵树，树上有点权也有边权。一次查询其实是在si和ti的路径上，找一个以si为首元素
的点权下降序列，直到ti。这条路径的权值是这个下降序列每两个相邻元素间的路径乘以左边元素的点权的总和。
由这个我们可以直接得到一个朴素算法——首先找出si到ti之间的路径，从ti开始，找到这条路径上的最小点，这个点到终点的
路径乘以点权，然后将终点赋值为最小点，依次累加求和。
找到si到ti之间的路径、找到路径上面的最小点，都可以用树链剖分和LinkCutTree做。这样的做法写起来很简单，但是极端情况
下复杂度很高，经过验证，可以通过50%的数据。

好了，现在起码有一个对拍的程序了…………

题目中有这样一句话——一个城市至多与其它两个城市相连——这是一条链啊！
好吧，我们来想一想这个题目放在链上怎么做。
假如起点终点分别是x与y
在x后面，第一个小于x的点，记为next[x]，这个可以通过单调栈的形式找到。
实际上，x到y所经过的点，一定是一遍又一遍地走next，直到一个点t，next[t]在y的后面
可以看出，这个由next所构成的链表，它的形式是一个森林
把x看做是next[x]的一个儿子，边长看做是w[x]*route(x,next[x])，在一条链上解决这个问题，可以抽象为先找到一个t，next[t]
在y的后面，然后求解x到t上，这个next构成的树的路径长，再加上t到y的距离*w[t]。
在一个链上可以这么做，然而原题中的形式，一棵树，可以看做是多个链的交集。
在树上，最简单的能够抽取出来的链就是子节点到祖先节点。
因此我们还可以考虑在这棵树上这么做——
原树，我们设它是tree1，现在对于tree1上的节点x，我们寻找x的祖先中，第一个比x小的节点，记为f2[x]，这个求法依旧是单调栈，只
不过要维护深搜序的单调栈，并且这个单调栈需要回溯。可以证明，单调栈中每个元素出栈入栈的次数和跟边长是线性关系。这个由f2[x]
构成的森林，设为tree2，x到f2[x]的边长，依旧如上文所述。
现在，如果一个询问是A到B，那么势必会经过一个点C，C是A到B的LCA。
那么，用一个LinkCutTree维护tree2，我们可以求出A到C之间一部分的答案，假设求得的路径是A到D。显然，D一定是A到C之间的最小点。
接下来需要求D到B的答案。D到B的答案可以划分为两个部分。一个部分是E，E在C和B之间，且D到E的路径中，没有比D还要小的点（除了E），那
么这段距离的长度是w[D]*route(D,E)，通过维护tree1的LinkCutTree，这个路径长度很容易求得。那么这个E要怎么找呢？
事实上，这个E具有二分性——对于C到B上的每一个点T，C到T之间的点权最小值一定单调不升。通过这样的性质我们可以找到这个E，利用LinkCutTree
同样能做到。
现在麻烦的是E到B的答案，可以发现一点——从根到每个叶子节点会有很多链，E和B一定会出现在一条链上。这样我们又可以用处理链的方式来处理
这两个点。只是这条链是动态的，这不就是LinkCutTree的Link和Cut操作么！
至此，题目就解决了，要维护两遍单调栈和三个LinkCutTree，真是醉了……

值得一提的是，这个破玩意有100000个点，深搜递归可能会爆栈，因此手动模拟了递归……*/

#include <iostream>
#include <cstdio> 
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std; 
const int maxn=1e5+2;
int w[maxn],fa[maxn],vis[maxn];
struct Edge{
	int to;
	int e;
};
vector<Edge> tr[maxn];
int s,t;
void bfs(){
	queue<int> Q;
	fa[s]=0;
	vis[s]=true;
	Q.push(s);
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		for(int i=0;i<tr[u].size();i++){
			int v=tr[u][i].to;
			if(!vis[v]){
				vis[v]=true;
				fa[v]=u;
				if(v==t) break;
				Q.push(v);
			}
		}
		if(vis[t]) break;
	}
}
void cal(){
	vector<Edge> path;
	int now=t;
	while(now!=s){
		int pre=fa[now];
		for(int i=0;i<tr[pre].size();i++){
			if(tr[pre][i].to==now){
				path.push_back(tr[pre][i]);
				break;
			}
		}
		now=pre;
	}
	long long ans=0;
	now=s;
	int MIN=0x3f3f3f3f;
	for(int i=path.size()-1;i>=0;i--){
		MIN=min(MIN,w[now]);
		ans+=(long long)MIN*path[i].e;
		now=path[i].to;
	}
	printf("%lld\n",ans);
}
int main(){ 
	int n,m;
	while(scanf("%d %d",&n,&m)==2){
		for(int i=1;i<=n;i++){
			scanf("%d",&w[i]);
			tr[i].clear();
		} 
		for(int i=1;i<n;i++){
			int a,b,e;
			scanf("%d %d %d",&a,&b,&e);
			tr[a].push_back((Edge){b,e});
			tr[b].push_back((Edge){a,e});
		}
		while(m--){
			scanf("%d %d",&s,&t);
			memset(vis,false,sizeof(vis));
			bfs();
			cal();
		}
	} 
	return 0;
}

#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#define fa(x) tree[x].fa
#define l(x) tree[x].l
#define r(x) tree[x].r
#define sum(x) tree[x].sum
#define size(x) tree[x].size
#define elen(x) tree[x].elen
#define Min(x) tree[x].Min
#define data(x) tree[x].data

using std::max;
using std::min;
using std::vector;

int e[200010], v[100010], next[200010],len[200010];
int n, m,cnt = 0;
vector<int> si[100010], num[100010];
long long res[100010];

struct treenode
{
	int fa, l, r;
	long long data, elen,size;
	long long sum, wsum, Min;
} tree[400010];

inline void connect(int x, int y, int flow)
{
	next[++cnt] = v[x], v[x] = cnt, e[cnt] = y, len[cnt] = flow;
	next[++cnt] = v[y], v[y] = cnt, e[cnt] = x, len[cnt] = flow;
}

int top1, top2, s1[100010], s2[100010], w[100010];

struct StackFrame
{
	int r;
	int tmp;
	int pre;
} SysStack[100010];

int SysTop = 0;

inline void search(int r)
{
	fa(r) = 0;
	elen(r) = 0;
	size(r) = 1;
	data(r + n) = data(r) = w[r];
	SysStack[++SysTop].r = r, SysStack[SysTop].pre = 0, SysStack[SysTop].tmp = v[r];
	fa(r + n) = 0;
	s1[++top1] = r + n;
	while (SysTop != 0)
	{
		int i = SysStack[SysTop].r;
		int tmp = SysStack[SysTop].tmp;
		int pre = SysStack[SysTop].pre;
		if (tmp == 0)
		{
			top1--;
			size(i + n) = size(i);
			while (top2 != pre)
			{
				s1[++top1] = s2[top2--];
			}
			SysTop--;
			size(SysStack[SysTop].r) += size(i);
		}
		else
		{
			if (e[tmp] != fa(i))
			{
				SysStack[++SysTop].r = e[tmp];
				SysStack[SysTop].tmp = v[e[tmp]];
				SysStack[SysTop].pre = top2;
				fa(e[tmp]) = i;
				size(e[tmp]) = 1;
				elen(e[tmp]) = len[tmp];
				data(e[tmp]) = data(e[tmp] + n) = w[e[tmp]];
				while (top1 && w[e[tmp]] <= w[s1[top1] - n])
				{
					s2[++top2] = s1[top1--];
				}
				fa(e[tmp] + n) = s1[top1];
				s1[++top1] = e[tmp] + n;
				continue;
			}
		}
		SysStack[SysTop].tmp = next[SysStack[SysTop].tmp];
	}
}

inline void update(int x)
{
	if (x == 0)
		return;
	Min(x) = min(min(Min(l(x)), Min(r(x))), data(x));
	sum(x) = sum(l(x)) + sum(r(x)) + elen(x);
}

inline void right_rotate(int x)
{
	int tmp = r(x), y = fa(x);
	if (l(fa(y)) == y)
		l(fa(y)) = x;
	else
		if (r(fa(y)) == y)
			r(fa(y)) = x;
	fa(x) = fa(y), fa(tmp) = y, r(x) = y, fa(y) = x, l(y) = tmp;
	update(y);
}

inline void left_rotate(int x)
{
	int tmp = l(x), y = fa(x);
	if (l(fa(y)) == y)
		l(fa(y)) = x;
	else
		if (r(fa(y)) == y)
			r(fa(y)) = x;
	fa(x) = fa(y), fa(tmp) = y, l(x) = y, fa(y) = x, r(y) = tmp;
	update(y);
}

inline bool be_root(int x)
{
	return (l(fa(x)) != x && r(fa(x)) != x);
}

inline void splay(int x)
{
	if (x == 0) return;
	while (!be_root(x))
	{
		int y = fa(x), z = fa(y);
		if (be_root(y))
		{
			if (l(y) == x)
				right_rotate(x);
			else
				left_rotate(x);
			break;
		}
		if (l(z) == y)
		{
			if (l(y) == x)
				right_rotate(y), right_rotate(x);
			else
				left_rotate(x), right_rotate(x);
		}
		else
		{
			if (l(y) == x)
				right_rotate(x), left_rotate(x);
			else
				left_rotate(y), left_rotate(x);
		}
	}
	update(x);
}


inline void access(int x)
{
	for (int y = 0; x; x = fa(x))
	{
		splay(x);
		r(x) = y, update(y = x);
	}
}

inline long long ask_road(int x, int y)
{
	if (x == 0 || y == 0)
		return 0;
	access(y);
	for (y = 0;; x = fa(x))
	{
		splay(x);
		if (fa(x) == 0)
			return sum(r(x)) + sum(y);
		r(x) = y, update(y = x);
	}
}

inline int left_adj(int x)
{
	for (int tmp = x; l(x); x = l(x));
	return x;
}

inline int right_adj(int x)
{
	for (int tmp = x; r(x); x = r(x));
	return x;
}

inline int find_LCA(int x, int y)
{
	access(y);
	int tmp = x;
	int LCA = 1;
	for (int pre = 0;; tmp = fa(tmp))
	{
		splay(tmp);
		if (fa(tmp) == 0)
		{
			LCA = tmp;
			break;
		}
		r(tmp) = pre, update(pre = tmp);
	}
	return LCA;
}

inline long long query(int ord, int x, int y)
{
	access(y);
	int tmp = x;
	int LCA = 1;
	for (int pre = 0;; tmp = fa(tmp))
	{
		splay(tmp);
		if (fa(tmp) == 0)
		{
			LCA = tmp;
			break;
		}
		r(tmp) = pre, update(pre = tmp);
	}
	long long d = size(LCA);
	access(x + n);
	splay(x + n);
	tmp = x + n;
	int pre = 0;
	while (tmp != 0)
	{
		pre = tmp;
		if (size(tmp) < d)
		{
			tmp = l(tmp);
		}
		else if (size(tmp) > d)
		{
			tmp = r(tmp);
		}
		else
		{
			break;
		}
	}
	splay(pre);
	if (size(pre) > d)
		splay(pre = left_adj(r(pre)));
	long long ans = 0;
	ans += sum(r(pre));
	int left = pre - n;
	d = data(pre - n);
	if (y == LCA)
		return ans + d * ask_road(left, LCA);
	//splay(LCA);r(LCA) = 0, update(LCA);
	access(LCA);
	//TODO：在另一链找拐点
	pre = 0;
	splay(y);
	tmp = y;
	while (tmp != 0)
	{
		pre = tmp;
		//int mid = Min(l(tmp));
		if (Min(l(tmp)) <= d)
		{
			tmp = l(tmp);
		}
		else if (data(tmp) <= d)
		{
			break;
		}
		else if (Min(r(tmp)) <= d)
		{
			tmp = r(tmp);
		}
		else
		{
			break;
		}
	}
	int right = pre;
	ans += d * ask_road(left, right);
	access(y);
	splay(pre);
	access(tmp = right_adj(l(pre)));
	splay(pre);
	tmp = pre;
	while (tmp != 0)
	{
		//pre = tmp;
		if (Min(l(tmp)) == Min(tmp))
		{
			tmp = l(tmp);
		}
		else if (Min(tmp) == data(tmp))
		{
			break;
		}
		else
		{
			tmp = r(tmp);
		}
	}
	splay(tmp);
	ans += data(tmp) * sum(r(tmp));
	num[tmp].push_back(ord);
	si[tmp].push_back(pre);
	return ans;
}

bool hash[100010];

inline void search(int r, int p)
{
	SysStack[++SysTop].r = r;
	SysStack[SysTop].pre = top2;
	SysStack[SysTop].tmp = v[r];
	hash[r] = true;
	while (top1 && w[r] < w[s1[top1]])
	{
		s2[++top2] = s1[top1--];
		fa(s2[top2] + 2 * n) = r + n + n;
		elen(s2[top2] + 2 * n) = data(s2[top2]) * ask_road(s2[top2], r);
	}
	s1[++top1] = r;
	while (SysTop != 0)
	{
		int i = SysStack[SysTop].r;
		int pre = SysStack[SysTop].pre;
		int tmp = SysStack[SysTop].tmp;
		if (tmp == 0)
		{
			SysTop--;
			top1--;
			//access(i + n + n);
			while (top2 != pre)
			{
				s1[++top1] = s2[top2--];
				int x = s1[top1] + n + n;
				access(x);
				splay(x);
				fa(l(x)) = fa(x), l(x) = 0, elen(x) = 0, update(x);
			}
		}
		else
		{
			int j = e[tmp];
			if (hash[j] == 0)
			{
				int pre = top2;
				while (top1 && w[j] < w[s1[top1]])
				{
					s2[++top2] = s1[top1--];
					access(s2[top2] + n + n);
					splay(s2[top2] + n + n);
					fa(s2[top2] + 2 * n) = j + n + n;
					elen(s2[top2] + 2 * n) = data(s2[top2]) * ask_road(s2[top2], j);
				}
				s1[++top1] = j;
				for (vector<int>::iterator it1 = si[j].begin(), it2 = num[j].begin(); it1 != si[j].end(); it1++, it2++)
				{
					int pre = *it1;
					int ord = *it2;
					access(pre + n + n);
					splay(j + n + n);
					res[ord] += sum(r(j + n + n));
				}
				SysStack[++SysTop].r = j;
				hash[j] = true;
				SysStack[SysTop].tmp = v[j];
				SysStack[SysTop].pre = pre;
				continue;
			}
		}
		SysStack[SysTop].tmp = next[SysStack[SysTop].tmp];
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", w + i);
	}
	Min(0) = 0x7fffffff;
	for (int i = 1; i <= n - 1; i++)
	{
		int u, v, e;
		scanf("%d%d%d", &u, &v, &e);
		connect(u, v, e);
	}
	search(1);
	for (int i = 1; i <= n; i++)
	{
		if (fa(i + n) != 0)
		{
			elen(i + n) = data(i + n) * ask_road(i, fa(i + n) - n);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		res[i] = query(i, u, v);
	}
	search(1, 0);
	for (int i = 1; i <= m; i++)
	{
		printf("%lld\n", res[i]);
	}
	return 0;
}