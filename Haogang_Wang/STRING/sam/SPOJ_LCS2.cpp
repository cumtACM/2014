#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<lolo, lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)1e5 + 5;
const int maxm = (int)1e6 + 5;
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
//    mxa代表该节点满足所有字符串的最大值，初始化为该字符串建立时的最大值，每次匹配后更新。
//    mx代表该节点满足单一字符串时的最大值，匹配完一个字符串后重置为0；
    int mx[maxn<<1],mxa[maxn<<1],c[maxn<<1],que[maxn<<1];
    int idx, last;
    void init() {
        idx = last = 0;
        sn[idx++].init();
    }
    int newnode() {
        sn[idx].init();
        return idx++;
    }
    void add(int c) {
        int end = newnode();
        int tmp = last;
        mxa[end]=sn[end].len = sn[last].len + 1;
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
                mxa[np]=sn[np].len = sn[tmp].len + 1;
                sn[end].f = sn[nxt].f = np;
                for (; tmp != -1 && sn[tmp].ch[c] == nxt; tmp = sn[tmp].f) {
                    sn[tmp].ch[c] = np;
                }
            }
        }
        last = end;
    }
    void solve(int len1) {
        memset(c,0,sizeof(c));
        // 基数排序 按照拓扑序从后往前更新（保证父节点在子节点后被更新）
        for(int i=0;i<idx;i++) c[sn[i].len]++;
        for(int i=1;i<=len1;i++) c[i]+=c[i-1];
        for(int i=idx-1;i>=0;i--) que[c[sn[i].len]--]=i;
        while(scanf("%s", s)!=EOF) {
            int len=(int)strlen(s);
            memset(mx,0,sizeof(mx));
            int u=0,curlen=0;
            for(int i=0;i<len;i++) {
                int idx=s[i]-'a';
                if(sn[u].ch[idx]!=-1) {
                    u=sn[u].ch[idx];
                    ++curlen;
                }
                else {
                    for(;u!=-1&&sn[u].ch[idx]==-1;u=sn[u].f);
                    if(u==-1) curlen=u=0;
                    else {
                        curlen=sn[u].len+1;
                        u=sn[u].ch[idx];
                    }
                }
                mx[u]=max(mx[u],curlen);

            }
            for(int i=idx;i>0;i--)  {
                int &u=que[i];
                // 因为虽然mx记录在了某个状态上，但实际上mx对一切该状态的祖先都是可行的
                // （只不过匹配的时候匹配了该状态），所以我们还需要向上传递一下，这样才能够刷出正确的答案。
                if(sn[u].f!=-1) {
                    mx[sn[u].f] = max(mx[sn[u].f], mx[u]);
                }
                mxa[u]=min(mxa[u],mx[u]);
            }
        }
        int ans=0;
        IFOR(i,idx-1,0) ans=max(mxa[i],ans);
        out(ans);putchar('\n');
    }
}sam;

int main() {
    sam.init();
    scanf("%s",s);
    int len=(int)strlen(s);
    for(int i=0;i<len;++i) sam.add(s[i]-'a');
    sam.solve(len);
    return 0;
}