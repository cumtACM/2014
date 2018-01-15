#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <unordered_map>
#include <set>
#include <ctime>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 200005;
const int maxm = 200005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
char str[1100];
string scf() {
    scanf("%s",str);
    return str;
}
template<class T>
inline void out(T x) {
    if(x>9) out(x/10);
    x=x%10;
    putchar('0'+x);
}
const int MAXNODE=1000;
const int SIGMA_SIZE=80;
int n,K,cnt;
char v[110],s[22][22];
double p[110];
int idc[130];
double dp[MAXNODE][105];
bool vis[MAXNODE][105];
struct AhoCorasickAutomata {
    int ch[MAXNODE][SIGMA_SIZE];
    int f[MAXNODE];    // fail函数
    bool match[MAXNODE];    // match[i]表示结点i是否为单词结点
    int sz;
    void init() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }

    // 字符c的编号
    int idx(char c) {
        if(!idc[c]) idc[c]=++cnt;
        return idc[c];
    }

    // 插入字符串。v必须非0
    void insert(char *s, int v) {
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                match[sz] = false;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        match[u] = true;
    }

    // 计算fail函数
    void getFail() {
        queue<int> q;
        f[0] = 0;
        // 初始化队列
        for(int c = 0; c < SIGMA_SIZE; c++) {
            int u = ch[0][c];
            if(u) { f[u] = 0; q.push(u); }
        }
        // 按BFS顺序计算fail
        while(!q.empty()) {
            int r = q.front(); q.pop();
            for(int c = 0; c < SIGMA_SIZE; c++) {
                int u = ch[r][c];
                if(!u) { ch[r][c]=ch[f[r]][c];continue;}   // 没有last数组，直接连接
                q.push(u);
                int v = f[r];
                while(v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                match[u]|=match[f[u]];
            }
        }
    }

    double getProb(int u,int L) {
        if(!L) return 1;
        if(vis[u][L]) return dp[u][L];
        vis[u][L]=true;
        double &ans=dp[u][L];
        ans=0;
        for (int i = 1; i <= n; ++i) {
            if(!match[ch[u][i]]) ans += p[i]*getProb(ch[u][i], L-1);
        }
        return ans;
    }

}ac;
int main() {
    int T,L;
    read(T);
    FOR(cas, 1, T) {
        ac.init();
        read(K);
        FOR(j, 1, K) scanf("%s",s[j]);
        read(n);
        cnt=n;
        memset(idc, 0, sizeof(idc));
        memset(vis,false, sizeof(vis));
        FOR(j, 1, n) {
            scanf("%s %lf",str,p+j);
            v[j]=str[0];
            idc[str[0]]=j;
        }
        read(L);
        FOR(j, 1, K) {
            ac.insert(s[j], j);
        }
        ac.getFail();
        printf("Case #%d: %.6f\n",cas,ac.getProb(0, L));
    }
    return 0;
}