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
const int MAXNODE=11000;
const int SIGMA_SIZE=30;
int n;
char s[155][75],T[1000005];
struct AhoCorasickAutomata {
    int ch[MAXNODE][SIGMA_SIZE];
    int f[MAXNODE];    // fail函数
    int val[MAXNODE];  // 每个字符串的结尾结点都有一个非0的val
    int last[MAXNODE]; // 输出链表的下一个结点
    int cnt[155];
    int sz;
    void init() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        memset(cnt, 0, sizeof(cnt));
    }

    // 字符c的编号
    int idx(char c) {
        return c-'a';
    }

    // 插入字符串。v必须非0
    void insert(char *s, int v) {
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    // 计算fail函数
    void getFail() {
        queue<int> q;
        f[0] = 0;
        // 初始化队列
        for(int c = 0; c < SIGMA_SIZE; c++) {
            int u = ch[0][c];
            if(u) { f[u] = 0; q.push(u); last[u]=0;}
        }
        // 按BFS顺序计算fail
        while(!q.empty()) {
            int r = q.front(); q.pop();
            for(int c = 0; c < SIGMA_SIZE; c++) {
                int u = ch[r][c];
                if(!u) continue;
                q.push(u);
                int v = f[r];
                while(v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }

    void find(char *T) {
        int len = (int)strlen(T);
        int j=0;
        for (int i = 0; i < len; ++i) {
            int c= idx(T[i]);
            while(j&&!ch[j][c]) j=f[j];
            j=ch[j][c];
            if(val[j]) print(j);
            else if(last[j]) print(last[j]);
        }
    }

    void print(int j){
        if(j) {
            cnt[val[j]]++;   // 由输出改为计数
            print(last[j]);
        }
    }

}ac;
int main() {
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/in.txt", "r", stdin);
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/out.txt", "w", stdout);
    while (true) {
        ac.init();
        read(n);
        if(!n) break;
        FOR(j, 1, n) {
            scanf("%s",s[j]);
            ac.insert(s[j], j);
        }
        ac.getFail();
        scanf("%s",T);
        ac.find(T);
        vector<int> ans;
        int maxc=0;
        FOR(j, 1, n) {
            if(ac.cnt[j]>maxc) {
                maxc=ac.cnt[j];
                ans.clear();
                ans.push_back(j);
            } else if(ac.cnt[j]==maxc) {
                ans.push_back(j);
            }
        }
        out(maxc);
        putchar('\n');
        for (int i = 0; i < ans.size(); ++i) {
            printf("%s\n",s[ans[i]]);
        }
    }
    return 0;
}
