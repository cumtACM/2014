/*
 Our Journey of Xian Ends
 我们其实只有两种路线选择：西安->虹桥->青岛->浦东或者西安->浦东、虹桥->青岛->虹桥、浦东
 用网络流来做，经过虹桥、青岛的流肯定为2，浦东的为1
*/
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 10005;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

map<string, int> mp;
struct Edge{
    int from,to,cost,flow,cap;
    int nxt;
};
char str[20];
int n;
string scf() {
    scanf("%s",str);
    return str;
}
struct MCMF {
    int n,m;
    Edge edges[maxn<<3];
    int head[maxn<<1];
    bool inq[maxn<<1];
    int d[maxn<<1],p[maxn<<1],a[maxn<<1];
    void Init(int n) {
        this->n=n;
        memset(head,-1, sizeof(int)*n);
        m=0;
    }
    void AddEdge(int from,int to,int cost,int cap,int flow=0) {
        edges[m]=(Edge){from,to,cost,flow,cap,head[from]};
        head[from]=m++;
        edges[m]=(Edge){to,from,-cost,0,0,head[to]};
        head[to]=m++;
    }
    bool BellmanFord(int s,int t,int& flow,int& cost){
        for(int i=0;i<n;i++) d[i]=INF,inq[i]=false;
        d[s]=0;inq[s]=true;p[s]=0;a[s]=INF;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()){
            int u=Q.front();Q.pop();
            inq[u]=false;
            for(int i=head[u];i!=-1;i=edges[i].nxt){
                Edge& e=edges[i];
                if(e.cap>e.flow&&d[e.to]>d[u]+e.cost){
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=i;
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to]){
                        Q.push(e.to);
                        inq[e.to]=true;
                    }
                }
            }
        }
        if(d[t]==INF) return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while(u!=s){
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }
    int Mincost(int s,int t,int &flow){
        int cost=0;
        flow=0;
        while(BellmanFord(s,t,flow,cost));
        return cost;
    }
}solve1;
int c[maxn];
string fr[maxn],to[maxn];
int main() {
    int T,a,b;
    scanf("%d",&T);
    while(T--) {
        mp.clear();
        int cnt=4;
        mp["Xian"]=1;
        mp["Qingdao"]=2;
        mp["Hongqiao"]=3;
        mp["Pudong"]=4;
        scanf("%d",&n);
        FOR(i, 0, n-1) {
            fr[i]=scf();to[i]=scf();
            scanf("%d",c+i);
            if(!mp.count(fr[i])) {
                mp[fr[i]]=++cnt;
            }
            if(!mp.count(to[i])) {
                mp[to[i]]=++cnt;
            }
        }
        solve1.Init((cnt+1)<<1);
        FOR(i, 0, n-1) {
            a=mp[fr[i]];
            b=mp[to[i]];
            solve1.AddEdge(a+cnt, b, c[i], INF);
            solve1.AddEdge(b+cnt, a, c[i], INF);
        }
        FOR(i,5,cnt) {
            solve1.AddEdge(i,i+cnt,0,1);
        }
        solve1.AddEdge(0, 4, 0, 1);
        solve1.AddEdge(4, 4+cnt, 0, 1);
        solve1.AddEdge(0, 3, 0, 2);
        solve1.AddEdge(3, 3+cnt, 0, 2);
        solve1.AddEdge(2, 2+cnt, 0, 2);
        solve1.AddEdge(2+cnt, cnt<<1|1, 0, 2);
        solve1.AddEdge(1, 1+cnt, 0, 1);
        solve1.AddEdge(1+cnt, cnt<<1|1, 0, 1);
        int flow1;
        int cost1=solve1.Mincost(0, cnt<<1|1, flow1);
        if(flow1<3) {
            puts("-1");
        } else {
            int ans=INF;
            ans=min(ans,cost1);
            printf("%d\n",ans);
        }
    }
    return 0;
}
