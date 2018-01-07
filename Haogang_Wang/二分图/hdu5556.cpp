#include <bits/stdc++.h>
#define MEM(a,b) memset((a),(b),sizeof(a))
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 10005;
const int maxp = 2000005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

bool vis[maxn];
int flag[maxn];
vector<int> G[maxn];
bool dfs(int u) {
    for(int i=(int)G[u].size()-1;i>=0;i--) {
        int &v=G[u][i];
        if(vis[v]) continue;
        vis[v]=true;
        if(!flag[v]||dfs(flag[v])) {
            flag[v]=u;
            return true;
        }
    }
    return false;
}
int dx[4]={-1,1,0,0};
int dy[4]={0,0,1,-1};
char s[12];
int mp[12][12];
int anc[12],acnt;
vector<int> fs[11];
int oc[12][12];
int n,m;
int check(int st) {
    int ret=0;
    for(int i=0;i<acnt;i++) {
        if(st&(1<<i)) {
            for(int j=(int)fs[i].size()-1;j>=0;j--) {
                int x=fs[i][j]/m,y=fs[i][j]%m;
                oc[x][y]=1;
            }
            ret++;
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(oc[i][j]==1) {
                for(int k=0;k<4;k++) {
                    int nx=i+dx[k],ny=j+dy[k];
                    if(nx<0||nx>=n||ny<0||ny>=m) continue;
                    if(oc[nx][ny]==2) continue;
                    if(!oc[nx][ny]) oc[nx][ny]=2;
                    else if(mp[nx][ny]==mp[i][j]) continue;
                    else return -1;
                }
            }
        }
    }
    return ret;
}
int Hungary()
{
    int res = 0;
    memset(flag, 0, sizeof(flag));
    for(int i = 0; i < n*m; i++)
    {
        memset(vis, 0, sizeof(vis));
        res += dfs(i);
    }
    return res;
}
int main() {
    int T;
    scanf("%d",&T);
    for (int cas = 1; cas <= T; ++cas) {
        scanf("%d%d",&n,&m);
        memset(anc, -1, sizeof(anc));
        memset(mp,0, sizeof(mp));
        acnt=0;
        for (int i = 0; i < n; ++i) {
            scanf("%s",s);
            for (int j = 0; j < m; ++j) {
                if(s[j]!='.') {
                    if(anc[s[j]-'0']==-1) fs[acnt].clear(),anc[s[j]-'0']=acnt++;
                    mp[i][j]=anc[s[j]-'0'];
                    fs[mp[i][j]].push_back(i*m+j);
                } else mp[i][j]=10;
            }
        }
        int lim=(1<<acnt),ans=0;
        for(int st=0;st<lim;st++) {
            memset(oc,false, sizeof(oc));
            int num=check(st);
            if(num==-1) continue;
            for(int i=0;i<n*m;i++) G[i].clear();
            int all=0;
            for(int i = 0; i < n; i++)
                for(int j = 0; j < m; j++)
                {
                    if(!oc[i][j] && mp[i][j] == 10) all++;
                    if(oc[i][j] || mp[i][j] != 10) continue;
                    for(int k = 0; k < 4; k++)
                    {
                        int tx = i+dx[k];
                        int ty = j+dy[k];
                        if(tx >= 0 && tx < n && ty >= 0 && ty < m && !oc[tx][ty] && mp[tx][ty] == 10)
                        {
                            G[i*m+j].push_back(tx*m+ty);
                        }
                    }
                }
            int tmp = Hungary();
            ans = max(ans, num+(all-tmp/2));
        }
        printf("Case #%d: %d\n",cas,ans);
    }
    return 0;
}
