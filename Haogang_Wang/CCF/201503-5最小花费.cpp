/*http://blog.csdn.net/buaa1306ksy/article/details/49078801
��������
����C������n�����С���n-1��˫���·��ÿ����·�����������У�������������֮���ܻ��ൽ�СR����C�����У������滮��m�����е�·�ߣ���i������·�ߵ������si���յ���ti�������й����У�СRÿ����һ��λ���ȵ�·��Ҫ��һ��λ��ʳ�C����ʳ��ֻ���ڸ����������򵽣����Ҳ�ͬ���е�ʳ��۸���ܲ�ͬ��
����Ȼ����СR��ϣ����������Ϊ�˹���ϵͼ۵���ʳ����Զ·��������ܻ�ѡ�������·�ߡ����ڣ��������СR�滮��ÿ������·�ߵ���С�����Ƕ��١�
�����ʽ
������һ�а���2������n��m��
�����ڶ��а���n����������i������wi��ʾ����i��ʳ��۸�
����������n-1�У�ÿ�а���3������u, v, e����ʾ����u�ͳ���v֮����һ����Ϊe��˫���·��
����������m�У�ÿ�а���2������si��ti���ֱ��ʾһ������·�ߵ������յ㡣
�����ʽ
�������m�У��ֱ����ÿһ�����з�������С���ѡ�
��������
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
�������
35
16
26
13
����˵��
�������ڵ�һ��·�ߣ�СR�ᾭ��2->1->3->5�������ڳ���2����7�ļ۸���4��λ��ʳ��������1ʱȫ�����꣬����1�ļ۸���7��λ��ʳ��Ȼ�󵽴��յ㡣
����������ģ��Լ��
����ǰ10%�������������㣺n, m �� 20, wi �� 20��
����ǰ30%�������������㣺n, m �� 200��
��������40%�������������㣺һ������������������������������
���������������������㣺1 �� n, m �� 105��1 �� wi �� 106��1 �� e �� 10000��
����Ŀ������
��Ŀ����������ʵģ�ͺܼ򵥡�������һ�����������е�ȨҲ�б�Ȩ��һ�β�ѯ��ʵ����si��ti��·���ϣ���һ����siΪ��Ԫ��
�ĵ�Ȩ�½����У�ֱ��ti������·����Ȩֵ������½�����ÿ��������Ԫ�ؼ��·���������Ԫ�صĵ�Ȩ���ܺ͡�
��������ǿ���ֱ�ӵõ�һ�������㷨���������ҳ�si��ti֮���·������ti��ʼ���ҵ�����·���ϵ���С�㣬����㵽�յ��
·�����Ե�Ȩ��Ȼ���յ㸳ֵΪ��С�㣬�����ۼ���͡�
�ҵ�si��ti֮���·�����ҵ�·���������С�㣬�������������ʷֺ�LinkCutTree��������������д�����ܼ򵥣����Ǽ������
�¸��ӶȺܸߣ�������֤������ͨ��50%�����ݡ�

���ˣ�����������һ�����ĵĳ����ˡ�������

��Ŀ��������һ�仰����һ������������������������������������һ��������
�ðɣ���������һ�������Ŀ����������ô����
��������յ�ֱ���x��y
��x���棬��һ��С��x�ĵ㣬��Ϊnext[x]���������ͨ������ջ����ʽ�ҵ���
ʵ���ϣ�x��y�������ĵ㣬һ����һ����һ�����next��ֱ��һ����t��next[t]��y�ĺ���
���Կ����������next�����ɵ�����������ʽ��һ��ɭ��
��x������next[x]��һ�����ӣ��߳�������w[x]*route(x,next[x])����һ�����Ͻ��������⣬���Գ���Ϊ���ҵ�һ��t��next[t]
��y�ĺ��棬Ȼ�����x��t�ϣ����next���ɵ�����·�������ټ���t��y�ľ���*w[t]��
��һ�����Ͽ�����ô����Ȼ��ԭ���е���ʽ��һ���������Կ����Ƕ�����Ľ�����
�����ϣ���򵥵��ܹ���ȡ�������������ӽڵ㵽���Ƚڵ㡣
������ǻ����Կ��������������ô������
ԭ��������������tree1�����ڶ���tree1�ϵĽڵ�x������Ѱ��x�������У���һ����xС�Ľڵ㣬��Ϊf2[x]������������ǵ���ջ��ֻ
����Ҫά��������ĵ���ջ�������������ջ��Ҫ���ݡ�����֤��������ջ��ÿ��Ԫ�س�ջ��ջ�Ĵ����͸��߳������Թ�ϵ�������f2[x]
���ɵ�ɭ�֣���Ϊtree2��x��f2[x]�ı߳�������������������
���ڣ����һ��ѯ����A��B����ô�Ʊػᾭ��һ����C��C��A��B��LCA��
��ô����һ��LinkCutTreeά��tree2�����ǿ������A��C֮��һ���ֵĴ𰸣�������õ�·����A��D����Ȼ��Dһ����A��C֮�����С�㡣
��������Ҫ��D��B�Ĵ𰸡�D��B�Ĵ𰸿��Ի���Ϊ�������֡�һ��������E��E��C��B֮�䣬��D��E��·���У�û�б�D��ҪС�ĵ㣨����E������
ô��ξ���ĳ�����w[D]*route(D,E)��ͨ��ά��tree1��LinkCutTree�����·�����Ⱥ�������á���ô���EҪ��ô���أ�
��ʵ�ϣ����E���ж����ԡ�������C��B�ϵ�ÿһ����T��C��T֮��ĵ�Ȩ��Сֵһ������������ͨ���������������ǿ����ҵ����E������LinkCutTree
ͬ����������
�����鷳����E��B�Ĵ𰸣����Է���һ�㡪���Ӹ���ÿ��Ҷ�ӽڵ���кܶ�����E��Bһ���������һ�����ϡ����������ֿ����ô������ķ�ʽ������
�������㡣ֻ���������Ƕ�̬�ģ��ⲻ����LinkCutTree��Link��Cut����ô��
���ˣ���Ŀ�ͽ���ˣ�Ҫά�����鵥��ջ������LinkCutTree���������ˡ���

ֵ��һ����ǣ������������100000���㣬���ѵݹ���ܻᱬջ������ֶ�ģ���˵ݹ顭��*/

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
	//TODO������һ���ҹյ�
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