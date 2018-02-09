/*
 CCPC Final 2017 J
 不等式联立求可行解，全部处理成>=后建图求最长距离，或者
 处理成<=求最短距离，有负环则无解。
*/
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 2005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9 + 7;

struct Edge {
    int to,cost,nxt;
}edge[maxn<<2];
int n;
int head[maxn];
int cnt;
lolo dt[maxn];
int ind[maxn];
bool inq[maxn];
void init() {
    cnt=0;
    memset(head+1,-1, sizeof(int)*n);
}
void addEdge(int from,int to,int cost) {
    edge[cnt].to=to;edge[cnt].cost=cost;edge[cnt].nxt=head[from];
    head[from]=cnt++;
}
bool spfa(int u) {
    for(int i=1;i<=n;i++) {
        inq[i]=false;
        dt[i]=-inf;
        ind[i]=0;
    }
    queue<int> Q;
    Q.push(u);
    dt[u]=0;
    inq[u]=true;
    while(!Q.empty()) {
        int now=Q.front();Q.pop();
        if(++ind[now]>=n) return false;
        inq[now]=false;
        for(int i=head[now];i!=-1;i=edge[i].nxt) {
            int &v=edge[i].to;
            int &c=edge[i].cost;
            if(dt[v]<dt[now]+c) {
                dt[v]=dt[now]+c;
                if(!inq[v]) {
                    inq[v]=true;
                    Q.push(v);
                }
            }
        }
    }
    return true;
}
int main() {
//    freopen("../in.txt","r",stdin);
    int T,m,x,a,b,c,d;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++) {
        scanf("%d%d%d",&n,&m,&x);
        init();
        for(int i=1;i<n;i++) addEdge(i,i+1,1);
        while(m--) {
            scanf("%d%d%d%d",&a,&b,&c,&d);
            if(a==b) {
                if(c==d) {
                    addEdge(a,c,x);       // dt[c]-dt[a]>=x;
                    addEdge(c,a,-x);      // dt[a]-dt[c]>=-x;
                } else {
                    addEdge(a,d,x+1);      // dt[d]-dt[a]>=x+1
                    addEdge(c,a,-x+1);     // dt[a]-dt[c]>=-x+1
                }
            } else {
                if(c==d) {
                    addEdge(a,d,x+1);      // dt[d]-dt[a]>=x+1
                    addEdge(d,b,-x+1);     // dt[b]-dt[d]>=-x+1
                } else {
                    addEdge(a,d,x+1);      // dt[d]-dt[a]>=x+1
                    if(c>b) addEdge(c,b,-x+1);
                }
            }
        }
        printf("Case #%d:",cas);
        if(spfa(1)) {
            for(int i=2;i<=n;i++) {
                printf(" %lld",dt[i]-dt[i-1]);
            }
            putchar('\n');
        } else puts(" IMPOSSIBLE");
    }
    return 0;
}
