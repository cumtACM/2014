#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<lolo, lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)25e4 + 5;
const int maxm = (int)1e6 + 5;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-18;
const int MOD = (int)1e9+7;


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
    int c[maxn],que[maxn<<1],ans[maxn];
    int ccnt[maxn<<1]; // ccnt[i]表示i号节点表示的最长子串能够被包含多少次
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
    //然后初始化中间那条最长链上的节点(就是原串)，每个节点代表一个后缀，这样一开始就有n个数量为1的后缀。
    //紧接着，我们将所有的节点按照长度从大到下来迭代更新，每次更新当然只能够更新其f指针，f指针表示与其拥有相同的后缀但是最长长度小于当前后缀的最长长度。
    //这次也顺便构造出一些字符串发现一个替换其他节点的点，可能被再次替换；一个被替换的点可能被替换多次。
    void solve(int len) {
        memset(c,0, sizeof(int)*(len+5));
        memset(ccnt, 0, sizeof (int)*(len+5));
        memset(ans, 0, sizeof (int)*(len+5));
        for (int i = 0; i < idx; ++i) ++c[sn[i].len];
        FOR(i,1,len) c[i]+=c[i-1];
        IFOR(i,idx-1,0) que[c[sn[i].len]--]=i;
        // 初始化原始的后缀
        for (int i = 0, p = 0; i < len; ++i) {
            ++ccnt[p = sn[p].ch[s[i]-'a']];
        }

        IFOR(i,idx,1) { // 长度长的后缀能够更新与其拥有相同后缀的较短的后缀
            int &u=que[i];
            ans[sn[u].len] = max(ans[sn[u].len], ccnt[u);
            if (sn[u].f > 0) ccnt[sn[u].f] += ccnt[u;
        }

        for (int i = 1; i <= len; ++i) printf("%d\n", ans[i]);
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