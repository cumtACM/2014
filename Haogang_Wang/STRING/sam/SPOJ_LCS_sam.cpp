// 题意：求两个串的最长公共子串。
#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = (int)250000 + 5;
const int maxm = (int)1e6 + 5;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-18;
const int MOD = (int)1e9+7;

template<class T>
inline void out(T x) {
    if (x > 9) out(x / 10);
    x = x % 10;
    putchar('0' + x);
}

char s1[maxn],s2[maxn];
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
    // 先用第一个串构造出后缀自动机，然后逐个的匹配第二个串，如果当前节点失配，那么找 f 节点。
    void solve() {
        int u = 0, ans = 0, len = 0;
        for(int i=0;s2[i];++i) {
            int idx=s2[i]-'a';
            if(sn[u].ch[idx]!=-1) {
                len++;
                u=sn[u].ch[idx];
            } else {
                for(;u!=-1&&sn[u].ch[idx]==-1;u=sn[u].f);
                if(u==-1) len=u=0;
                else {
                    len=sn[u].len+1;
                    u=sn[u].ch[idx];
                }
            }
            ans=max(len,ans);
        }
        out(ans);
        putchar('\n');
    }
}sam;

int main() {
//    freopen("../in.txt","r",stdin);
    scanf("%s%s",s1,s2);
    sam.init();
    for(int i=0;s1[i];++i) sam.add(s1[i]-'a');
    sam.solve();
    return 0;
}
