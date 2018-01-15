/*
根据前缀判断所属
*/
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
const int maxnode=100005;
int n,num[110],ans;
char A[110][20],B[110][20],bp[110][22],s[22];
bool valid[110];
struct Trie {
    int ch[maxnode][12];
    int val[maxnode];
    int sz;
    void init() {
        sz=1;
        memset(ch[0], 0, sizeof(ch[0]));
        val[0]=0;
    }
    int idx(char c) { return c-'0';}
    void insert(char *s1,char *s2,int bl) {
        int u1=0,u2=0,len=(int)strlen(s1);
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < 10; ++j) {
                if(!ch[u1][j]) {
                    memset(ch[sz], 0, sizeof(ch[sz]));
                    val[sz]=0;
                    ch[u1][j]=sz++;
                }
                if(val[u1]>0) val[ch[u1][j]]=val[u1];   //将标记都向下推移,新的优先级大于旧的
                if(!ch[u2][j]) {
                    memset(ch[sz], 0, sizeof(ch[sz]));
                    val[sz]=0;
                    ch[u2][j]=sz++;
                }
                if(val[u2]>0) val[ch[u2][j]]=val[u2];
            }
            val[u1]=val[u2]=0;
            if(u1==u2) {      //被bl这个支线占领的部分,并不要拓展因为到了这里就可以判断出前缀所属
                for (int j = s1[i]-'0'+1; j < s2[i]-'0'; ++j) {
                    val[ch[u1][j]]=bl;
                }
            } else {
                for (int j = 0; j < s2[i]-'0'; ++j) {
                    val[ch[u2][j]]=bl;
                }
                for (int j = s1[i]-'0'+1; j < 10; ++j) {
                    val[ch[u1][j]]=bl;
                }
            }
            u1=ch[u1][s1[i]-'0'];
            u2=ch[u2][s2[i]-'0'];
        }
        val[u1]=val[u2]=bl;
    }
    void dfs(int u) {
        if(val[u]>0) {
            ans+=valid[val[u]];
            return;
        }
        if(!ch[u][0]) return;
        bool flag=false;
        for (int i = 0; i < 10; ++i) {
            dfs(ch[u][i]);
            if(val[ch[u][i]]!=val[ch[u][0]]) {
                flag=true;
            }
        }
        //合并操作要在回溯中进行方便之后的输出
        if(!flag && valid[val[ch[u][0]]] && u != 0)//下面所有分支都被同一支线用了
        {
            ans -= 9;
            val[u] = val[ch[u][0]];//还原
        }
    }
    void output(int u,int len) {
        if(val[u]>0) {
            if(valid[val[u]]) {
                for (int i = 0; i < len; ++i) {
                    putchar(s[i]);
                }
                putchar(' ');
                puts(bp[val[u]]);
            }
            return ;
        }
        if(!ch[u][0]) return;
        for (int j = 0; j < 10; ++j) {
            s[len]=j+'0';
            output(ch[u][j], len+1);
        }
    }
}trie;

int main() {
    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/in.txt", "r", stdin);
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/out.txt", "w", stdout);
    int cas=1;
    while(scanf("%d",&n)!=EOF) {
        if(cas++>1) putchar('\n');
        ans=0;
        trie.init();
        FOR(j, 1, n) {
            scanf("%s - %s %s",A[j],B[j],bp[j]);
            int len1= strlen(A[j]),len2= strlen(B[j]);
            IFOR(i, len2-1, 0) {
                B[j][i+len1-len2]=B[j][i];
            }
            FOR(i, 0, len1-len2-1) {
                B[j][i]=A[j][i];
            }
            valid[j]=strcmp(bp[j], "invalid")!=0;
            num[j]=j;
            FOR(i, 1, j-1) {
                if(strcmp(bp[j], bp[i])==0) {
                    num[j]=i;
                    break;
                }
            }
        }
        IFOR(j, n, 1) {  //一定要倒着插入, 先插入的会被覆盖, 对应的是给出的表中后出现的
            trie.insert(A[j], B[j], num[j]);
        }
        trie.dfs(0);
        out(ans);
        putchar('\n');
        trie.output(0, 0);
    }
    return 0;
}
