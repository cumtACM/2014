#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <bitset>
#include <unordered_map>
#include <map>
#include <set>
#include <ctime>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 1000010;
const int maxm = 200005;
const int INF = 1000000000;
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
bool Eoln(char ch) {return ch==10||ch==13||ch==EOF;}
int reads(char *s)   // 读取字符串，并在每个字符之间插入'%'
{
    int len=0;char ch=getchar();if (ch==EOF) return EOF;
    s[++len]='%';
    s[++len]=ch;while (!Eoln(s[len])) s[++len]='%',s[++len]=getchar();s[++len]='%';s[len--]=0;
    return len;
}
char str[110];
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
char s[maxn<<1];
int p[maxn<<1],n;
int manacher(char *s) {     // 马拉车算法，p[i]记录以i为中心，最长向左或右衍生的回文串半长度。
    int ans=0;
    int pos=0,R=0;    // R是回文子串能覆盖到的最右位置,pos为对应的中心
    p[0]=1;
    for(int i=1;i<n;++i) {
        p[i]=i<R?min(p[2*pos-i],R-i):1;
        while (0<=i-p[i]&&s[i-p[i]]==s[i+p[i]]) ++p[i];
        if(i+p[i]>R) pos=i,R=i+p[i];
        if(p[i]-1>ans) ans=p[i]-1;      // 因为插入了'%'的缘故，p[i]对应的实际回文串长度为p[i]-1
    }
    return ans;
}
int main(){
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/CCPP/CCPP/in.txt","r",stdin);
    int T;
    read(T);
    while (T--) {
        n = reads(s);
        out(manacher(s));
        putchar('\n');
    }
    return 0;
}