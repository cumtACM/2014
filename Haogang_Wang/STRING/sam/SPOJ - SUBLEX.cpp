#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<lolo, lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)9e4 + 5;
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
    int idx, last;
    // 从每个状态出发的不同路径数
    int dp[maxn<<1];
    int c[maxn],que[maxn<<1];
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
        last = end;
    }
    void calc(int len) {
        memset(c,0, sizeof(c));
        for (int i = 0; i < idx; ++i) ++c[sn[i].len];
        for (int i = 1; i <= len; ++i) c[i]+=c[i-1];
        for (int i = idx-1; i >= 0; --i) que[c[sn[i].len]--]=i;
        for (int i = idx; i > 0; --i) {
            int &u=que[i];
            dp[u]=1;    // 空路径
            for (int j = 0; j < 26; ++j) {
                if(sn[u].ch[j]!=-1) dp[u]+=dp[sn[u].ch[j]];
            }
        }
    }
    void query(int k) {
        int u=0;
        while(k) {
            FOR(i,0,25) {
                if(sn[u].ch[i]!=-1) {
                    int v=sn[u].ch[i];
                    if(dp[v]>=k) {
                        u=v;
                        putchar('a'+i);
                        --k;   // 减去一个空路径
                        break;
                    } else k-=dp[v];
                }
            }
        }
        putchar('\n');
    }
}sam;

int main() {
    sam.init();
    scanf("%s",s);
    int len=(int)strlen(s);
    for(int i=0;i<len;++i) sam.add(s[i]-'a');
    int q,k;
    sam.calc(len);
    read(q);
    while (q--) {
        read(k);
        sam.query(k);
    }
    return 0;
}