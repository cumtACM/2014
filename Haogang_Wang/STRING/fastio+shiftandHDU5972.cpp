//  FastIO+shiftAnd HDU5972
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 1005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0;
    T flag=1;
    char c;
    do {
        c = (char)getchar();
        if(c=='-') break;
    } while (c < '0' || c > '9');
    if(c=='-')
        c='0',flag=-1;
    do {
        x = x * 10 + c - '0';
        c = (char)getchar();
    } while (c >= '0' && c <= '9');
    x*=flag;
}
struct ShiftAnd {
    int size = 128; // 此处默认字符集规模为128

    //预处理，
    void preShiftAnd(const char *p, int m, unsigned int *s){
        for(int i=0; i<size; i++)
            s[i] = 0;
        for(int i=0; i<m; i++){
            s[p[i]] |= 1<<i;
        }
    }

    //Shift—And
    int shiftAnd(const char *t, const char *p) {
        int tLen = strlen(t);
        int pLen = strlen(p);
        unsigned int state = 0;            //即D数组
        unsigned int s[size];

        if(tLen < pLen) return -1;

        preShiftAnd(p, pLen, s);     //预处理

        for(int i=0; i<tLen; i++){
            state = ((state<<1)|1) & s[t[i]];
            if(state & 1<<(pLen-1))            //最高位出现1
                return i - pLen + 1;
        }
        return -1;
    }
    // my version
    vector<int> ans;
    void shiftAnd(const char *p,const char *t,int m) {
        ans.clear();
        bitset<maxn+5> b[size];
        for(int i=0; i<size; i++)
            b[i].reset();
        for(int i=0; i<m; i++){
            b[p[i]].set(i);
        }
        bitset<maxn+5> state;
        for(int i=0; t[i]; i++){
            state = state<<1;
            state.set(0);
            state = state & b[t[i]];
            if(state[m-1])            //最高位出现1
                ans.push_back(i - m + 1);
        }
    }
};
struct FastIO
{
    static const int S = 2 * 5000005;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar()
    {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos ++];
    }
    inline int xuint()
    {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline int xint()
    {
        int s = 1, c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    inline void xstring(char *s)
    {
        int c = xchar();
        while (c <= 32) c = xchar();
        for (; c > 32; c = xchar()) * s++ = c;
        *s = 0;
    }
    inline void wchar(int x)
    {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos ++] = x;
    }
    inline void wint(lolo x)
    {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n ++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
    }
    inline void wstring(const char *s)
    {
        while (*s) wchar(*s++);
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

bitset<maxn> b[10],ans;
char str[5000005];
int main() {
    int n,a,x;
    n=io.xint();
    for(int i=0;i<n;i++) {
        a=io.xint();
        while(a--) {
            x=io.xint();
            b[x].set(i);
        }
    }
    io.xstring(str);
    for(int i = 0; str[i]; i++){
        ans <<= 1;
        ans[0] = 1;
        ans &= b[str[i]-'0'];
        if(ans[n-1]){
            for(int j = i - n + 1; j <= i; j++) io.wchar(str[j]);
            io.wchar('\n');
        }
    }
    return 0;
}
