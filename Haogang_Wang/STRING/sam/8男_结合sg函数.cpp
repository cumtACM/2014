#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<lolo, lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)1e5 + 5;
const int maxm = (int)1e4 + 5;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-18;
const int MOD = (int)1e9+7;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
template<class T>
inline void out(T x) {
    if (x > 9) out(x / 10);
    x = x % 10;
    putchar('0' + x);
}
char s[maxn];
struct SAM {
    struct Node {
        int ch[26];
        int f, len;
        void init() {
            f = -1, len = 0;
            memset(ch, 0xff, sizeof (ch));
        }
    };
    Node sn[maxn<<1];
    int idx, last, sg[maxn<<1];
    int c[maxn],que[maxn<<1];
    void init() {
        idx = last = 0;
        sg[0]=-1;
        sn[idx++].init();
    }
    int newnode() {
        sn[idx].init();
        sg[idx]=-1;
        return idx++;
    }
    void add(int c) {
        int end = newnode();
        int tmp = last;
        sn[end].len = sn[last].len + 1;
        for ( ; tmp != -1 && sn[tmp].ch[c] == -1; tmp = sn[tmp].f) {
            sn[tmp].ch[c] = end;
        }
        if (tmp == -1) sn[end].f = 0; // 所有的上一轮可接受点都没有指向字符c的孩子节点
        else {
            int nxt = sn[tmp].ch[c];
            if (sn[tmp].len + 1 == sn[nxt].len) sn[end].f = nxt; // 如果可接受点有向c的转移，且长度只加1，那么该孩子可以替代当前的end，并且end的双亲指向该孩子
            else {
                int np = newnode();
                sn[np] = sn[nxt];
                sn[np].len = sn[tmp].len + 1;
                sn[end].f = sn[nxt].f = np;
                for (; tmp != -1 && sn[tmp].ch[c] == nxt; tmp = sn[tmp].f) {
                    sn[tmp].ch[c] = np;
                }
            }
        }
        last=end;
    }
    void calc(int len) {
        memset(c,0, sizeof(c));
        for (int i = 0; i < idx; ++i) ++c[sn[i].len];
        for (int i = 1; i <= len; ++i) c[i]+=c[i-1];
        for (int i = idx-1; i >= 0; --i) que[c[sn[i].len]--]=i;
        memset(sg,-1, sizeof(int)*idx);
        vector<int> vis;
        IFOR(i,idx,1) {
            int &u=que[i];
            sg[u]=0;
            vis.clear();
            FOR(j,0,25) {
                if(sn[u].ch[j]!=-1) {
                    vis.push_back(sg[sn[u].ch[j]]);
                }
            }
            sort(vis.begin(),vis.end());
            if(vis.empty()||vis[0]!=0) continue;
            FOR(i,1,vis.size()-1) if(vis[i]>vis[i-1]+1) {
                    sg[u]=vis[i-1]+1;
                    break;
                }
            if(sg[u]==0) sg[u]=vis[vis.size()-1]+1;
        }
    }
    int getSG(char *s) {
        int u=0;
        for (int i = 0; s[i]; ++i) {
            u=sn[u].ch[s[i]-'a'];
        }
        return sg[u];
    }
}sam;

int main() {
    while (scanf("%s",s)!=EOF) {
        sam.init();
        int len=(int)strlen(s);
        for(int i=0;i<len;++i) sam.add(s[i]-'a');
        sam.calc(len);
        int n;
        read(n);
        int ans=0;
        while(n--) {
            scanf("%s",s);
            ans^=sam.getSG(s);
        }
        puts(ans?"Alice":"Bob");
    }
    return 0;
}
