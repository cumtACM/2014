//  POJ-1741
//  题意：找出树中有多少点对，满足dis（u，v）<K
//  思路：点分治模板题
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=10010;
int N,K;
int ans,root,Max;
struct node {
    int v,next,w;
}edge[maxn<<1];
int head[maxn],tot;
int size[maxn];//树的大小
int maxv[maxn];//最大孩子节点的size
int vis[maxn];
int dis[maxn];
int num;
void init() {
    tot=0;
    ans=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}
void add_edge(int u,int v,int w) {
    edge[tot].v=v;
    edge[tot].w=w;
    edge[tot].next=head[u];
    head[u]=tot++;
}
//处理子树的大小
void dfs_size(int u,int f) {
    size[u]=1;
    maxv[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].v;
        if(v==f||vis[v])continue;
        dfs_size(v,u);
        size[u]+=size[v];
        if(size[v]>maxv[u])maxv[u]=size[v];
    }
}
//找重心
void dfs_root(int r,int u,int f) {
    if(size[r]-size[u]>maxv[u])//size[r]-size[u]是u上面部分的树的尺寸，跟u的最大孩子比，找到最大孩子的最小差值节点
        maxv[u]=size[r]-size[u];
    if(maxv[u]<Max)Max=maxv[u],root=u;
    for(int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].v;
        if(v==f||vis[v])continue;
        dfs_root(r,v,u);
    }
}
//求每个点离重心的距离
void dfs_dist(int u,int d,int f) {
    dis[num++]=d;
    for(int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].v;
        if(v!=f&&!vis[v])
            dfs_dist(v,d+edge[i].w,u);
    }
}
//计算以u为根的子树中有多少点对的距离小于等于K
int cal(int u,int d) {
    int ret=0;
    num=0;
    dfs_dist(u,d,0);
    sort(dis,dis+num);
    int i=0,j=num-1;
    while(i<j) {
        while(dis[i]+dis[j]>K&&i<j)j--;
        ret+=j-i;
        i++;
    }
    return ret;
}
void dfs(int u) {
    Max=N;
    dfs_size(u,0);
    dfs_root(u,u,0);
    ans+=cal(root,0);
    vis[root]=1;
    for(int i=head[root];i!=-1;i=edge[i].next) {
        int v=edge[i].v;
        if(!vis[v]) {
            ans-=cal(v,edge[i].w);
            dfs(v);
        }
    }
}
int main() {
    while(scanf("%d%d",&N,&K)!=EOF) {
        if(!N&&!K)break;
        int u,v,w;
        init();
        for(int i=1;i<N;i++) {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        dfs(1);
        printf("%d\n",ans);
    }
    return 0;
}
