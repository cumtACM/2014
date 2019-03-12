/*
 * 树分治+高维前缀和hdu5977
 * 给一棵节点数为n，节点种类为k的无根树，问其中有多少种不同
 * 的简单路径，可以满足路径上经过所有k种类型的点？（a->b与
 * b->a算作两条路径，起点与终点也可以相同）
 * 与POJ-1741的区别就在于后者是求长度小于等于k的路径数目，
 * 而这道题是求经过所有种类点的路径，状压一下，也就是求状态
 * 为(1<<k)-1的路径数目
 * 我们枚举每一个其中的每一个数x，想找到数组中有多少数和x的
 * 或运算的和为(1<<k)-1，也就是找到可以包含((1<<k)-1)^x
 * 的数，这时候可以反向考虑，先枚举x的子集，然后再与(1<<k)-1
 * 进行异或运算，就可以找到了所有的情况。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 50005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0;
    T flag=1;
    char c;
    do {
        c = (char)getchar();
        if(c=='-') break;
    } while (c < '0' || c > '9');
    if(c=='-')
        c='0',flag=-1;
    do {
        x = x * 10 + c - '0';
        c = (char)getchar();
    } while (c >= '0' && c <= '9');
    x*=flag;
}

int n,k,root,Max;
lolo ans;
vector<int> G[maxn];
vector<int> sta;
bool vis[maxn];
int Hash[1100];
int sz[maxn],maxv[maxn],a[maxn];
void init() {
    memset(vis,false, sizeof(bool)*(n+1));
    for(int i=0;i<=n;i++) G[i].clear();
}
void dfs_size(int u,int pre) {      // 求出每个子树的大小，以及每个节点的最大儿子
    sz[u]=1;
    maxv[u]=0;
    int sze=G[u].size();
    for(int i=0;i<sze;i++) {
        int &v = G[u][i];
        if (v == pre || vis[v]) continue;
        dfs_size(v, u);
        sz[u] += sz[v];
        maxv[u] = max(maxv[u], sz[v]);
    }
}
void dfs_root(int r,int u,int pre) {      // 找出以u为根的子树的重心
    maxv[u]=max(maxv[u],sz[r]-sz[u]);
    if(Max>maxv[u]) {
        Max=maxv[u];
        root=u;
    }
    int sze = G[u].size();
    for (int i = 0; i < sze; i++) {
        int &v = G[u][i];
        if (v == pre || vis[v]) continue;
        dfs_root(r, v, u);
    }
}
void dfs_sta(int u,int pre,int s) {
    sta.push_back(s);
    int sze = G[u].size();
    for (int i = 0; i < sze; i++) {
        int v = G[u][i];
        if (v == pre || vis[v]) continue;
        dfs_sta(v, u, s | (1 << a[v]));

    }
}
lolo cal(int u, int s) {
    lolo res = 0;
    sta.clear(); dfs_sta(u, -1, s);
    memset(Hash, 0, sizeof(Hash));
    int sze = sta.size();
    for (int i = 0; i < sze; i++) Hash[sta[i]]++;
    for (int i = 0; i < sze; i++) {
        Hash[sta[i]]--;
        res += Hash[(1 << k) - 1];
        for (int s0 = sta[i]; s0; s0 = (s0 - 1) & sta[i])
            res += Hash[((1 << k) - 1) ^ s0];
        Hash[sta[i]]++;
    }
    return res;
}
void dfs(int u) {
    Max = n;
    dfs_size(u, -1); dfs_root(u, u, -1);
    ans += cal(root, (1 << a[root]));
    vis[root] = true;
    int sze = G[root].size(), rt = root;
    for (int i = 0; i < sze; i++) {
        int v = G[rt][i];
        if (vis[v]) continue;
        ans -= cal(v, (1 << a[rt]) | (1 << a[v]));
        dfs(v);
    }
}
int main() {
    while(scanf("%d%d",&n,&k)!=EOF) {
        init();
        for(int i=1;i<=n;i++) read(a[i]),--a[i];
        int u,v;
        for(int i=1;i<n;i++) {
            read(u);read(v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        if(k==1) {
            printf("%lld\n",1LL*n*n);
            continue;
        }
        ans=0;
        dfs(1);
        printf("%lld\n",ans);
    }
    return 0;
}
