/*
做法1、
①统计每个点的度数
②入度<=sqrt(m)的分为第一类，入度>sqrt(m)的分为第二类
③对于第一类，暴力每个点，然后暴力这个点的任意两条边，再判断这两条边的另一个端点是否连接
因为m条边最多每条边遍历一次，然后暴力的点的入度<=sqrt(m)，所以复杂度约为O(msqrt(m))
④对于第二类，直接暴力任意三个点，判断这三个点是否构成环，因为这一类点的个数不会超过sqrt(m)个，所以复杂度约为O(sqrt(m)3)=O(msqrt(m))
⑤判断两个点是否连接可以用set，map和Hash都行,根据具体情况而行
这种做法建的是双向边，常数很大

更优的做法2、建有向边 复杂度为O(msqrt(n))
对所有边按照两端点的度数定向，度数小的往度数大的走，度数相同则按编号小到大走，这样定向后
可以保证是个有向无环图。
为什么呢，要想定向存在环，则这个环上的点度数必须相同，由于保证了编号从小到大走
所以是不可能存在环的。
这样定向同时还保证了每个点的出度不超过sqrt(n)，乍一眼看觉得应该是sqrt(m)的，仔细一想确实比这个低，不过不知道怎么证。
对于这道题，我们在求三元环的时候，统计一下每条边有多少对点能构成三元环，C(cnt,2)累计一下即可
*/

// 方法二
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = (int)1e5 + 5;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') { c = '0', flag = -1;}
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}

vector<pii> G[maxn];
int deg[maxn],X[maxn<<1],Y[maxn<<1];
int pos[maxn],rv[maxn],cnt[maxn<<1];
int main() {
    int n,m;
    while (scanf("%d%d",&n,&m)!=EOF) {
        FOR(i,1,n) G[i].clear(),deg[i]=pos[i]=rv[i]=0;;
        FOR(i,1,m) {
            read(X[i]);read(Y[i]);
            deg[X[i]]++;deg[Y[i]]++;
            cnt[i]=0;
        }
        FOR(i,1,m) {
            if(deg[X[i]]<deg[Y[i]]) G[X[i]].push_back(make_pair(Y[i],i));
            else if(deg[X[i]]>deg[Y[i]]) G[Y[i]].push_back(make_pair(X[i],i));
            else {
                if(X[i]<Y[i]) G[X[i]].push_back(make_pair(Y[i],i));
                else G[Y[i]].push_back(make_pair(X[i],i));
            }
        }
        FOR(i,1,m) {
            int &u=X[i],&v=Y[i];
            for(pii x:G[u]) pos[x.first]=x.second,rv[x.first]=i;
            for(pii x:G[v]) {
                if(rv[x.first]==i) {
                    ++cnt[i];
                    ++cnt[pos[x.first]];
                    ++cnt[x.second];
                }
            }
        }
        lolo ans=0;
        FOR(i,1,m) ans+=1LL*cnt[i]*(cnt[i]-1)>>1;
        printf("%lld\n",ans);
    }
    return 0;
}

// 方法一
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = (int)1e5 + 5;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') { c = '0', flag = -1;}
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}

vector<int> G[maxn];
set<lolo> g;
int deg[maxn];
int rv[maxn];
bool vis[maxn];
int main() {
//    freopen("../in.txt","r",stdin);
    int n,m;
    while (scanf("%d%d",&n,&m)!=EOF) {
        int sz=(int)sqrt(m);
        g.clear();
        FOR(i,1,n) G[i].clear(),deg[i]=rv[i]=0,vis[i]= false;
        FOR(i,1,m) {
            int u,v;
            read(u);read(v);
            deg[u]++;deg[v]++;
            G[u].push_back(v);G[v].push_back(u);
            if(u<v) swap(u,v);
            g.insert(1LL*u*maxn+v);
        }
        lolo ans=0;
        FOR(u,1,n) {
            vis[u]=true;
            for(int v:G[u]) rv[v]=u;
            for(int v:G[u]) {
                int cnt=0;
                if(vis[v]) continue;
                if(deg[v]<=sz) {
                    for(int vv:G[v]) {
                        if(rv[vv]==u) ++cnt;
                    }
                } else {
                    for(int vv:G[u]) {
                        if(vv==v) continue;
                        lolo tmp;
                        if(vv<v) tmp=1LL*v*maxn+vv;
                        else tmp=1LL*vv*maxn+v;
                        if(g.find(tmp)!=g.end()) ++cnt;
                    }
                }
                ans+=1LL*cnt*(cnt-1)>>1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
