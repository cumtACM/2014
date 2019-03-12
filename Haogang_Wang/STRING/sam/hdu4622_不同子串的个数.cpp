#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<lolo, lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)2e3 + 5;
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
int n,ans[maxm];
struct Node {
    int ind,l,r;
}node[maxm];
bool cmp(const Node& a,const Node& b) {
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}
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
        last=end;
    }
    // 对于给定的后缀自动机，不同子串的个数是遍历每一个节点，ans += ele[i].len - ele[ele[i].f].len，
    // 意思为枚举每个子串的最后一个元素，新增的子串个数就是到该点最长后缀减去与其父亲节点的重复后缀部分。
    // 后缀数组则是在遍历height数组的时候确定每个子串的开始位置，然后减去相同的前缀部分。
    int calc() {
        int ret=0;
        FOR(i,1,idx-1) {
            ret+=sn[i].len-sn[sn[i].f].len;
        }
        return ret;
    }
}sam;

int main() {
    int T;
    read(T);
    while (T--) {
        scanf("%s",s+1);
        n=(int)strlen(s+1);
        int q;
        read(q);
        FOR(i,0,q-1) {
            read(node[i].l);read(node[i].r);
            node[i].ind=i;
        }
        sort(node,node+q,cmp);
        FOR(i,0,q-1) {
            if(!i||node[i].l!=node[i-1].l) {
                sam.init();
                FOR(j,node[i].l,node[i].r)
                    sam.add(s[j]-'a');
            } else {
                FOR(j,node[i-1].r+1,node[i].r)
                    sam.add(s[j]-'a');
            }
            ans[node[i].ind]=sam.calc();
        }
        FOR(i,0,q-1) printf("%d\n",ans[i]);
    }
    return 0;
}