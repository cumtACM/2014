/*
图是一个完全二叉树（不一定满），a[i]是(i>>1)和i之间边的权值。询问给出起点x，和路费y，每一种路径的收益是
y-路径长度，问所有可行（收益为正）的方案的总收益。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int,int> pii;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,b,a) for(int i=(b);i>=(a);i--)

const int maxn=1000005;
const int INF=0x3f3f3f3f;
const lolo inf=0x3f3f3f3f3f3f3f3f;
template <class T>
void read(T& x) {
    x=(T)0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    do {x=(T)(x*10+c-'0');c=getchar();}while(c>='0'&&c<='9');
}
vector<int> G[maxn];
vector<lolo> sum[maxn];
int a[maxn];

int main() {
    int n,m,x,y;
    read(n);read(m);
    FOR(i,2,n) read(a[i]);
    FOR(i,1,n) G[i].push_back(0),sum[i].push_back(0);
    IFOR(i,n,2) {
        // 将到子节点的路径长度全部保存。
        for(vector<int>::iterator p=G[i].begin();p!=G[i].end();p++) {   // 每层n空间,空间复杂度nlogn;
            G[i>>1].push_back(*p+a[i]);
        }
    }
    FOR(i,1,n) {
        // 计算前缀和
        sort(G[i].begin(),G[i].end());
        int sz=G[i].size();
        FOR(j,1,sz-1) {
            sum[i].push_back(sum[i][j-1]+G[i][j]);
        }
        G[i].push_back(INF);sum[i].push_back(inf);
    }
    while(m--) {
        read(x);read(y);
        int p=0,ny=y,cnt=0;
        lolo fans=0;
        vector<int>::iterator it=lower_bound(G[x].begin(),G[x].end(),y);  // 向下走的方案
        int z=it-G[x].begin();
        cnt+=z;
        fans+=sum[x][z-1];
        // 每次向上走一步后走起点不在的另一棵子树
        while(x>1) {
            ny-=a[x];p+=a[x];
            if(ny<=0) break;
            cnt++;          // 只走到这个父节点也是一种方案。
            fans+=p;
            int nx=(x&1)?x-1:x+1;
            if(nx<=n&&ny-a[nx]>0) {
                it = lower_bound(G[nx].begin(), G[nx].end(), ny - a[nx]);
                z = it - G[nx].begin();
                if (z > 0) {
                    cnt += z;
                    fans += 1LL * z * (p + a[nx]) + sum[nx][z - 1];
                }
            }
            x>>=1;
        }
        printf("%lld\n",1LL*cnt*y-fans);
    }
    return 0;
}
