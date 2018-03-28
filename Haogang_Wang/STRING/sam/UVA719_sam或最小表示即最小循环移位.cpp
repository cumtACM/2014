#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>
#include <bitset>
#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <iomanip>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)


using namespace std;

typedef long long lolo;
typedef pair<lolo, lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)5e4 + 5;
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

struct sam {
    int last,p,q,np,nq,l[maxn],par[maxn],to[maxn][27],pos[maxn],sum;
    sam() {
        last=++sum;
    }
    inline void extend(int c,int now) {
        p=last,np=last=++sum;
        pos[np]=now;
        l[np]=l[p]+1;
        for(;!to[p][c];p=par[p])to[p][c]=np;
        if(!p)par[np]=1;
        else {
            int q=to[p][c];
            if(l[q]==l[p]+1)par[np]=q;
            else {
                nq=++sum;l[nq]=l[p]+1;
                memcpy(to[nq],to[q],sizeof(to[nq]));
                par[nq]=par[q];par[q]=par[np]=nq;
                for(;to[p][c]==q;p=par[p])to[p][c]=nq;
            }
        }
    }
    inline void build(char *ch,int len){
        for(int i=1;i<=len;i++)
            extend(ch[i]-'a'+1,i);
    }
    inline void reset(){
        last=sum=1;
        memset(l,0,sizeof(l));
        memset(par,0,sizeof(par));
        memset(to,0,sizeof(to));
    }
    inline int find(int le){
        int po=1;
        for(int tt=1;tt<=le;tt++){
            for(int i=1;i<=26;i++){
                if(to[po][i]){
                    po=to[po][i];
                    break;
                }
            }
        }
        return pos[po];
    }
}sam;

char s[20005];
int main() {
    int T;
    read(T);
    while(T--) {
        scanf("%s",s+1);
        int n=(int)strlen(s+1);
        sam.reset();
        memcpy(s+1+n,s+1,sizeof(char)*n);
        sam.build(s,n<<1);
        printf("%d\n",sam.find(n)-n+1);
    }
    return 0;
}