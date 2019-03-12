#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<lolo, lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)25e4 + 5;
const int maxm = (int)2e5 + 5;
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
int n,m,k;
lolo ans[maxm];
int op[maxn];
int pa[maxn],sub[maxn];
int findset(int x) {return pa[x]==x?x:pa[x]=findset(pa[x]);}
//我们先把所有串都插进去，然后一个个字符删除，找链上那个次数大于等于k的节点。
//因为小于k的节点已经没用，用一个并查集进行路径压缩。使得可以快速到达第一个次数>=k的节点

// 用一个节点的len减去父节点的fa.len，就是该节点表示的串中父节点不能表示的串个数。
// 当某节点的计数到达k次时，就说明有len-fa.len个不同子串计数到达k次了。
//（同理，当插入这个节点，出现的新不同子串个数就是len-fa.len。这也是很有用的性质。）
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
    int nc[maxn];  // 第i个字符对应的节点
    int idx, last;
    int c[maxn],que[maxn<<1];
    int ccnt[maxn<<1];
    void init() {
        idx = last = 0;
        sn[idx++].init();
    }
    int newnode() {
        sn[idx].init();
        return idx++;
    }
    void add(int c,int ind) {
        int end = newnode();
        nc[ind]=end;
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
    void solve(int len) {
        memset(c,0, sizeof(int)*(len+5));
        memset(ccnt, 0, sizeof (int)*(idx));
        for (int i = 0; i < idx; ++i) ++c[sn[i].len];
        FOR(i,1,len) c[i]+=c[i-1];
        IFOR(i,idx-1,0) que[c[sn[i].len]--]=i;
        for (int i = 0,p=0; i < len; ++i) {
            ++ccnt[p = sn[p].ch[s[i]-'a']];
        }
        IFOR(i,idx,1) {
            int &u=que[i];
            if(sn[u].f!=-1) ccnt[sn[u].f]+=ccnt[u];
        }
        lolo ret=0;
        for (int i = 0; i < idx; ++i) {
            if(ccnt[i]>=k) {
                ret+=sn[i].len;
                if(sn[i].f!=-1) ret-=sn[sn[i].f].len;
            }
        }
        for (int i = 0; i < idx; ++i) pa[i]=i,sub[i]=0;
        int p,y,f;
        IFOR(i,m,1) {
            if(op[i]==2) {
                ans[i]=ret;
                continue;
            }
            p=nc[--n];
            y=findset(p);
            while(y!=0&&ccnt[y]<k) {   //find first>=k 以它为根
                f=sn[y].f;
                pa[y]=f=findset(f);
                y=f;
            }
            y=findset(p);
            if(y==0) continue;
            ++sub[y];
            while(y!=0&&(ccnt[y]-sub[y]<k)){   //after -1,find first >=k
                ret-=sn[y].len-sn[sn[y].f].len;
                f=sn[y].f;
                f=findset(f);
                sub[f]+=sub[y];
                pa[y]=f;
                y=f;
            }
        }
        FOR(i,1,m) {
            if(op[i]==2) printf("%lld\n",ans[i]);
        }
    }
}sam;

int main() {
    while (scanf("%d%d%d",&n,&m,&k)!=EOF) {
        sam.init();
        scanf("%s", s);
        for (int i = 0; i < n; ++i) sam.add(s[i] - 'a',i);
        char c[3];
        FOR(i,1,m) {
            read(op[i]);
            if(op[i]==1) {
                scanf("%s",c);
                sam.add(c[0]-'a',n);
                s[n++]=c[0];
            }
        }
        sam.solve(n);
    }
    return 0;
}